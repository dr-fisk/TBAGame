#ifndef TEXTURE_RESOURCE_HPP
#define TEXTURE_RESOURCE_HPP

#include "resource/resource.hpp"
#include "renderEngine/texture.hpp"
#include "glm/vec2.hpp"

class TextureResource : public Resource
{
  public:
    TextureResource();
    TextureResource(const std::string& crTag, std::shared_ptr<RenderEngine>& prRenderEngine,
                    const glm::uvec2& crDimensions, const int32_t cInternalFormat=GL_RGBA8,
                    const int32_t cFormat=GL_RGBA);
    int8_t update(void *pBuffer, const glm::uvec2& crDimensions, const glm::uvec2& crOffset,
                  const int32_t cFormat=GL_RGBA, const int32_t cType=GL_UNSIGNED_BYTE);
    int8_t bind(int32_t cActiveSlot) const;
    void unbind() const;
    glm::uvec2 getSize() const;
    uint32_t getTextureId() const;
    bool operator==(const TextureResource& rhs) const;
    ~TextureResource();
  private:
    Texture* mpTexture;
};

#endif