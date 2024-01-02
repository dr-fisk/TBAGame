#include <iostream>

#include "renderEngine/batchBuffer.h"
#include "utility/vertexUtility.h"

const std::string MAIN_SHADER = "./shaders/shader1.txt";

//! @brief Construct Batch Buffer Object to handle batch rendering
//!
//! @param[in] cNumVao      Number of VAOs to generate
//! @param[in] cNumVbo      Number of VBOs to generate
//! @param[in] cNumIbo      Number of IBOs to generate
//! @param[in] cNumShaders  Number of Shaders to generate
//!
//! @return BatchBuffer Object
BatchBuffer::BatchBuffer(const uint32_t cNumVao, const uint32_t cNumVbo, const uint32_t cNumIbo,
                         const uint32_t cNumShaders)
{
  // initBatchBuffer(cNumVao, cNumVbo, cNumIbo, crRendData, cDrawType);
  // mPrimitiveType = cShape;
  mShader.resize(cNumShaders);
  mVbo.resize(cNumVbo);
  mVao.resize(cNumVao);
  mIbo.resize(cNumIbo);
  mRenderIdCount = 0;
  initBuffers();
  mBoundedTextureIdx = 0;
  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &mMaxTextureUnits);
}

//! @brief Registers drawable to batch render
//!
//! @param[in] pDrawable  Drawable Object to register
//! @param[in] cTextureId Texture ID useful for sorting map via Textures
//!
//! @return None
void BatchBuffer::registerDrawable(Drawable *pDrawable, const uint32_t cTextureId)
{
  mRenderIdCount ++;
  if(0 == mRenderIdCount)
  {
    mRenderIdCount ++;
  }

  mQuads[std::pair(cTextureId, mRenderIdCount)] = pDrawable;
  pDrawable->setRenderId(mRenderIdCount);
}

//! @brief Registers drawable to batch render
//!
//! @param[in] pDrawable Drawable Object to register
//!
//! @return None
void BatchBuffer::unregisterDrawable(const uint64_t cId, const uint32_t cTextureId)
{
  mQuads.erase(std::pair(cTextureId, cId));
}

//! @brief Updates all Buffer Object items to incorporate any updates made to registered drawables
//! TODO: Fix this function it is not correct and unfinished
//!
//! @param[in] cVboId VBO ID to store vertex data in
//! @param[in] cIboId IBO ID to store indices data TODO: Determine if necessary, I doubt this is needed
//!
//! @return None
void BatchBuffer::render(const uint32_t cVboId, const uint32_t cIboId, const std::shared_ptr<RenderTarget> &crpTarget)
{
  uint32_t numVertexes = 0;
  uint32_t offset = 0;
  uint32_t currentQuad = 0;
  crpTarget->clear();
  for(auto drawable : mQuads)
  {
    if(drawable.second->hasResource() && !drawable.second->textureBounded())
    {
      if(mMaxTextureUnits > mTextureCache.size())
      {
        mTextureCache[mBoundedTextureIdx] = drawable.second->getResource();
        mTextureCache[mBoundedTextureIdx]->bind(mBoundedTextureIdx);
        mBoundedTextureIdx ++;
      }
      else
      {
        mTextureCache[mBoundedTextureIdx]->unbind();
        mTextureCache[mBoundedTextureIdx] = drawable.second->getResource();
        mTextureCache[mBoundedTextureIdx]->bind(mBoundedTextureIdx);
        mBoundedTextureIdx ++;
      }
    }
    
    drawable.second->getVertex(mVertexes, numVertexes);

    if (mMaxTextureUnits == mBoundedTextureIdx)
    {
      mVbo.at(cVboId)->updateVboSubBuffer(offset * sizeof(Vertex),
                                          numVertexes * sizeof(Vertex),
                                          mVertexes.data());
      offset += numVertexes;
      crpTarget->draw(numVertexes * 6);
      mBoundedTextureIdx = 0;
      numVertexes = 0;
    }
  }

  // Group up to max active texture vertexes to update. This limits the amount of updates we need to make per frame
  // allowing us to increase performance
  // Some bugs here, and there are a few more optimizations I'd love to do
  if (0 != numVertexes)
  {
    mVbo.at(cVboId)->updateVboSubBuffer(offset * sizeof(Vertex),
                                        numVertexes * sizeof(Vertex),
                                        mVertexes.data());
    crpTarget->draw(numVertexes * 6);
  }

  for(auto& texture : mTextureCache)
  {
    texture.second->unsetCacheUpdate();
  }

  GLCall(glfwPollEvents());

  // Need to update the below thing cuz this ain't good
  // mIbo.at(cIboId)->updateIboSubBuffer(0, numVertexes * 6, nullptr);
}

