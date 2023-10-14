#ifndef TEXTURE_H
#define TEXTURE_H

#include "common.h"

class Texture {
  public:
    Texture() = default;
    Texture(const std::string &crPath);
    void bind(const uint32_t cId, const uint32_t cSlot);
    void unbind();
    ~Texture();
  private:
    uint32_t mId;
    uint32_t mWidth;
    uint32_t mHeight;
    uint32_t mBpp;
    std::vector<uint8_t> mBuffer;
};

#endif