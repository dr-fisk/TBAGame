#include "indexBuffer.h"

/* Function:    IndexBuffer
   Description: Creates IndexBuffer as an Element Array Buffer
   Parameters:  uint32_t - Number of Index Buffer Objects to generate
                uint32_t* - Indeces describing VBO
                uint32_t  - Size of array
   Returns:     None
 */
IndexBuffer::IndexBuffer(const uint32_t cNumIbo, const uint32_t *cpData, const uint32_t cCount) : mCount(cCount) {
  mIndexBuffers.resize(cNumIbo);
  GLCall(glGenBuffers(cNumIbo, mIndexBuffers.data()));
  mLastDataSize = 0;
}

/* Function:    ~IndexBuffer
   Description: Deletes IndexBuffer
   Parameters:  None
   Returns:     None
 */
IndexBuffer::~IndexBuffer() {
  GLCall(glDeleteBuffers(mIndexBuffers.size(), mIndexBuffers.data()));
}

/* Function:    bind
   Description: Prepares IBO to be rendered
                Always call before drawing
   Parameters:  uint32_t - Specific Index Buffer Object to be bounded
   Returns:     None
 */
void IndexBuffer::bind(const uint32_t cId) const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffers[cId]));
}

/* Function:    unbind
   Description: Cleans up IBO after being drawn
   Parameters:  None
   Returns:     None
 */
void IndexBuffer::unbind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

/* Function:    updateBoundedBufferData
   Description: Sets GL_ARRAY_BUFFER to use the provided buffer data
   Parameters:  void * - Index Buffer Data for bounded Vertex Buffer Object
                uint32_t - Number of Indexes
                GLenum   - The Draw Type OpenGL should use below are the type and explanation
                GL_STATIC_DRAW: Use this when your Index Buffer Object will not be modified, usually should be set during initialization only
                GL_DYNAMIC_DRAW: Use this for when your Index Buffer Object will be changing buffers
                GL_STREAM_DRWA: Use this for when Index Buffer Object will be changing consistently frame by frame
   Returns:     None
 */
void IndexBuffer::updateBoundedBufferData(const void *cpData, const uint32_t cCount, const GLenum cDrawType) {
  const uint32_t cSize = cCount * sizeof(uint32_t);
  //TODO: add ability to change draw type
  mCount = cCount;
  if (cSize > mLastDataSize) {
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, cSize, cpData, cDrawType));
    mLastDataSize = cSize;
  }
  else {
    GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, cSize, cpData));
  }
}
