#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdint>
#include <memory>

#include "renderEngine/renderEngine.h"
#include "resource/textureResource.h"
#include "glm/vec2.hpp"

class FrameBuffer
{
  public:
    FrameBuffer();
    void genVao();
    ~FrameBuffer();
    void bind() const;
    void unbind() const;
    void invalidate(const glm::uvec2& crDimensions, std::shared_ptr<RenderEngine>& prRenderEngine);
    std::shared_ptr<TextureResource> getTexture() const;
  private:
    uint32_t mFrameBufferId;
    uint32_t mRenderBufferId;
    std::shared_ptr<TextureResource> mTexture;
};

#endif