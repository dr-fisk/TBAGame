#include <iostream>

#include "glcommon.h"
#include "renderer/renderer2D.h"
#include "utility/vertexUtility.h"

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

static std::shared_ptr<VertexArray> sQuadVao;
static std::shared_ptr<VertexBuffer> sQuadVbo;
static std::shared_ptr<Shader> sQuadShader;
static std::map<int8_t, std::shared_ptr<TextureResource>> sTextureCache;
static int8_t sBoundedTextureIdx;
static RendererLimits sRenderer2DLimits;
static bool sLimitsDefined = false;
static std::vector<Vertex> sQuads;
static uint32_t sNumQuads;

//! @brief Initializes the Renderer2D Engine
//!
//! @return None
void Renderer2D::init()
{
  if(!sLimitsDefined)
  {
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &sRenderer2DLimits.MaxTextures);
    std::cout << "Max textures " << sRenderer2DLimits.MaxTextures << std::endl;
    sLimitsDefined = true;
  }

  sQuadVao = std::make_shared<VertexArray>();
  sQuadVao->genVao();

  sQuadVbo = std::make_shared<VertexBuffer>(sRenderer2DLimits.MaxQuads * sizeof(Vertex), GL_DYNAMIC_DRAW);
    
  // First set of Float are quad position
  // First set of Float are quad position
  // Next 2 floats are Texture Coords
  // Next float is Texture Index
  sQuadVbo->setLayout({
    {GL_FLOAT, TWO_D_COORDS, false},
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

  for(int i = 0; i < sRenderer2DLimits.MaxTextures; i ++)
  {
    sampler[i] = i;
  }

  GLCall(glUniform1iv(uni, sRenderer2DLimits.MaxTextures, sampler));
  sBoundedTextureIdx = 0;

  sQuads.resize(sRenderer2DLimits.MaxQuads);
  sNumQuads = 0;
  sBoundedTextureIdx = 0;
}

void Renderer2D::beginScene()
{
  // TODO add camera stuff to have views
  initBatch();
}

void Renderer2D::registerQuad(const Vertex& crVertex, const std::shared_ptr<TextureResource>& crpTexture)
{
  if(sNumQuads >= sRenderer2DLimits.MaxQuads || sBoundedTextureIdx == sRenderer2DLimits.MaxTextures)
  {
    nextBatch();
  }

  sQuads[sNumQuads] = crVertex;

  if(nullptr != crpTexture)
  {
    if(!crpTexture->isBounded())
    {
      // Update this code
      sTextureCache[sBoundedTextureIdx] = crpTexture;
      sTextureCache[sBoundedTextureIdx]->bind(sBoundedTextureIdx);
      sBoundedTextureIdx ++;

      std::cout << "Texture bound: " << crpTexture->getTextureId() << std::endl;
      std::cout << "Num textures bounded: " << (int) sBoundedTextureIdx << std::endl;
    }

    VertexUtility::setVertexTextureIndex(sQuads[sNumQuads], crpTexture->getCacheId());
  }

  sNumQuads++;
}

void Renderer2D::endScene()
{
  flush();
}

void Renderer2D::initBatch()
{
  sNumQuads = 0;

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
  sQuadVbo->updateVboSubBuffer(0, sNumQuads * sizeof(Vertex), sQuads.data());
  GLCall(glDrawElements(GL_TRIANGLES, sNumQuads * 6, GL_UNSIGNED_INT, nullptr));
}

void Renderer2D::shutdown()
{
  sQuadVao.reset();
  sQuadVbo.reset();
  sQuadShader.reset();
  sTextureCache.clear();
  sQuads.clear();
}