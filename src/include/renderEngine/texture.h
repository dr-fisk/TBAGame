#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>

#include "utility/net_utility.h"
#include "Vector.h"

class Texture
{
  public:
    Texture();
    int8_t create(const uint32_t cHeight, const uint32_t cWidth);
    int8_t loadTexture(void *pBuffer, const uint32_t cHeight, const uint32_t cWidth, const uint32_t cBpp);
    int8_t update(void *pBuffer, const Vector2<uint32_t>& crDimensions, const Vector2<uint32_t>& crOffset);
    int8_t loadTexture(const std::string &crPath);
    void bind(const int32_t cSlot) const;
    void unbind();
    uint32_t getTextureId();
    uint8_t getCacheId();
    bool updateTextureIndex();
    bool isBounded();
    void unsetCacheUpdate();
    Vector2<uint32_t> getSize();
    ~Texture();
    Texture& operator=(const Texture& rhs) = delete;
    Texture(const Texture& rhs) = delete;
  private:
    uint32_t mTextureId;
    Vector2<uint32_t> mSize;
    uint32_t mBpp;
    bool mBufferGenerated;
    std::vector<uint8_t> mBuffer;
    mutable int8_t mCacheId;
    mutable bool mCacheUpdated;
    mutable bool mIsBounded;
};

#endif