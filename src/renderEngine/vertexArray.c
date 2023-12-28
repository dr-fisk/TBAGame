#include "glcommon.h"
#include "renderEngine/vertexArray.h"

//! @brief Creates a VertexArray
//!
//! @return None
void VertexArray::genVao()
{
  GLCall(glGenVertexArrays(1, &mVaoId));
}

//! @brief Deletes VertexArray
//!
//! @return None
VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &mVaoId);
}

//! @brief Prepares the VAO for rendering by mapping attributes
//!
//! @param[in] crLayout The format of the VBO so that the VAO can interpret and render data accordingly
//!
//! @return None
//TODO: make switch a function
void VertexArray::setVaoAttributes(const VertexBufferLayout& crLayout)
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

//! @brief Attaches VAO so that it is the element that will be drawn Call bind before Drawing each time
//!
//! @return None
void VertexArray::bind() const
{
  GLCall(glBindVertexArray(mVaoId));
}

//! @brief Unattaches VAO from elements to be drawn
//! Call unbind after Drawing each time
//!
//! @return None
void VertexArray::unbind() const
{
  GLCall(glBindVertexArray(0));
}