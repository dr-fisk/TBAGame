#include <iostream>

#include "renderEngine/batchBuffer.h"
#include "utility/vertexUtility.h"

const std::string MAIN_SHADER = "./shaders/shader1.txt";

BatchBuffer::BatchBuffer(const uint32_t cNumVao, const uint32_t cNumVbo, const uint32_t cNumIbo,
                         const uint32_t cNumShaders, const uint32_t cNumTextures)
{
  // initBatchBuffer(cNumVao, cNumVbo, cNumIbo, crRendData, cDrawType);
  // mPrimitiveType = cShape;
  mShader.resize(cNumShaders);
  mVbo.resize(cNumVbo);
  mVao.resize(cNumVao);
  mIbo.resize(cNumIbo);
  mTexture.resize(cNumTextures);
  mRenderIdCount = 0;
  initBuffers();
}

/* Function:    createRectIndices
   Description: Creates Rect IBO data to associate with VBO
   Parameters:  uint32_t - Size of VBO
   Returns:     Vector   - Indices to construct Rect IBO
 */
std::vector<uint32_t> BatchBuffer::createRectIndices(const uint32_t cVboSize)
{
  // Probably should allocate before hand later
  std::vector<uint32_t> indices((cVboSize + 1) * 6);
  indices[0] = 0;
  indices[1] = 1;
  indices[2] = 2;
  indices[3] = 2;
  indices[4] = 3;
  indices[5] = 0;
  uint32_t offset = SQUARE_VERTICES2D;
  uint64_t curr_idx = 0;
  uint64_t curr_offset = 0;

  /* Squares contain 6 Vertices indexed from 0-5*/
  for(uint32_t i = 1; i < cVboSize; i++)
  {
    curr_idx = i * 6;
    curr_offset = offset * i;
    indices[curr_idx] = (indices[0] + curr_offset); 
    indices[curr_idx + 1] = (indices[1] + curr_offset);
    indices[curr_idx + 2] = (indices[2] + curr_offset);
    indices[curr_idx + 3] = (indices[3] + curr_offset);
    indices[curr_idx + 4] = (indices[4] + curr_offset);
    indices[curr_idx + 5] = (indices[5] + curr_offset);
  }

  return indices;
}

/* Function:    createTriIndices
   Description: Creates Triangle IBO data to associate with VBO
   Parameters:  uint32_t - Size of VBO
   Returns:     Vector   - Indeces to construct Triangle IBO
 */
std::vector<uint32_t> BatchBuffer::createTriIndices(const uint32_t cVboSize)
{
  std::vector<uint32_t> indices = {0, 1, 2};
  uint32_t offset = TRIANGLE_VERTICES2D;

  /* Triangles contain 3 vertices indexed 0-2 */
  for (int i = 1; i < cVboSize; i++)
  {
    // cache offset * i later
    indices.push_back(indices[0] + (offset * i)); 
    indices.push_back(indices[1] + (offset * i));
    indices.push_back(indices[2] + (offset * i));
  }

  return indices;
}

/* Function:    concatVertex
   Description: Concatenates render data for each drawable item into one vector
   Parameters:  Vector - List of drawable items
                Vector - Container for all render data
   Returns:     None
 */
void BatchBuffer::concatVertex(const std::vector<Drawable*> &crBufferData, std::vector<Vertex> &rData)
{
  std::vector<Vertex> temp;

  for(size_t i = 0; i < crBufferData.size(); i ++)
  {
    if (0 == i)
      rData = crBufferData[i]->getVertex();
    else
    {
      temp = crBufferData[i]->getVertex();
      rData.insert(rData.end(), temp.begin(), temp.end());
      temp.clear();
    }
  }
}

/* Function:    registerDrawable
   Description: Concatenates render data for each drawable item into one vector
   Parameters:  Vector - List of drawable items
                Vector - Container for all render data
   Returns:     None
 */
// TODO Update implementation this is in no way the final function
void BatchBuffer::registerDrawable(const uint32_t cVboId, const uint32_t cIboId, std::shared_ptr<Drawable> pDrawable)
{
  mQuads[mRenderIdCount] = pDrawable;
  pDrawable->setRenderId(mRenderIdCount);
  mRenderIdCount ++;

  // mVbo.at(cVboId)->updateVboSubBuffer(0, temp.size() * sizeof(Vertex), temp.data());
  // mIbo.at(cIboId)->updateIboSubBuffer(0, temp.size() * 6 * sizeof(uint32_t), nullptr);
}

