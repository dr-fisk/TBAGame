#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <cstdint>
#include <memory>

#include "renderEngine/texture2D.hpp"
#include "glm/vec2.hpp"

class FrameBuffer
{
  public:
    FrameBuffer();
    void genVao();
    ~FrameBuffer();
    void bind() const;
    void unbind() const;
    void invalidate(const glm::uvec2& crDimensions);
    Texture2D getTexture() const;
  private:
    uint32_t mFrameBufferId;
    uint32_t mRenderBufferId;
    Texture2D mTexture;
};

#endif