//! @brief Init Buffers to default states
//!
//! @return None
void BatchBuffer::initBuffers()
{
  for(auto &ibo : mIbo)
  {
    ibo = std::make_shared<IndexBuffer>();
    ibo->genIbo();
  }

  for(auto &vbo : mVbo)
  {
    vbo = std::make_shared<VertexBuffer>();
    vbo->genVbo();
  }

  for(auto &vao : mVao)
  {
    vao = std::make_shared<VertexArray>();
    vao->genVao();
  }
}

//! @brief Generates IBO internal Buffer
//!
//! @param[in] cId          ID of IBO to generate buffer for
//! @param[in] cNumVertexes Number of Vertexes to generate indices for
//! @param[in] cDrawType    Draw Type to configure IBO with correct settings
//!
//! @return None
void BatchBuffer::genIboBuffer(const uint32_t cId, const uint32_t cNumVertexes, const GLenum cDrawType)
{
  mIbo.at(cId)->genIboBuffer(cNumVertexes, cDrawType);
}

//! @brief Generates VBO internal Buffer
//!
//! @param[in] cId          ID of VBO to generate buffer for
//! @param[in] cNumVertexes Number of Vertexes to generate right buffer size
//! @param[in] cDrawType    Draw Type to configure VBO with correct settings
//!
//! @return None
void BatchBuffer::genVboBuffer(const uint32_t cId, const uint32_t cNumVertexes, const GLenum cDrawType)
{
  mVertexes.resize(cNumVertexes);
  mVbo.at(cId)->genVboBuffer(cNumVertexes, cDrawType);
}

//! @brief Updates IBO Buffer
//!
//! @param[in] cId       ID of IBO to update
//! @param[in] cIndex    Index offset to update buffer from
//! @param[in] cBuffSize Size of buffer that we will copy data from
//! @param[in] pBuffer   Buffer data to copy from
//!
//! @return None
void BatchBuffer::updateIboSubBuffer(const uint32_t cId, const uint32_t cIndex, const uint32_t cBuffSize,
                                     void *pBuffer)
{
  mIbo.at(cId)->updateIboSubBuffer(cIndex, cBuffSize, pBuffer);
}

//! @brief Updates VBO Buffer
//!
//! @param[in] cId       ID of VBO to update
//! @param[in] cIndex    Index offset to update buffer from
//! @param[in] cBuffSize Size of buffer that we will copy data from
//! @param[in] pBuffer   Buffer data to copy from
//!
//! @return None
void BatchBuffer::updateVboSubBuffer(const uint32_t cId, const uint32_t cIndex, const uint32_t cBuffSize,
                                     void *pBuffer)
{
  mVbo.at(cId)->updateVboSubBuffer(cIndex, cBuffSize, pBuffer);
}

//! @brief Initializes shader using shader program from path
//!
//! @param[in] cId    ID of Shader to initialize
//! @param[in] crPath Path to Shader program
//!
//! @return None
void BatchBuffer::initShader(const uint32_t cId, const std::string& crPath)
{
  mShader.at(cId) = std::make_shared<Shader>(MAIN_SHADER);
}

//! @brief Binds Shader
//!
//! @param[in] cId ID of Shader to bind
//!
//! @return None
void BatchBuffer::bindShader(const uint32_t cId)
{
    mShader.at(cId)->bind();
}

//! @brief Binds VBO
//!
//! @param[in] cId ID of VBO to bind
//!
//! @return None
void BatchBuffer::bindVbo(const uint32_t cId)
{
  mVbo.at(cId)->bind();
}

//! @brief Binds IBO
//!
//! @param[in] cId ID of IBO to bind
//!
//! @return None
void BatchBuffer::bindIbo(const uint32_t cId)
{
  mIbo.at(cId)->bind();
}

//! @brief Binds VAO
//!
//! @param[in] cId ID of VAO to bind
//!
//! @return None
void BatchBuffer::bindVao(const uint32_t cId)
{
  mVao.at(cId)->bind();
}

//! @brief Sets attributes in VAO to decode VBO
//!
//! @param[in] cId      ID of VAO to update
//! @param[in] crLayout Layout of VBO
//!
//! @return None
void BatchBuffer::setVaoAttributes(const uint32_t cId, const VertexBufferLayout& crLayout)
{
  mVao.at(cId)->setVaoAttributes(crLayout);
}

//! @brief Gets the number of indices active in IBO
//!
//! @param[in] cId ID of IBO to get indices count from
//!
//! @return Indices count
uint32_t BatchBuffer::getIndicesCount(const uint32_t cId)
{
  return mIbo.at(cId)->getCount();
}

//! @brief Gets uniform name
//!
//! @param[in] cId       ID of Shader to get uniform from
//! @param[in] crUniform Uniform name to get
//!
//! @return Uniform ID
int32_t BatchBuffer::getUniform(const uint32_t cId, const std::string& crUniform)
{
  return mShader.at(cId)->getUniform(crUniform);
}

//! @brief Gets Max Texture Units supported
//!
//! @return Max Texture Units
int32_t BatchBuffer::getMaxTextureUnits()
{
  return mMaxTextureUnits;
}