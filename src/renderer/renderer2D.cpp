#include <iostream>
#include <atomic>
#include <future>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <shared_mutex>

#define GLM_FORCE_CTOR_INIT
#include "vertex.hpp"
#include "glcommon.hpp"
#include "renderer/renderer2D.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "math/lestMath.hpp"
#include "renderer/contextResourceManager.hpp"

static const uint8_t TWO_D_COORDS = 2;
static const uint8_t TRIANGLE_VERTICES2D = 3;
static const uint8_t SQUARE_VERTICES2D = 4;
static const uint8_t RGBA = 4;
static const uint8_t SQUARE_INDICES = 6;
static const uint8_t SQUARE_BYTE_SIZE = 32;
static const uint32_t BYTES_IN_MB = 1048576;
static const uint32_t sMaxQuads = 1000;
static const uint32_t sMaxVertices = sMaxQuads * 4;
static const uint32_t sMaxIndices = sMaxQuads * 6;
static int32_t sMaxTextures;

enum VertexPositions
{
  BOTTOM_LEFT,
  BOTTOM_RIGHT,
  TOP_RIGHT,
  TOP_LEFT
};

struct TextureCacheData
{
  std::shared_ptr<TextureResource> TexturePtr;
  bool Bounded;
};

struct RenderData
{
  std::shared_ptr<VertexArray> QuadVao;
  std::shared_ptr<VertexBuffer> QuadVbo; // Can be removed soon Vao keeps track of this
  std::shared_ptr<Shader> QuadShader;
  Vertex Quads[sMaxVertices];
  std::vector<TextureCacheData> TextureCache;
  uint8_t TextureCacheIndex;
  uint32_t NumVerts;
  uint32_t NumQuadCount;
  glm::mat4 ViewProjection;
  std::shared_ptr<OrthCamera> CameraView;
  std::shared_ptr<std::mutex> VboMutex;
};

static bool sLimitsDefined = false;
static glm::vec2 sTextCoords[sNumQuadVerts];
static glm::vec4 sQuadVertexes[sNumQuadVerts];

std::shared_mutex sSharedMutex;
std::unordered_map<GLFWwindow*, RenderData> sContextMap;

void initNewContext(GLFWwindow* pContext)
{
  sSharedMutex.lock();
  RenderData* renderData = &sContextMap[pContext];
  sSharedMutex.unlock();
  renderData->QuadVao = std::make_shared<VertexArray>();

  renderData->QuadVbo = std::make_shared<VertexBuffer>(sMaxVertices * sizeof(Vertex), GL_DYNAMIC_DRAW);
    
  // First set of Float are quad position
  // First set of Float are quad position
  // Next 2 floats are Texture Coords
  // Next float is Texture Index
  renderData->QuadVbo->setLayout({
    {GL_FLOAT, TWO_D_COORDS, false},
    {GL_UNSIGNED_BYTE, RGBA, true},
    {GL_FLOAT, TWO_D_COORDS, false},
    {GL_FLOAT, 1, false}
  });

  renderData->QuadVao->addVertexBuffer(renderData->QuadVbo);

  std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(sMaxIndices, GL_STATIC_DRAW);
  renderData->QuadVao->setIndexBuffer(ibo);

  renderData->QuadShader = std::make_shared<Shader>("./shaders/shader1.txt");

  renderData->QuadShader->bind();
  auto uni = renderData->QuadShader->getUniform("u_Textures");
  int sampler[sMaxTextures];
  std::cout << "Num text: " << sMaxTextures<< std::endl;
  for(int i = 0; i < sMaxTextures; i ++)
  {
    sampler[i] = i;
  }

  GLCall(glUniform1iv(uni, sMaxTextures, sampler));
  renderData->NumVerts = 0;
  renderData->NumQuadCount = 0;
  renderData->TextureCache.resize(sMaxTextures);
  renderData->TextureCacheIndex = 0;
  renderData->VboMutex = std::make_shared<std::mutex>();
  // sSharedMutex.unlock();
}

