#include "glcommon.hpp"
#include "renderEngine/vertexArray.hpp"

//! @brief Generates Vertex Array Object
//!
//! @return Vertex Array Objet
VertexArray::VertexArray()
{
  mVertexBufferIndex = 0;
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

//! @brief Adds VBO to VAO
//!
//! @param crpVbo VBO to add
//!
//! @return None
void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& crpVbo)
{
  const auto& elements = crpVbo->getLayout().getElements();
  uintptr_t offset = 0;

  bind();
  crpVbo->bind();

  for(uint32_t i = 0; i < elements.size(); i ++)
  {
      const auto& element = elements[i];
      GLCall(glEnableVertexAttribArray(mVertexBufferIndex));

      GLCall(glVertexAttribPointer(mVertexBufferIndex, element.count, element.type, element.normalized, 
                                   crpVbo->getLayout().getStride(), (const void *) offset));

      offset += element.count * VertexBufferLayout::getElementSize(element.type);
      mVertexBufferIndex ++;
  }

  mVertexBuffers.push_back(crpVbo);
}

//! @brief Sets the Index Buffer to VAO
//!
//! @param crpIbo IBO to set
//!
//! @return None
void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& crpIbo)
{
  bind();
  crpIbo->bind();
  mpIndexBuffer = crpIbo;
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