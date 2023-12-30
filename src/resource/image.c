#include <iostream>

#include "resource/image.h"
#include "png.h"
#include "glcommon.h"

//! @brief Constructs Image Object
//!
//! @param crPath Path of Image to load 
//!
//! @return Image Object
Image::Image(const std::string& crPath)
{
  Png::IHDR ihdr;
  Png png(crPath);
  mPixelData = png.getImgData();
  ihdr = png.getIhdr();
  mDimensions = Vector2<uint32_t>(ihdr.width, ihdr.height);
  mOffset = Vector2<uint32_t>(0, 0);

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
Vector2<uint32_t> Image::getOffset()
{
  return mOffset;
}

//! @brief Gets Dimensions of image
//!
//! @return Dimensions of Image
Vector2<uint32_t> Image::getDimensions()
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