void initSharedContext(GLFWwindow* pOriginalContext, GLFWwindow* pNewContext)
{
  sSharedMutex.lock();
  RenderData* renderData = &sContextMap[pNewContext];
  RenderData* originalData = &sContextMap[pOriginalContext];
  // sSharedMutex.unlock();
  renderData->QuadVao = std::make_shared<VertexArray>();
  renderData->QuadVbo = originalData->QuadVbo;
  renderData->QuadVao->addVertexBuffer(renderData->QuadVbo);
  renderData->QuadVao->setIndexBuffer(originalData->QuadVao->getIndexBuffer());

  renderData->QuadShader = originalData->QuadShader;

  renderData->QuadShader->bind();
  renderData->VboMutex = originalData->VboMutex;
  // auto uni = sContextMap[pContext].QuadShader->getUniform("u_Textures");
  // int sampler[sMaxTextures];
  // std::cout << "Num text: " << sMaxTextures<< std::endl;
  // for(int i = 0; i < sMaxTextures; i ++)
  // {
  //   sampler[i] = i;
  // }

  // GLCall(glUniform1iv(uni, sMaxTextures, sampler));
  renderData->NumVerts = 0;
  renderData->NumQuadCount = 0;
  renderData->TextureCache.resize(sMaxTextures);
  renderData->TextureCacheIndex = 0;
  sSharedMutex.unlock();
}

void Renderer2D::registerContext(GLFWwindow* pOriginalContext, GLFWwindow* pNewContext)
{
  if(nullptr != pOriginalContext)
  {
    initSharedContext(pOriginalContext, pNewContext);
  }
  else
  {
    initNewContext(pNewContext);
  }
}

//! @brief Initializes the Renderer2D Engine
//!
//! @return None
void Renderer2D::init()
{
  if(!sLimitsDefined)
  {
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &sMaxTextures);
    sLimitsDefined = true;
    std::cout << glGetString(GL_VENDOR) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;
    sQuadVertexes[TOP_LEFT] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    sQuadVertexes[TOP_RIGHT] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    sQuadVertexes[BOTTOM_RIGHT] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    sQuadVertexes[BOTTOM_LEFT] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

    sTextCoords[BOTTOM_LEFT] = glm::vec2(0.0f, 0.0f);
    sTextCoords[BOTTOM_RIGHT] = glm::vec2(1.0f, 0.0f);
    sTextCoords[TOP_RIGHT] = glm::vec2(1.0f, 1.0f);
    sTextCoords[TOP_LEFT] = glm::vec2(0.0f, 1.0f);
  }
}

void Renderer2D::beginScene(const std::shared_ptr<OrthCamera>& crpCamera)
{
  initBatch();
  GLFWwindow* context = glfwGetCurrentContext();
  sSharedMutex.lock_shared();
  RenderData* renderData = &sContextMap[context];
  sSharedMutex.unlock_shared();
  renderData->ViewProjection = crpCamera->getViewProjectionMatrix();
  renderData->CameraView = crpCamera;
  // sSharedMutex.unlock_shared();
}

void Renderer2D::registerQuad(const glm::vec2& crPos, const glm::vec2& crSize,
                              std::array<Vertex, sNumQuadVerts>& rVertexes,
                              const lg::Color& crColor,
                              const bool cGeometryNeedUpdate)
{
  GLFWwindow* context = glfwGetCurrentContext();
  sSharedMutex.lock_shared();
  RenderData* renderData = &sContextMap[context];
  sSharedMutex.unlock_shared();

  if(renderData->NumVerts >= sMaxVertices)
  {
    nextBatch();
  }

  if(renderData->CameraView->geometryNeedUpdate() || cGeometryNeedUpdate)
  {
    // Apparently rounding crPos here may potentially cause stutters during movement, float values can cause rasterization issues so it's a trade off
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(crPos, 0.0f)) * /*rotation*/ glm::scale(glm::mat4(1.0f),
                                       {crSize.x, crSize.y, 1.0f});
    // Setting default color to purple, so if something bad happens when rendering it's in your face
    for(int i = 0; i < sNumQuadVerts; i ++)
    {
      renderData->Quads[renderData->NumVerts].Pos = renderData->ViewProjection * transform * sQuadVertexes[i];
      renderData->Quads[renderData->NumVerts].Rgba = crColor;
      renderData->Quads[renderData->NumVerts].TextCoord = sTextCoords[i];
      renderData->Quads[renderData->NumVerts].TextureIndex = -1;
      rVertexes[i] = renderData->Quads[renderData->NumVerts];

      renderData->NumVerts ++;
    }
  }
  else
  {
    for(int i = 0; i < sNumQuadVerts; i ++)
    {
      rVertexes[i].TextureIndex = -1;
      renderData->Quads[renderData->NumVerts] = rVertexes[i];

      renderData->NumVerts ++;
    }
  }

  renderData->NumQuadCount ++;
  // sSharedMutex.unlock_shared();
}

