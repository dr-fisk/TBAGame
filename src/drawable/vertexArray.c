#include "vertexArray.h"

uint8_t VertexArray::smNumVao = 0;

/* Function:    VertexArray
   Description: Creates a VertexArray, if not on the main stack allocate
                memory otherwise your VAO will delete
   Parameters:  uint32_t - The number of Vertex Arrays to generate
   Returns:     None
 */
VertexArray::VertexArray(const uint32_t cNum)
{
  if ((cNum + smNumVao) <= 16)
  {
    mVertexArrays.resize(cNum);
    GLCall(glGenVertexArrays(cNum, mVertexArrays.data()));
    smNumVao += cNum;
  }
  else
  {
    std::cout << "Max number of VAOs reached, VAOs not generated. Delete VAOs to gen more." << std::endl;
  }
  
}

/* Function:    ~VertexArray
   Description: Deletes VertexArray
   Parameters:  None
   Returns:     None
 */
VertexArray::~VertexArray()
{
  smNumVao -= mVertexArrays.size();
  glDeleteVertexArrays(mVertexArrays.size(), mVertexArrays.data());
}

/* Function:    addBuffer
   Description: Prepares the VAO for rendering by mapping attributes
   Parameters:  VertexBufferLayout - The format of the VBO so that the VAO can interpret and render data accordingly
   Returns:     None
 */

//TODO: make switch a function
void VertexArray::addBuffer(const VertexBufferLayout &crLayout)
{
  const auto& elements = crLayout.getElements();
  uintptr_t offset = 0;

  for(uint32_t i = 0; i < elements.size(); i ++)
  {
      const auto& element = elements[i];
      GLCall(glEnableVertexAttribArray(i));

      GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, 
                                   crLayout.getStride(), (const void *) offset));

      offset += element.count * sizeof(GLfloat);
  }
}

/* Function:    bind
   Description: Attaches VAO so that it is the element that will be drawn Call bind before Drawing each time
   Parameters:  uint32_t - The Vertex Attribute Object to bind to
   Returns:     None
 */
void VertexArray::bind(const uint32_t cId) const
{
  GLCall(glBindVertexArray(mVertexArrays[cId]));
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