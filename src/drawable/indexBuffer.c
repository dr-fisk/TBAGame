#include "indexBuffer.h"

/* Function:    IndexBuffer
   Description: Creates IndexBuffer as an Element Array Buffer
   Parameters:  uint32_t* - Indeces describing VBO
                uint32_t  - Size of array
   Returns:     None
 */
IndexBuffer::IndexBuffer(const uint32_t *cpData, const uint32_t cCount) : mCount(cCount) {
  GLCall(glGenBuffers(1, &mIndexID));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexID));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, cCount * sizeof(uint32_t), cpData, GL_STATIC_DRAW));
}

/* Function:    ~IndexBuffer
   Description: Deletes IndexBuffer
   Parameters:  None
   Returns:     None
 */
IndexBuffer::~IndexBuffer() {
  GLCall(glDeleteBuffers(1, &mIndexID));
}

/* Function:    bind
   Description: Prepares IBO to be rendered
                Always call before drawing
   Parameters:  None
   Returns:     None
 */
void IndexBuffer::bind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexID));
}

/* Function:    unbind
   Description: Cleans up IBO after being drawn
   Parameters:  None
   Returns:     None
 */
void IndexBuffer::unbind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}