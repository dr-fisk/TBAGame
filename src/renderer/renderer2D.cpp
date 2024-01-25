#include <iostream>

#define GLM_FORCE_CTOR_INIT
#include "glcommon.hpp"
#include "renderer/renderer2D.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "math/lestMath.hpp"

const uint8_t TWO_D_COORDS = 2;
const uint8_t TRIANGLE_VERTICES2D = 3;
const uint8_t SQUARE_VERTICES2D = 4;
const uint8_t RGBA = 4;
const uint8_t SQUARE_INDICES = 6;
const uint8_t SQUARE_BYTE_SIZE = 32;
const uint32_t BYTES_IN_MB = 1048576;

struct RendererLimits
{
  const uint32_t MaxQuads = 1000;
  const uint32_t MaxVertices = MaxQuads * 4;
  const uint32_t MaxIndices = MaxQuads * 6;
  int32_t MaxTextures;
};

enum VertexPositions
{
  BOTTOM_LEFT,
  BOTTOM_RIGHT,
  TOP_RIGHT,
  TOP_LEFT
};

static std::shared_ptr<VertexArray> sQuadVao;
static std::shared_ptr<VertexBuffer> sQuadVbo;
static std::shared_ptr<Shader> sQuadShader;
static std::map<int8_t, std::shared_ptr<TextureResource>> sTextureCache;
static int8_t sBoundedTextureIdx;
static RendererLimits sRenderer2DLimits;
static bool sLimitsDefined = false;
static std::vector<Vertex> sQuads;
static uint32_t sNumVerts;
static uint32_t sNumQuadCount;
static glm::mat4 sViewProjection;
static glm::vec4 sQuadVertexes[sNumQuadVerts];
static glm::vec2 TextCoords[sNumQuadVerts];
static std::shared_ptr<OrthCamera> sCameraView;

//! @brief Initializes the Renderer2D Engine
//!
//! @return None
void Renderer2D::init()
{
  if(!sLimitsDefined)
  {
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &sRenderer2DLimits.MaxTextures);
    sLimitsDefined = true;
  }

  sQuadVao = std::make_shared<VertexArray>();

  sQuadVbo = std::make_shared<VertexBuffer>(sRenderer2DLimits.MaxVertices * sizeof(Vertex), GL_DYNAMIC_DRAW);
    
  // First set of Float are quad position
  // First set of Float are quad position
  // Next 2 floats are Texture Coords
  // Next float is Texture Index
  sQuadVbo->setLayout({
    {GL_FLOAT, TWO_D_COORDS, true},
    {GL_UNSIGNED_BYTE, RGBA, true},
    {GL_FLOAT, TWO_D_COORDS, false},
    {GL_FLOAT, 1, false}
  });

  sQuadVao->addVertexBuffer(sQuadVbo);

  std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(sRenderer2DLimits.MaxIndices, GL_STATIC_DRAW);
  sQuadVao->setIndexBuffer(ibo);

  sQuadShader = std::make_shared<Shader>("./shaders/shader1.txt");

  sQuadShader->bind();

  auto uni = sQuadShader->getUniform("u_Textures");
  int sampler[sRenderer2DLimits.MaxTextures];

  std::cout << glGetString(GL_VENDOR) << std::endl;
  std::cout << glGetString(GL_RENDERER) << std::endl;
  std::cout << glGetString(GL_VERSION) << std::endl;
  sQuadVertexes[TOP_LEFT] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  sQuadVertexes[TOP_RIGHT] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
  sQuadVertexes[BOTTOM_RIGHT] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
  sQuadVertexes[BOTTOM_LEFT] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

  TextCoords[BOTTOM_LEFT] = glm::vec2(0.0f, 0.0f);
  TextCoords[BOTTOM_RIGHT] = glm::vec2(1.0f, 0.0f);
  TextCoords[TOP_RIGHT] = glm::vec2(1.0f, 1.0f);
  TextCoords[TOP_LEFT] = glm::vec2(0.0f, 1.0f);

  for(int i = 0; i < sRenderer2DLimits.MaxTextures; i ++)
  {
    sampler[i] = i;
  }

  GLCall(glUniform1iv(uni, sRenderer2DLimits.MaxTextures, sampler));
  sBoundedTextureIdx = 0;

  sQuads.resize(sRenderer2DLimits.MaxVertices);
  sNumVerts = 0;
  sBoundedTextureIdx = 0;
  sNumQuadCount = 0;
}

void Renderer2D::beginScene(const std::shared_ptr<OrthCamera>& crpCamera)
{
  // TODO add camera stuff to have views
  initBatch();
  sViewProjection = crpCamera->getViewProjectionMatrix();
  sCameraView = crpCamera;
}

void Renderer2D::registerQuad(const glm::vec2& crPos, const glm::vec2& crSize,
                              std::array<Vertex, sNumQuadVerts>& rVertexes,
                              const lg::Color& crColor,
                              const bool cGeometryNeedUpdate)
{
  if(sNumVerts >= sRenderer2DLimits.MaxVertices)
  {
    nextBatch();
  }

  if(sCameraView->geometryNeedUpdate() || cGeometryNeedUpdate)
  {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(round(crPos), 0.0f)) * /*rotation*/ glm::scale(glm::mat4(1.0f),
                                       {crSize.x, crSize.y, 1.0f});
    // Setting default color to purple, so if something bad happens when rendering it's in your face
    for(int i = 0; i < sNumQuadVerts; i ++)
    {
      sQuads[sNumVerts].Pos = sViewProjection * transform * sQuadVertexes[i];
      sQuads[sNumVerts].Rgba = crColor;
      sQuads[sNumVerts].TextCoord = TextCoords[i];
      sQuads[sNumVerts].TextureIndex = -1;
      rVertexes[i] = sQuads[sNumVerts];

      sNumVerts ++;
    }
  }
  else
  {
    for(int i = 0; i < sNumQuadVerts; i ++)
    {
      rVertexes[i].TextureIndex = -1;
      sQuads[sNumVerts] = rVertexes[i];

      sNumVerts ++;
    }
  }


  sNumQuadCount ++;
}

