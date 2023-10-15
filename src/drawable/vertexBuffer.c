#include <iostream>

#include "drawable/vertexBuffer.h"

/* Function:     VertexBuffer
   Description: Generates a VBO and binds the buffer for the VAO
   Parameters:  void* - The data in array format to attach to VBO
                size  - The size of data array
   Returns:     None
 */
void VertexBuffer::genVboBuffer(const uint32_t cNumVertexes, const GLenum cDrawType) {
  mBuffer.clear();
  mBuffer.resize(cNumVertexes * sizeof(RenderData));
  GLCall(glBufferData(GL_ARRAY_BUFFER, mBuffer.size(), mBuffer.data(), cDrawType));
}

void VertexBuffer::updateVboSubBuffer(const uint32_t cIndex, const uint32_t cBuffSize, void *pBuffer)
{
  GLCall(glBufferSubData(GL_ARRAY_BUFFER, cIndex, cBuffSize, pBuffer));
}

void VertexBuffer::genVbo()
{
  GLCall(glGenBuffers(1, &mVboId));
}

/* Function:    ~VertexBuffer
   Description: Deletes VertexBuffer
   Parameters:  None
   Returns:     None
 */
VertexBuffer::~VertexBuffer() {
  GLCall(glDeleteBuffers(1, &mVboId));
}

/* Function:    bind
   Description: Attaches VBO so that it is the element that will be drawn
                Use addBuffer in VAO to bind VBO do not call on it's own
                unless not using VAO
   Parameters:  uint32_t - The specific Vertex Buffer Object to bind
   Returns:     None
 */
void VertexBuffer::bind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, mVboId));
}

/* Function:    unbind
   Description: Unbinds the VBO when no longer in use
                Call after drawing
   Parameters:  None
   Returns:     None
 */
void VertexBuffer::unbind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}