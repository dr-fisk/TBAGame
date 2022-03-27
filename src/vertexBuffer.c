#include "vertexBuffer.h"

/* Function:     VertexBuffer
   Description: Generates a VBO and binds the buffer for the VAO
   Parameters:  void* - The data in array format to attach to VBO
                size  - The size of data array
   Returns:     None
 */
VertexBuffer::VertexBuffer(const void *data, uint32_t size) {
  GLCall(glGenBuffers(1, &bufID));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufID));
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

/* Function:    ~VertexBuffer
   Description: Deletes the buffer when VBO not needed anymore
   Parameters:  None
   Returns:     None 
 */
VertexBuffer::~VertexBuffer() {
  GLCall(glDeleteBuffers(1, &bufID));
}

/* Function:    bind
   Description: Attaches VBO so that it is the element that will be drawn
                Use addBuffer in VAO to bind VBO do not call on it's own
                unless not using VAO
   Parameters:  None
   Returns:     None 
 */
void VertexBuffer::bind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufID));
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