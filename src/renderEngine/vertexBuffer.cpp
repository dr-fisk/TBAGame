#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "renderEngine/vertexBuffer.hpp"

//! @brief Generates a VBO and binds the buffer for the VAO
//!
//! @param[in] cBuffSize Buffer Size to allocate memory
//! @param[in] cDrawType Draw Type to configure VBO for
//!
//! @return VertexBufferObject
VertexBuffer::VertexBuffer(const uint32_t cBuffSize, const GLenum cDrawType)
{
  GLCall(glGenBuffers(1, &mVboId));
  bind();
  GLCall(glBufferData(GL_ARRAY_BUFFER, cBuffSize, nullptr, cDrawType));
  unbind();
}

//! @brief Sets the layout of the VBO
//!
//! @param[in] crLayout Layout of VBO
//!
//! @return None
void VertexBuffer::setLayout(const VertexBufferLayout& crLayout)
{
  mLayout = crLayout;
}

//! @brief Generates a VBO and binds the buffer for the VAO
//!
//! @param[in] cIndex    Offset within VBO buffer
//! @param[in] cBuffSize Size of Data to copy
//! @param[in] pBuffer   Data to copy
//!
//! @return None
void VertexBuffer::updateVboSubBuffer(const uint32_t cIndex, const uint32_t cBuffSize, void *pBuffer)
{
  GLCall(glBufferSubData(GL_ARRAY_BUFFER, cIndex, cBuffSize, pBuffer));
}

//! @brief Deletes VertexBuffer
//!
//! @return None
VertexBuffer::~VertexBuffer()
{
  GLCall(glDeleteBuffers(1, &mVboId));
}

//! @brief Attaches VBO so that it is the element that will be drawn
//!        Use addBuffer in VAO to bind VBO do not call on it's own unless not using VAO
//!
//!@return None
void VertexBuffer::bind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, mVboId));
}

//! @brief Unbinds the VBO when no longer in use
//!        Call after drawing
//!
//! @return None
void VertexBuffer::unbind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}