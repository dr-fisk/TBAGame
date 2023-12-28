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
    void bind(const uint32_t cSlot) const;
    void unbind();
    int32_t getTextureId();
    Vector2<uint32_t> getSize();
    ~Texture();
    //temporary remove after resource manager implemented
    Texture& operator=(const Texture &rhs)
    {
      mTextureId = rhs.mTextureId;
      mSize = rhs.mSize;
      mBpp = rhs.mBpp;
      mBufferGenerated = rhs.mBufferGenerated;
      mBuffer = rhs.mBuffer;
      mBuffer.resize(rhs.mBuffer.size());
      mCacheId = rhs.mCacheId;

      int i = 0;
      for(auto element = rhs.mBuffer.begin(); element != rhs.mBuffer.end(); element ++)
      {
        mBuffer[i] = *element;
        i ++;
      }

      return *this;
    }

  private:
    uint32_t mTextureId;
    Vector2<uint32_t> mSize;
    uint32_t mBpp;
    bool mBufferGenerated;
    std::vector<uint8_t> mBuffer;
    uint32_t mCacheId;
};

#endif