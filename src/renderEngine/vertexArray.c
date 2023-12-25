#include "glcommon.h"
#include "renderEngine/vertexArray.h"

/* Function:    VertexArray
   Description: Creates a VertexArray, if not on the main stack allocate
                memory otherwise your VAO will delete
   Parameters:  uint32_t - The number of Vertex Arrays to generate
   Returns:     None
 */
void VertexArray::genVao()
{
  GLCall(glGenVertexArrays(1, &mVaoId));
}

/* Function:    ~VertexArray
   Description: Deletes VertexArray
   Parameters:  None
   Returns:     None
 */
VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &mVaoId);
}

/* Function:    setVaoAttributes
   Description: Prepares the VAO for rendering by mapping attributes
   Parameters:  VertexBufferLayout - The format of the VBO so that the VAO can interpret and render data accordingly
   Returns:     None
 */

//TODO: make switch a function
void VertexArray::setVaoAttributes(const VertexBufferLayout &crLayout)
{
  const auto& elements = crLayout.getElements();
  uintptr_t offset = 0;

  for(uint32_t i = 0; i < elements.size(); i ++)
  {
      const auto& element = elements[i];
      GLCall(glEnableVertexAttribArray(i));

      GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, 
                                   crLayout.getStride(), (const void *) offset));

      offset += element.count * VertexBufferLayout::getElementSize(element.type);
  }
}

/* Function:    bind
   Description: Attaches VAO so that it is the element that will be drawn Call bind before Drawing each time
   Parameters:  uint32_t - The Vertex Attribute Object to bind to
   Returns:     None
 */
void VertexArray::bind() const
{
  GLCall(glBindVertexArray(mVaoId));
}

/* Function:    unbind
   Description: Unattaches VAO from elements to be drawn
                Call unbind after Drawing each time
   Parameters:  None
   Returns:     None
 */
void VertexArray::unbind() const
{
  GLCall(glBindVertexArray(0));
}