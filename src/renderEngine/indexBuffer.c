#include <iostream>

#include "renderEngine/indexBuffer.h"


const uint8_t SQUARE_VERTICES2D = 4;
const uint8_t NUM_INDICES_PER_VERTEX = 6;

//! @brief Creates IndexBuffer as an Element Array Buffer
//!
//! @param[in]  cNumIndices Number of Indices to generate
//! @param[in]  cDrawType   Draw Type of IBO
//!
//! @return Index Buffer Object
IndexBuffer::IndexBuffer(const uint32_t cNumIndices, const GLenum cDrawType)
{
  GLCall(glGenBuffers(1, &mIboId));
  std::vector<uint32_t> temp_indices;
  temp_indices.reserve(cNumIndices);
  temp_indices.push_back(0);
  temp_indices.push_back(1);
  temp_indices.push_back(2);
  temp_indices.push_back(2);
  temp_indices.push_back(3);
  temp_indices.push_back(0);
  uint64_t curr_offset = 0;

  /* Squares contain 6 Vertices indexed from 0-5*/
  for(uint32_t i = 6; i < cNumIndices; i+=6)
  {
    curr_offset += 4;
    temp_indices.push_back(temp_indices[0] + curr_offset); 
    temp_indices.push_back(temp_indices[1] + curr_offset);
    temp_indices.push_back(temp_indices[2] + curr_offset);
    temp_indices.push_back(temp_indices[3] + curr_offset);
    temp_indices.push_back(temp_indices[4] + curr_offset);
    temp_indices.push_back(temp_indices[5] + curr_offset);
  }

  bind();
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, temp_indices.size() * sizeof(uint32_t), temp_indices.data(), cDrawType));
  unbind();
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