#ifndef TEXTURE_RESOURCE_H
#define TEXTURE_RESOURCE_H

#include "resource/resource.h"
#include "renderEngine/texture.h"
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
    int8_t bind(int32_t cActiveSlot);
    void unbind();
    glm::uvec2 getSize();
    uint32_t getTextureId();
    uint8_t getCacheId();
    bool updateTextureIndex();
    bool isBounded();
    void unsetCacheUpdate();
    ~TextureResource();
  private:
    Texture* mpTexture;
};

#endif