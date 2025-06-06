#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "renderEngine/frameBuffer.hpp"
#include "glcommon.hpp"

//! @brief Creates a Frame Buffer Object
//!
//! @return Frame Buffer Object
FrameBuffer::FrameBuffer()
{
  glGenFramebuffers(1, &mFrameBufferId);
}

//! @brief Deletes Frame Buffer Object
//!
//! @return None
FrameBuffer::~FrameBuffer()
{
  glDeleteFramebuffers(1, &mFrameBufferId);
}

//! @brief Binds the Frame Buffer Object
//!
//! @return None
void FrameBuffer::bind() const
{
  glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId);
  // glViewport(0, 0, gView.WindowWidth, gView.WindowHeight);
}

//! @brief Unbinds the Frame Buffer Object
//!
//! @return None
void FrameBuffer::unbind() const
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//! @brief Invalidates the current FrameBuffer Object
//!
//! @param[in] crDimensions   Dimensions to set the Frame Buffer Object Color attachment
//!
//! @return None 
void FrameBuffer::invalidate(const glm::uvec2& crDimensions)
{
  bind();
  mTexture.create(crDimensions.y, crDimensions.x, GL_RGB8, GL_RGB);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture.getTextureId(), 0);
  std::cout << "Texture binded: " << mTexture.getTextureId() << std::endl;

  glGenRenderbuffers(1, &mRenderBufferId);
  glBindRenderbuffer(GL_RENDERBUFFER, mRenderBufferId);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, crDimensions.x, crDimensions.y);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRenderBufferId);

  GLenum buffers[1] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1, buffers);

  if(GL_FRAMEBUFFER_COMPLETE == glCheckFramebufferStatus(GL_FRAMEBUFFER))
  {
    std::cout << "Frame buffer complete \n";
  }
  else
  {
        std::cout << "Frame buffer not finsihed \n";

  }
  unbind();
}

//! @brief Gets the Texture attached to the Frame Buffer Object
//!
//! @return Texture Resource
Texture2D FrameBuffer::getTexture() const
{
  return mTexture;
}