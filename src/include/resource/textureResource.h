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
    int8_t bind(uint32_t cActiveSlot);
    Vector2<uint32_t> getSize();
    ~TextureResource();
  private:
    Texture* mpTexture;
};

#endif