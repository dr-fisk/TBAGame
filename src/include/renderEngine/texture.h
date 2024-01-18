#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>

#include "utility/net_utility.h"
#include "glcommon.h"
#include "glm/vec2.hpp"

class Texture
{
  public:
    Texture();
    int8_t create(const uint32_t cHeight, const uint32_t cWidth, const int32_t cInternalFormat=GL_RGBA8,
                  const int32_t cFormat=GL_RGBA);
    int8_t loadTexture(void *pBuffer, const uint32_t cHeight, const uint32_t cWidth, const uint32_t cBpp);
    int8_t update(void *pBuffer, const glm::uvec2& crDimensions, const glm::uvec2& crOffset,
                  const int32_t cFormat=GL_RGBA, const int32_t cType=GL_UNSIGNED_BYTE);
    int8_t loadTexture(const std::string &crPath);
    void bind(const int32_t cSlot) const;
    void unbind();
    uint32_t getTextureId();
    uint8_t getCacheId();
    bool updateTextureIndex();
    bool isBounded();
    void unsetCacheUpdate();
    glm::uvec2 getSize();
    ~Texture();
    Texture& operator=(const Texture& rhs) = delete;
    Texture(const Texture& rhs) = delete;
  private:
    uint32_t mTextureId;
    glm::uvec2 mSize;
    uint32_t mBpp;
    bool mBufferGenerated;
    std::vector<uint8_t> mBuffer;
    mutable int8_t mCacheId;
    mutable bool mCacheUpdated;
    mutable bool mIsBounded;
};

#endif