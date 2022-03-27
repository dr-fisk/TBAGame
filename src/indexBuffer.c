#include "indexBuffer.h"

/* Function:    IndexBuffer
   Description: Creates IndexBuffer as an Element Array Buffer
   Parameters:  uint32_t* - Indeces describing VBO
                uint32_t  - Size of array
   Returns:     None 
 */
IndexBuffer::IndexBuffer(const uint32_t *data, uint32_t count) : count(count) {
  GLCall(glGenBuffers(1, &indexID));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));
}

/* Function:    ~IndexBuffer
   Description: Destroys IndexBuffer
   Parameters:  None
   Returns:     None 
 */
IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &indexID);
}

/* Function:    bind
   Description: Prepares IBO to be rendered
                Always call before drawing
   Parameters:  None
   Returns:     None 
 */
void IndexBuffer::bind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID));
}

/* Function:    unbind
   Description: Cleans up IBO after being drawn
   Parameters:  None
   Returns:     None 
 */
void IndexBuffer::unbind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}