#ifndef PNG_TEXTURE_H
#define PNG_TEXTURE_H

#include <vector>
#include <string>

#include "utility/net_utility.h"
#include "color.h"
#include "glm/vec2.hpp"

class Image
{
  public:
    Image(const std::string& crPath);
    ~Image() = default;
    std::string getName();
    glm::uvec2 getOffset();
    glm::uvec2 getDimensions();
    std::vector<uint8_t> getImgData();
    int32_t getFormat();
    int32_t getType();
    int32_t getInternalFormat();
    void fillAllColor(const lg::Color& crColor);
    void recolorBorderedShape(const lg::Color& crBorderColor, const lg::Color& crFillColor,
                              const lg::Color& crOriginalFillColor);
  private:
    std::vector<uint8_t> mPixelData;
    glm::uvec2 mDimensions;
    glm::uvec2 mOffset;
    int32_t mFormat;
    int32_t mType;
    int32_t mInternalFormat;
    std::string mName;
};

#endif