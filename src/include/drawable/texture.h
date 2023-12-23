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
    int8_t loadTexture(const std::string &crPath);
    void bind(const uint32_t cSlot) const;
    void unbind();

    int32_t getTextureId();
    virtual ~Texture();
  private:
    uint32_t mTextureId;
    Vector2<int32_t> mSize;
    uint32_t mBpp;
    bool mBufferGenerated;
    std::vector<uint8_t> mBuffer;
};

#endif