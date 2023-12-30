#ifndef PNG_TEXTURE_H
#define PNG_TEXTURE_H

#include <vector>
#include <string>

#include "utility/net_utility.h"
#include "Vector.h"
class Image
{
  public:
    Image(const std::string& crPath);
    ~Image() = default;
    std::string getName();
    Vector2<uint32_t> getOffset();
    Vector2<uint32_t> getDimensions();
    std::vector<uint8_t> getImgData();
    int32_t getFormat();
    int32_t getType();
    int32_t getInternalFormat();
  private:
    std::vector<uint8_t> mPixelData;
    Vector2<uint32_t> mDimensions;
    Vector2<uint32_t> mOffset;
    int32_t mFormat;
    int32_t mType;
    int32_t mInternalFormat;
    std::string mName;
};

#endif