void Renderer2D::registerQuad(const glm::vec2& crPos, const glm::vec2& crSize,
                              std::array<Vertex, sNumQuadVerts>& rVertexes,
                              const std::shared_ptr<TextureResource>& crpTexture,
                              bool cGeometryNeedUpdate)
{
  GLFWwindow* context = glfwGetCurrentContext();
  sSharedMutex.lock_shared();
  RenderData* renderData = &sContextMap[context];
  sSharedMutex.unlock_shared();

  if(renderData->NumVerts >= sMaxVertices || renderData->TextureCacheIndex == sMaxTextures)
  {
    nextBatch();
  }

  float textureIndex = -1.0f;
  for(size_t i = 0; i < renderData->TextureCacheIndex; i ++)
  {
    if(*renderData->TextureCache[i].TexturePtr == *crpTexture)
    {
      textureIndex = i;
      break;
    }
  }

  if(-1 == textureIndex)
  {
    renderData->TextureCache[renderData->TextureCacheIndex].TexturePtr = crpTexture;
    renderData->TextureCache[renderData->TextureCacheIndex].Bounded = false;
    textureIndex = renderData->TextureCacheIndex;
    renderData->TextureCacheIndex ++;
  }

  if(renderData->CameraView->geometryNeedUpdate() || cGeometryNeedUpdate)
  {
    // rotation  glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3{0.0, 0.0, 1.0}) *
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(crPos, 0.0f)) * glm::scale(glm::mat4(1.0f),
                                        {crSize.x, crSize.y, 1.0f});

    // Setting default color to purple, so if something bad happens when rendering it's in your face
    for(int i = 0; i < sNumQuadVerts; i ++)
    {
      renderData->Quads[renderData->NumVerts].Pos = renderData->ViewProjection * transform * sQuadVertexes[i];
      renderData->Quads[renderData->NumVerts].Rgba = lg::Purple;
      renderData->Quads[renderData->NumVerts].TextCoord = rVertexes[i].TextCoord;
      renderData->Quads[renderData->NumVerts].TextureIndex = textureIndex;
      rVertexes[i] = renderData->Quads[renderData->NumVerts];

      renderData->NumVerts ++;
    }
  }
  else
  {
    for(int i = 0; i < sNumQuadVerts; i ++)
    {
      rVertexes[i].TextureIndex = textureIndex;
      renderData->Quads[renderData->NumVerts] = rVertexes[i];

      renderData->NumVerts ++;
    }
  }

  renderData->NumQuadCount ++;
  // sSharedMutex.unlock_shared();
}

void Renderer2D::endScene()
{
  GLFWwindow* context = glfwGetCurrentContext();
  // shouldRender = false;
  // nextBatch();
  flush();
  sSharedMutex.lock_shared();
  sContextMap[context].CameraView->unsetUpdateFlag();
  sSharedMutex.unlock_shared();
}

void Renderer2D::initBatch()
{
  GLFWwindow* context = glfwGetCurrentContext();
  sSharedMutex.lock_shared();
  RenderData* renderData = &sContextMap[context];
  sSharedMutex.unlock_shared();
  renderData->NumVerts = 0;
  renderData->NumQuadCount = 0;
  // sSharedMutex.unlock_shared();
}

void Renderer2D::nextBatch()
{
  flush();
  initBatch();
}

void Renderer2D::flush()
{
  GLFWwindow* context = glfwGetCurrentContext();
  sSharedMutex.lock_shared();
  RenderData* renderData = &sContextMap[context];
  sSharedMutex.unlock_shared();
  renderData->VboMutex->lock();

  for(size_t i = 0; i < renderData->TextureCacheIndex; i++)
  {
    if(!renderData->TextureCache[i].Bounded)
    {
      renderData->TextureCache[i].TexturePtr->bind(i);
      renderData->TextureCache[i].Bounded = true;
    }
  }
  // Draw stuff
  renderData->QuadVbo->updateVboSubBuffer(0, renderData->NumVerts * sizeof(Vertex), renderData->Quads);
  // ContextMap[ContextHash(glfwGetCurrentContext())]->bind();
  GLCall(glDrawElements(GL_TRIANGLES, renderData->NumQuadCount * 6, GL_UNSIGNED_INT, nullptr));
  renderData->VboMutex->unlock();
  // sSharedMutex.unlock_shared();
}

void Renderer2D::unregisterContext(GLFWwindow* pContext)
{
  sSharedMutex.lock();
  sContextMap.erase(pContext);
  sSharedMutex.unlock();
}