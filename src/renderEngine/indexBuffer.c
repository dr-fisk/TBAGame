#include "renderEngine/indexBuffer.h"


const uint8_t SQUARE_VERTICES2D = 4;
const uint8_t NUM_INDICES_PER_VERTEX = 6;

//! @brief Creates IndexBuffer as an Element Array Buffer
//!
//! @param[in]  cNumVertexes Number of Index Buffer Objects to generate
//! @param[in]  cDrawType    Indeces describing VBO
//!
//! @return None
void IndexBuffer::genIboBuffer(const uint32_t cNumVertexes, const GLenum cDrawType)
{
  mBuffer.clear();
  mBuffer.resize(cNumVertexes * NUM_INDICES_PER_VERTEX);
  mBuffer[0] = 0;
  mBuffer[1] = 1;
  mBuffer[2] = 2;
  mBuffer[3] = 2;
  mBuffer[4] = 3;
  mBuffer[5] = 0;
  uint32_t offset = SQUARE_VERTICES2D;
  uint64_t curr_idx = 0;
  uint64_t curr_offset = 0;

  /* Squares contain 6 Vertices indexed from 0-5*/
  for(uint32_t i = 1; i < cNumVertexes; i++)
  {
    curr_idx = i * 6;
    curr_offset = offset * i;
    mBuffer[curr_idx] = (mBuffer[0] + curr_offset); 
    mBuffer[curr_idx + 1] = (mBuffer[1] + curr_offset);
    mBuffer[curr_idx + 2] = (mBuffer[2] + curr_offset);
    mBuffer[curr_idx + 3] = (mBuffer[3] + curr_offset);
    mBuffer[curr_idx + 4] = (mBuffer[4] + curr_offset);
    mBuffer[curr_idx + 5] = (mBuffer[5] + curr_offset);
  }

  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, mBuffer.size() * sizeof(uint32_t), mBuffer.data(), cDrawType));
}

//! @brief Generates IBO
//!
//! @return None
void IndexBuffer::genIbo()
{
  GLCall(glGenBuffers(1, &mIboId));
}

//! @brief Deletes IndexBuffer
//!
//! @return None
IndexBuffer::~IndexBuffer()
{
  GLCall(glDeleteBuffers(1, &mIboId));
}

//! @brief Prepares IBO to be rendered
//!        Always call before drawing
//!
//! @return None
void IndexBuffer::bind() const
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIboId));
}

//! @brief Cleans up IBO after being drawn
//!
//! @return None
void IndexBuffer::unbind() const
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}


void IndexBuffer::updateIboSubBuffer(const uint32_t cIndex, const uint32_t cBuffSize, void *pBuffer)
{
  //TODO: Fix
  mCount = cBuffSize;
  // GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, cIndex, cBuffSize, pBuffer));
}