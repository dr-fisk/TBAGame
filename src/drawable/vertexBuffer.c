#include "vertexBuffer.h"

/* Function:     VertexBuffer
   Description: Generates a VBO and binds the buffer for the VAO
   Parameters:  void* - The data in array format to attach to VBO
                size  - The size of data array
   Returns:     None
 */
VertexBuffer::VertexBuffer(const void *cpData, const uint32_t cSize) {
  GLCall(glGenBuffers(1, &mBuffID));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, mBuffID));
  GLCall(glBufferData(GL_ARRAY_BUFFER, cSize, cpData, GL_STATIC_DRAW));
}

/* Function:    ~VertexBuffer
   Description: Deletes VertexBuffer
   Parameters:  None
   Returns:     None
 */
VertexBuffer::~VertexBuffer() {
  GLCall(glDeleteBuffers(1, &mBuffID));
}

/* Function:    bind
   Description: Attaches VBO so that it is the element that will be drawn
                Use addBuffer in VAO to bind VBO do not call on it's own
                unless not using VAO
   Parameters:  None
   Returns:     None
 */
void VertexBuffer::bind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, mBuffID));
}

/* Function:    unbind
   Description: Unbinds the VBO when no longer in use
                Call after drawing
   Parameters:  None
   Returns:     None
 */
void VertexBuffer::unbind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}