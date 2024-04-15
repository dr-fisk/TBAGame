#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "resource/image.hpp"
#include "png.hpp"
#include "glcommon.hpp"

//! @brief Constructs Image Object
//!
//! @param crPath Path of Image to load 
//!
//! @return Image Object
Image::Image(const std::string& crPath)
{
  Png::IHDR ihdr;
  Png png(crPath);
  png.reverseImg();
  mPixelData = png.getImgData();
  ihdr = png.getIhdr();
  mDimensions = glm::uvec2(ihdr.width, ihdr.height);
  mOffset = glm::uvec2(0, 0);

  mType = GL_UNSIGNED_BYTE;
  mInternalFormat = GL_RGBA8;
  mFormat = GL_RGBA;

  if (Png::ColorType::RGBTRIP == ihdr.colorType)
  {
    mInternalFormat = GL_RGB8;
    mFormat = GL_RGB;
  }

  const char EXTENSION[] = ".png";
  int32_t temp2 = -1;

  if(std::string::npos != crPath.find_last_of("/"))
  {
    temp2 = crPath.find_last_of("/");
  }

  temp2 ++;
  mName = crPath.substr(temp2, crPath.size() - ((sizeof(EXTENSION) - 1) + temp2));
}

//! @brief Gets name of PNG
//!        Note: Name has path truncated
//!
//! @return Name of PNG
std::string Image::getName()
{
  return mName;
}

//! @brief Gets offset of image
//!
//! @return Offset of Image
glm::uvec2 Image::getOffset()
{
  return mOffset;
}

//! @brief Gets Dimensions of image
//!
//! @return Dimensions of Image
glm::uvec2 Image::getDimensions()
{
  return mDimensions;
}

//! @brief Gets Image Data
//!
//! @return Image Data
std::vector<uint8_t> Image::getImgData()
{
  return mPixelData;
}

//! @brief Gets Data Type of Image
//!
//! @return Data Type of Image
int32_t Image::getType()
{
  return mType;
}

//! @brief Gets Format of Image
//!
//! @return Format of Image
int32_t Image::getFormat()
{
  return mFormat;
}

//! @brief Gets Internal Format of Image
//!
//! @return Internal Format of Image
int32_t Image::getInternalFormat()
{
  return mInternalFormat;
}

//! @brief Fills all non-transparent pixels with given color
//!        Useful for loading a shape and changing it's color this is not a polygon fill algorithm, this is a meant
//!        to be a fast fill
//!
//! @param[in] crColor Color to fill image with
//!
//! @return None
void Image::fillAllColor(const lg::Color& crColor)
{
  int adder = mFormat == GL_RGBA ? 4 : 3;
  for(size_t i = 0; i < mPixelData.size(); i += adder)
  {
    if(GL_RGBA == mFormat)
    {
      if(0 != mPixelData[i + 3])
      {
        mPixelData[i] = crColor.getRed();
        mPixelData[i + 1] = crColor.getGreen();
        mPixelData[i + 2] = crColor.getBlue();
      }
    }
    else
    {
      mPixelData[i] = crColor.getRed();
      mPixelData[i + 1] = crColor.getGreen();
      mPixelData[i + 2] = crColor.getBlue();
    }
  }
}

//! @brief Recolors a Shape image with border, you must know the shape within the border to actually fill
//!
//! @param crBorderColor       Color to set on border
//! @param crFillColor         Color to fill shape
//! @param crOriginalFillColor Original Color of shape to check against
//!
//! @return None
void Image::recolorBorderedShape(const lg::Color& crBorderColor, const lg::Color& crFillColor,
                                 const lg::Color& crOriginalFillColor)
{
  int adder = mFormat == GL_RGBA ? 4 : 3;
  for(size_t i = 0; i < mPixelData.size(); i += adder)
  {
    if(GL_RGBA == mFormat)
    {
      if(0 != mPixelData[i + 3])
      {
        if(mPixelData[i] == crOriginalFillColor.getRed() &&
           mPixelData[i + 1] == crOriginalFillColor.getGreen() &&
           mPixelData[i + 2] == crOriginalFillColor.getBlue())
        {
          mPixelData[i] = crFillColor.getRed();
          mPixelData[i + 1] = crFillColor.getGreen();
          mPixelData[i + 2] = crFillColor.getBlue();
        }
        else
        {
          mPixelData[i] = crBorderColor.getRed();
          mPixelData[i + 1] = crBorderColor.getGreen();
          mPixelData[i + 2] = crBorderColor.getBlue();
        }
      }
    }
    else
    {
      if(0 != mPixelData[i + 3])
      {
        if(mPixelData[i] == crOriginalFillColor.getRed() &&
           mPixelData[i + 1] == crOriginalFillColor.getGreen() &&
           mPixelData[i + 2] == crOriginalFillColor.getBlue())
        {
          mPixelData[i] = crFillColor.getRed();
          mPixelData[i + 1] = crFillColor.getGreen();
          mPixelData[i + 2] = crFillColor.getBlue();
        }
        else
        {
          mPixelData[i] = crBorderColor.getRed();
          mPixelData[i + 1] = crBorderColor.getGreen();
          mPixelData[i + 2] = crBorderColor.getBlue();
        }
      }
    }
  }
}