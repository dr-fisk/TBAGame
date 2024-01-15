#include <iostream>

#include "renderEngine/frameBuffer.h"
#include "glcommon.h"

FrameBuffer::FrameBuffer()
{
  glGenFramebuffers(1, &mFrameBufferId);
  std::cout << "Framebuffer how\n";
}

FrameBuffer::~FrameBuffer()
{
  glDeleteFramebuffers(1, &mFrameBufferId);
}

void FrameBuffer::bind() const
{
  glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId);
}

void FrameBuffer::unbind() const
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::invalidate(const Vector2<uint32_t>& crDimensions)
{
  bind();
  mTexture.create(crDimensions.y, crDimensions.x, GL_RGBA8);
  // mTexture.bind(31);
  // glBindTexture(GL_TEXTURE_2D, mTexture.getTextureId());
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture.getTextureId(), 0);
  // glBindTexture(GL_TEXTURE_2D, 0);
  std::cout << "Texture binded: " << mTexture.getTextureId() << std::endl;

  glGenRenderbuffers(1, &mRenderBufferId);
  glBindRenderbuffer(GL_RENDERBUFFER, mRenderBufferId);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, crDimensions.x, crDimensions.y);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRenderBufferId);
  // glClearColor(0.3, 0.0, 0.0, 1.0);
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