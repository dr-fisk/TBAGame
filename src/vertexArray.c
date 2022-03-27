#include "vertexArray.h"

/* Function:    VertexArray
   Description: Creates a VertexArray, if not on the main stack allocate
                memory otherwise your VAO will delete
   Parameters:  uint32_t - The number of Vertex Arrays to generate
   Returns:     None 
 */
VertexArray::VertexArray(uint32_t num) {
  GLCall(glGenVertexArrays(num, &vaID));
}

/* Function:    ~VertexArray
   Description: Deletes the VAO
   Parameters:  None
   Returns:     None 
 */
VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &vaID);
}

/* Function:    addBuffer
   Description: Prepares the VAO for rendering by mapping attributes
   Parameters:  VertexBuffer - The object buffer containing all vertexes
                and attributes
                VertexBufferLayout - The format of the VBO so that the VAO can
                interpret and render data accordingly
   Returns:     None 
 */
void VertexArray::addBuffer(const VertexBuffer *vb, const VertexBufferLayout &layout) {
  this->bind();
  vb->bind();

  const auto& elements = layout.getElements();
  uintptr_t offset = 0;

  for (uint32_t i = 0; i < elements.size(); i ++) {
      const auto& element = elements[i];
      GLCall(glEnableVertexAttribArray(i));
      GLCall(glVertexAttribPointer(i, element.count, element.type, false, //element.normalized, 
                            layout.getStride(), (const void *) offset));

      offset += element.count * sizeof(GLfloat);
  }
}

/* Function:    bind
   Description: Attaches VAO so that it is the element that will be drawn
                Call bind before Drawing each time
   Parameters:  None
   Returns:     None 
 */
void VertexArray::bind() const {
  GLCall(glBindVertexArray(vaID));
}

/* Function:    unbind
   Description: Unattaches VAO from elements to be drawn
                Call unbind after Drawing each time
   Parameters:  None
   Returns:     None 
 */
void VertexArray::unbind() const {
  GLCall(glBindVertexArray(0));
}