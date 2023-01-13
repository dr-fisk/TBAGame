#include "vertexBuffer.h"

/* Function:     VertexBuffer
   Description: Generates a VBO and binds the buffer for the VAO
   Parameters:  void* - The data in array format to attach to VBO
                size  - The size of data array
   Returns:     None
 */
VertexBuffer::VertexBuffer(const uint32_t cNumVbo) {
  mBuffers.resize(cNumVbo);
  GLCall(glGenBuffers(cNumVbo, mBuffers.data()));
  mLastDataSize = 0;
}

/* Function:    ~VertexBuffer
   Description: Deletes VertexBuffer
   Parameters:  None
   Returns:     None
 */
VertexBuffer::~VertexBuffer() {
  GLCall(glDeleteBuffers(mBuffers.size(), mBuffers.data()));
}

/* Function:    bind
   Description: Attaches VBO so that it is the element that will be drawn
                Use addBuffer in VAO to bind VBO do not call on it's own
                unless not using VAO
   Parameters:  uint32_t - The specific Vertex Buffer Object to bind
   Returns:     None
 */
void VertexBuffer::bind(const uint32_t cId) const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, mBuffers[cId]));
}

/* Function:    updateBoundedBufferData
   Description: Sets GL_ARRAY_BUFFER to use the provided buffer data
   Parameters:  void * - Buffer data to be rendered
                uint32_t - Size of the buffer data
                GLenum   - The Draw Type OpenGL should use below are the type and explanation
                GL_STATIC_DRAW: Use this when your Vertex Buffer Object will not be modified, usually should be set during initialization only
                GL_DYNAMIC_DRAW: Use this for when your Vertex Buffer Object will be changing buffers
                GL_STREAM_DRWA: Use this for when Vertex Buffer Object will be changing consistently frame by frame
   Returns:     None
 */
void VertexBuffer::updateBoundedBufferData(const void *cpData, const uint32_t cSize, const GLenum cDrawType) {
  //TODO: add ability to change draw type
  if (cSize > mLastDataSize) {
    GLCall(glBufferData(GL_ARRAY_BUFFER, cSize, cpData, cDrawType));
    mLastDataSize = cSize;
  }
  else {
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, cSize, cpData));
  }
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