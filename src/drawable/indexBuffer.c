#include "drawable/indexBuffer.h"


const uint8_t SQUARE_VERTICES2D = 4;

/* Function:    IndexBuffer
   Description: Creates IndexBuffer as an Element Array Buffer
   Parameters:  uint32_t - Number of Index Buffer Objects to generate
                uint32_t* - Indeces describing VBO
                uint32_t  - Size of array
   Returns:     None
 */
void IndexBuffer::genIboBuffer(const uint32_t cSizeInBytes, const GLenum cDrawType)
{
  mBuffer.clear();
  mBuffer.resize(cSizeInBytes / sizeof(uint32_t));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, mBuffer.size() * sizeof(uint32_t), mBuffer.data(), cDrawType));
}

void IndexBuffer::genIbo()
{
  GLCall(glGenBuffers(1, &mIboId));
}

/* Function:    ~IndexBuffer
   Description: Deletes IndexBuffer
   Parameters:  None
   Returns:     None
 */
IndexBuffer::~IndexBuffer()
{
  GLCall(glDeleteBuffers(1, &mIboId));
}

/* Function:    bind
   Description: Prepares IBO to be rendered
                Always call before drawing
   Parameters:  uint32_t - Specific Index Buffer Object to be bounded
   Returns:     None
 */
void IndexBuffer::bind() const
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIboId));
}

/* Function:    unbind
   Description: Cleans up IBO after being drawn
   Parameters:  None
   Returns:     None
 */
void IndexBuffer::unbind() const
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}


void IndexBuffer::updateIboSubBuffer(const uint32_t cIndex, const uint32_t cBuffSize, void *pBuffer)
{
  //TODO: Fix
  mCount = cBuffSize;
  GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, cIndex, cBuffSize, pBuffer));
}

void IndexBuffer::updateIndexBuffer(const uint64_t cNumVertexes)
{
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
  mCount = (cNumVertexes + 1) * 6;
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

  updateIboSubBuffer(0, mCount * sizeof(uint32_t), mBuffer.data());
}