#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdint>

#include "renderEngine/texture.h"
#include "Vector.h"

class FrameBuffer
{
  public:
    FrameBuffer();
    void genVao();
    ~FrameBuffer();
    void bind() const;
    void unbind() const;
    void invalidate(const Vector2<uint32_t>& crDimensions);
  private:
    uint32_t mFrameBufferId;
    uint32_t mRenderBufferId;
    Texture mTexture;
};

#endif