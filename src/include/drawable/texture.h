#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>

#include "net_utility.h"

class Texture {
  public:
    Texture() = default;
    Texture(const std::string &crPath);
    void bind(const uint32_t cSlot) const;
    void unbind();
    ~Texture();
  private:
    uint32_t mTextureId;
    uint32_t mWidth;
    uint32_t mHeight;
    uint32_t mBpp;
    std::vector<uint8_t> mBuffer;
};

#endif