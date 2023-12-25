#ifndef PNG_TEXTURE_H
#define PNG_TEXTURE_H

#include <vector>
#include <string>

#include "utility/net_utility.h"
#include "Vector.h"
#include "renderEngine/texture.h"
#include "png.h"

class Image
{
  public:
    Image(const std::string& crPath);
    ~Image() = default;
  private:
    std::vector<uint8_t> mPixelData;
    Vector2<int32_t> mDimensions;
};

#endif