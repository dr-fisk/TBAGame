#include "renderEngine/texture.h"
#include "glcommon.h"
#include "png.h"

//! @brief Default Constructor
//!
//! @return Texture Object
Texture::Texture()
{
  GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &mTextureId));
  mBufferGenerated = false;
}

//! @brief Creates Texture Buffer
//!
//! @param[in] cHeight Height of Texture
//! @param[in] cWidth  Width of Texture
//!
//! @return 0 on successful create
//! @return -1 on failed create 
int8_t Texture::create(const uint32_t cHeight, const uint32_t cWidth)
{
  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, cWidth, cHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
         nullptr));
  unbind();

  if( GL_NO_ERROR != glGetError())
  {
    std::cout << "Error generating Texture buffer." << std::endl;
    return -1;
  }

  mSize = Vector2<int32_t>(cWidth, cHeight);
  mBufferGenerated = true;

  return 0;
}

//! @brief Loads Texture from byte array
//!
//! @param[in] pBuffer Byte array representing Texture
//! @param[in] cHeight Height of byte array Texture
//! @param[in] cWidth  Width of byte array Texture 
//! @param[in] cBpp    TODO: Remove me
//!
//! @return 0 on successful load
//! @return -1 on failed load 
int8_t Texture::loadTexture(void *pBuffer, const uint32_t cHeight, const uint32_t cWidth, const uint32_t cBpp)
{
  if(!mBufferGenerated)
  {
    std::cout << "Buffer has not been generated for Texture ID: " << mTextureId << std::endl;
    return -1;
  }

  mBpp = cBpp;

  mBuffer.resize(cHeight * cWidth * sizeof(uint32_t));
  memcpy(mBuffer.data(), pBuffer, mBuffer.size());

  auto internalFormat = GL_RGBA8;
  auto format = GL_RGBA;
  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
  glPixelStorei(GL_UNPACK_ROW_LENGTH, cWidth);
  glPixelStorei(GL_PACK_ROW_LENGTH, cWidth);
  GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, cWidth, cHeight, format, GL_UNSIGNED_BYTE, mBuffer.data()));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));

  return 0;
}

//! @brief Loads Texture from file
//!
//! @param[in] crPath Path to file to load
//!
//! @return 0 on successful load
//! @return -1 on failed load 
int8_t Texture::loadTexture(const std::string &crPath)
{
  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
  Png::IHDR ihdr;
  Png png(crPath);
  // png.reverseImg();
  mBuffer = png.getImgData();
  ihdr = png.getIhdr();

  mBpp = ihdr.bitDepth;

  auto internalFormat = GL_RGBA8;
  auto format = GL_RGBA;

  if (Png::ColorType::RGBTRIP == ihdr.colorType)
  {
    internalFormat = GL_RGB8;
    format = GL_RGB;
  }


  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, ihdr.width, ihdr.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
         mBuffer.data()));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));

  mBufferGenerated = true;
  mSize = Vector2<int32_t>(ihdr.width, ihdr.height);
  return 0;
}

//! @brief Binds Texture Resource and sets active slot
//!
//! @param[in] cSlot Specific Slot number to set active
//!
//! @return None
void Texture::bind(const uint32_t cSlot) const
{
  //Can select different textures 0-31
  GLCall(glBindTextureUnit(cSlot, mTextureId));
}

//! @brief Unbinds Texture Resource
//!
//! @return None
void Texture::unbind()
{
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

//! @brief Gets Texture ID associated with Texture Resource
//!
//! @return     Texture ID
int32_t Texture::getTextureId()
{
  return mTextureId;
}

//! @brief Destructs Texture Object
//!
//! @return None
Texture::~Texture()
{
  GLCall(glDeleteTextures(1, &mTextureId));
}