void BatchBuffer::update(const uint32_t cVboId, const uint32_t cIboId)
{
  //Might need some updating
  std::vector<Vertex> temp;
  std::vector<Vertex> drawBuffer(32);
  int index = 0;
  int currentQuad = 0;
  for(auto &drawable : mQuads)
  {
    //Return Sprite instead of Vertex
    temp = drawable.second->getVertex();

    for(auto & vertex : temp)
    {
      if (index == 0)//drawable.second->getRenderId() != 1)
      {
        VertexUtility::setVertexTextureIndex(vertex, 0.0f);
      }
      else if (index == 1)
      {
        VertexUtility::setVertexTextureIndex(vertex, 1.0f);
      }
      else if (index == 2 || index == 4)
      {
        VertexUtility::setVertexTextureIndex(vertex, 2.0f);
      }
      else if (index == 3)
      {
        VertexUtility::setVertexTextureIndex(vertex, 3.0f);
      }
      else
      {
        VertexUtility::setVertexTextureIndex(vertex, 3.0f);
      }

      drawBuffer[index % drawBuffer.size()] = vertex;

      index ++;
    }

    currentQuad ++;

    // Group up to max active texture vertexes to update. This limits the amount of updates we need to make per frame
    // allowing us to increase performance
    // Some bugs here, and there are a few more optimizations I'd love to do
    if ((0 == index % drawBuffer.size()) || (currentQuad == mQuads.size()))
    {
      mVbo.at(cVboId)->updateVboSubBuffer((index / drawBuffer.size()) * sizeof(Vertex),
                                          (index % (drawBuffer.size() + 1)) * sizeof(Vertex),
                                          drawBuffer.data());
    }
  }

  // Need to update the below thing cuz this ain't good
  mIbo.at(cIboId)->updateIboSubBuffer(0, index * 6 * sizeof(uint32_t), nullptr);
}

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

  for(size_t i = 0; i < mTexture.size(); i++)
  {
    mTexture[i] = std::make_shared<Texture>();
  }
}

void BatchBuffer::genIboBuffer(const uint32_t cId, const uint32_t cNumVertexes, const GLenum cDrawType)
{
  mIbo.at(cId)->genIboBuffer(cNumVertexes, cDrawType);
}

void BatchBuffer::genVboBuffer(const uint32_t cId, const uint32_t cNumVertexes, const GLenum cDrawType)
{
  mVbo.at(cId)->genVboBuffer(cNumVertexes, cDrawType);
}

void BatchBuffer::updateIboSubBuffer(const uint32_t cId, const uint32_t cIndex, const uint32_t cBuffSize,
                                     void *pBuffer)
{
  mIbo.at(cId)->updateIboSubBuffer(cIndex, cBuffSize, pBuffer);
}

void BatchBuffer::updateVboSubBuffer(const uint32_t cId, const uint32_t cIndex, const uint32_t cBuffSize,
                                     void *pBuffer)
{
  mVbo.at(cId)->updateVboSubBuffer(cIndex, cBuffSize, pBuffer);
}

void BatchBuffer::initShader(const uint32_t cId, const std::string &crPath)
{
    mShader.at(cId) = std::make_shared<Shader>(MAIN_SHADER);
}

void BatchBuffer::initTexture(const uint32_t cId, const std::string &crPath)
{
    mTexture.at(cId)->loadTexture(crPath);
}

void BatchBuffer::initTexture(const uint32_t cId, void *pBuff, const uint32_t cHeight, const uint32_t cWidth,
                              const uint32_t cBpp)
{
    mTexture.at(cId)->create(30, 30);
    mTexture.at(cId)->loadTexture(pBuff, cHeight, cWidth, cBpp);
}

void BatchBuffer::bindShader(const uint32_t cId)
{
    mShader.at(cId)->bind();
}

void BatchBuffer::bindTexture(const uint32_t cId, const uint32_t cSlot)
{
    mTexture.at(cId)->bind(cSlot);
}

void BatchBuffer::bindVbo(const uint32_t cId)
{
    mVbo.at(cId)->bind();

}

void BatchBuffer::bindIbo(const uint32_t cId)
{
    mIbo.at(cId)->bind();
}

void BatchBuffer::bindVao(const uint32_t cId)
{
    mVao.at(cId)->bind();
}

void BatchBuffer::setVaoAttributes(const uint32_t cId, const VertexBufferLayout &crLayout)
{
  mVao.at(cId)->setVaoAttributes(crLayout);
}

uint32_t BatchBuffer::getIndicesCount(const uint32_t cId)
{
  return mIbo.at(cId)->getCount();
}

int32_t BatchBuffer::getUniform(const uint32_t cId, const std::string &crUniform)
{
  return mShader.at(cId)->getUniform(crUniform);
}