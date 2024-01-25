#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <cstdint>
#include <memory>

#include "renderEngine/renderEngine.hpp"
#include "resource/textureResource.hpp"
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