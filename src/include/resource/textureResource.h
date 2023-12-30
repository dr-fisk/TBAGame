#ifndef TEXTURE_RESOURCE_H
#define TEXTURE_RESOURCE_H

#include "resource/resource.h"
#include "renderEngine/texture.h"

class TextureResource : public Resource
{
  public:
    TextureResource();
    TextureResource(const std::string& crTag, std::shared_ptr<RenderEngine>& prRenderEngine,
                    const Vector2<uint32_t>& crDimensions);
    int8_t update(void *pBuffer, const Vector2<uint32_t>& crDimensions, const Vector2<uint32_t>& crOffset);
    int8_t bind(int32_t cActiveSlot);
    void unbind();
    Vector2<uint32_t> getSize();
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