void Renderer2D::registerQuad(const glm::vec2& crPos, const glm::vec2& crPrevPos, const glm::vec2& crSize,
                              std::array<Vertex, sNumQuadVerts>& rVertexes,
                              const std::shared_ptr<TextureResource>& crpTexture,
                              const bool cGeometryNeedUpdate,
                              const double cDeltaTime)
{
  if(sNumVerts >= sRenderer2DLimits.MaxVertices || sBoundedTextureIdx == sRenderer2DLimits.MaxTextures)
  {
    nextBatch();
  }

  if(!crpTexture->isBounded())
  {
    // Update this code
    sTextureCache[sBoundedTextureIdx] = crpTexture;
    sTextureCache[sBoundedTextureIdx]->bind(sBoundedTextureIdx);
    sBoundedTextureIdx ++;
  }

  if(sCameraView->geometryNeedUpdate() || cGeometryNeedUpdate)
  {
    // currentState * alpha + 
    //         previousState * ( 1.0 - alpha );

    glm::vec2 temp = lg::Math::lerp(crPrevPos, crPos, (float)cDeltaTime);
    // rotation  glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3{0.0, 0.0, 1.0}) *
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(round(temp), 0.0f)) * glm::scale(glm::mat4(1.0f),
                                        {crSize.x, crSize.y, 1.0f});

    // Setting default color to purple, so if something bad happens when rendering it's in your face
    for(int i = 0; i < sNumQuadVerts; i ++)
    {
      sQuads[sNumVerts].Pos = sViewProjection * transform * sQuadVertexes[i];
      sQuads[sNumVerts].Rgba = lg::Purple;
      sQuads[sNumVerts].TextCoord = rVertexes[i].TextCoord;
      sQuads[sNumVerts].TextureIndex = crpTexture->getCacheId();
      rVertexes[i] = sQuads[sNumVerts];

      sNumVerts ++;
    }
  }
  else
  {
    for(int i = 0; i < sNumQuadVerts; i ++)
    {
      rVertexes[i].TextureIndex = crpTexture->getCacheId();
      sQuads[sNumVerts] = rVertexes[i];

      sNumVerts ++;
    }
  }

  sNumQuadCount ++;
}

void Renderer2D::registerQuad(const glm::vec2& crPos, const glm::vec2& crSize,
                              std::array<Vertex, sNumQuadVerts>& rVertexes,
                              const std::shared_ptr<TextureResource>& crpTexture,
                              const bool cGeometryNeedUpdate)
{
  if(sNumVerts >= sRenderer2DLimits.MaxVertices || sBoundedTextureIdx == sRenderer2DLimits.MaxTextures)
  {
    nextBatch();
  }

  if(!crpTexture->isBounded())
  {
    // Update this code
    sTextureCache[sBoundedTextureIdx] = crpTexture;
    sTextureCache[sBoundedTextureIdx]->bind(sBoundedTextureIdx);
    sBoundedTextureIdx ++;
  }

  if(sCameraView->geometryNeedUpdate() || cGeometryNeedUpdate)
  {
    // rotation  glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3{0.0, 0.0, 1.0}) *
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(round(crPos), 0.0f)) * glm::scale(glm::mat4(1.0f),
                                        {crSize.x, crSize.y, 1.0f});

    // Setting default color to purple, so if something bad happens when rendering it's in your face
    for(int i = 0; i < sNumQuadVerts; i ++)
    {
      sQuads[sNumVerts].Pos = sViewProjection * transform * sQuadVertexes[i];
      sQuads[sNumVerts].Rgba = lg::Purple;
      sQuads[sNumVerts].TextCoord = rVertexes[i].TextCoord;
      sQuads[sNumVerts].TextureIndex = crpTexture->getCacheId();
      rVertexes[i] = sQuads[sNumVerts];

      sNumVerts ++;
    }
  }
  else
  {
    for(int i = 0; i < sNumQuadVerts; i ++)
    {
      rVertexes[i].TextureIndex = crpTexture->getCacheId();
      sQuads[sNumVerts] = rVertexes[i];

      sNumVerts ++;
    }
  }

  sNumQuadCount ++;
}

void Renderer2D::endScene()
{
  flush();
  sCameraView->unsetUpdateFlag();
}

void Renderer2D::initBatch()
{
  sNumVerts = 0;
  sNumQuadCount = 0;

  if(sBoundedTextureIdx == sRenderer2DLimits.MaxTextures)
  {
    sBoundedTextureIdx = 0;

    for(auto& textures : sTextureCache)
    {
      textures.second->unbind();
    }
  }
}

void Renderer2D::nextBatch()
{
  flush();
  initBatch();
}

void Renderer2D::flush()
{
  // Draw stuff
  sQuadVbo->updateVboSubBuffer(0, sNumVerts * sizeof(Vertex), sQuads.data());
  GLCall(glDrawElements(GL_TRIANGLES, sNumQuadCount * 6, GL_UNSIGNED_INT, nullptr));
}

void Renderer2D::shutdown()
{
  sQuadVao.reset();
  sQuadVbo.reset();
  sQuadShader.reset();
  sTextureCache.clear();
  sQuads.clear();
}