#ifndef PNG_TEXTURE_HPP
#define PNG_TEXTURE_HPP

#include <vector>
#include <string>
#include <cstdint>

#include "color.hpp"
#include "glm/vec2.hpp"

class Image
{
  public:
    //! @brief Constructor
    //!
    //! @param[in] crPath Path to image
    Image(const std::string& crPath);

    //! @brief Default Constructor
    ~Image() = default;

    //! @brief Gets name of PNG
    //!        Note: Name has path truncated
    //!
    //! @return Name of PNG
    std::string getName() const;

    //! @brief Gets offset of image
    //!
    //! @return Offset of Image
    glm::uvec2 getOffset() const;

    //! @brief Gets Dimensions of image
    //!
    //! @return Dimensions of Image
    glm::uvec2 getDimensions() const;

    //! @brief Gets Image Data
    //!
    //! @return Image Data
    std::vector<uint8_t> getImgData() const;
  
    //! @brief Gets Format of Image
    //!
    //! @return Format of Image
    int32_t getFormat() const;
  
    //! @brief Gets Data Type of Image
    //!
    //! @return Data Type of Image
    int32_t getType() const;

    //! @brief Gets Internal Format of Image
    //!
    //! @return Internal Format of Image
    int32_t getInternalFormat() const;
    
    //! @brief Fills all non-transparent pixels with given color
    //!        Useful for loading a shape and changing it's color this is not a polygon fill algorithm, this is a meant
    //!        to be a fast fill
    //!
    //! @param[in] crColor Color to fill image with
    void fillAllColor(const lg::Color& crColor);

    //! @brief Recolors a Shape image with border, you must know the shape within the border to actually fill
    //!
    //! @param[in] crBorderColor       Color to set on border
    //! @param[in] crFillColor         Color to fill shape
    //! @param[in] crOriginalFillColor Original Color of shape to check against
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