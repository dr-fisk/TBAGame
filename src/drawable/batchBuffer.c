#include <iostream>

#include "drawable/batchBuffer.h"

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

/* Function:    concatRenderData
   Description: Concatenates render data for each drawable item into one vector
   Parameters:  Vector - List of drawable items
                Vector - Container for all render data
   Returns:     None
 */
void BatchBuffer::concatRenderData(const std::vector<Drawable*> &crBufferData, std::vector<RenderData> &rData)
{
  std::vector<RenderData> temp;

  for(size_t i = 0; i < crBufferData.size(); i ++)
  {
    if (0 == i)
      rData = crBufferData[i]->getRenderData();
    else
    {
      temp = crBufferData[i]->getRenderData();
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
void BatchBuffer::registerDrawable(const uint32_t cVboId, const uint32_t cIboId, Drawable* pBufferData)
{
  std::vector<RenderData> temp = pBufferData->getRenderData();
  // int32_t NumVertices = temp.size();
  // // std::cout << "Num verts: " << mNumVertices << std::endl;
  // // std::cout << "Size of render data: " << sizeof(RenderData) << std::endl;
  // // std::cout << "data size: " << mNumVertices * sizeof(RenderData) << std::endl;
  // // std::cout << "Size vec float: " << sizeof(Vector2<GLfloat>()) << std::endl;
  // memcpy(mBuffer.data() + mNextAvailableAddress, temp.data(), 
  //        temp.size() * sizeof(RenderData));
  // mNextAvailableAddress += temp.size() * sizeof(RenderData);
  // std::cout << sizeof(RenderData) << std::endl;
  mVbo.at(cVboId)->updateVboSubBuffer(0, temp.size() * sizeof(RenderData), temp.data());
  std::vector<uint32_t> indeces = createRectIndices(temp.size());
  mIbo.at(cIboId)->updateIboSubBuffer(0, indeces.size() * sizeof(uint32_t), indeces.data());
  //   std::cout << "register done" << std::endl;
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
    mTexture.at(cId) = std::make_shared<Texture>(crPath);
}

void BatchBuffer::initTexture(const uint32_t cId, void *pBuff, const uint32_t cHeight, const uint32_t cWidth,
                              const uint32_t cBpp)
{
    mTexture.at(cId) = std::make_shared<Texture>(pBuff, cHeight, cWidth, cBpp);
}

void BatchBuffer::bindShader(const uint32_t cId)
{
    mShader.at(cId)->bind();
}

void BatchBuffer::bindTexture(const uint32_t cId)
{
    mTexture.at(cId)->bind(cId);
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