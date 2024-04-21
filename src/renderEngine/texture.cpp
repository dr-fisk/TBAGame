#include <iostream>

#include "renderEngine/texture.hpp"
#include "glcommon.hpp"

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
//! @param[in] cHeight         Height of Texture
//! @param[in] cWidth          Width of Texture
//! @param[in] cInternalFormat Specifies the number of color components in the texture
//! @param[in] cFormat Specifies the number of color components in the texture
//!
//! @return 0 on successful create
//! @return -1 on failed create 
int8_t Texture::create(const uint32_t cHeight, const uint32_t cWidth, const int32_t cInternalFormat,
                       const int32_t cFormat)
{
  std::vector<uint32_t> tempBuffer(cWidth * cHeight, 0);
  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, cInternalFormat, cWidth, cHeight, 0, cFormat, GL_UNSIGNED_BYTE,
         tempBuffer.data()));
  unbind();

  if( GL_NO_ERROR != glGetError())
  {
    std::cout << "Error generating Texture buffer." << std::endl;
    return -1;
  }

  mSize = glm::uvec2(cWidth, cHeight);
  mBufferGenerated = true;

  return 0;
}

//! @brief Update specific part of Buffer from Texture
//!
//! @param[in] pBuffer      Data to place into Texture Buffer
//! @param[in] crDimensions Dimensions of Buffer Data (L x W)
//! @param[in] crOffset     Offset in Texture Buffer to store data in
//! @param[in] cFormat      Specifies the format of the pixel data
//! @param[in] cType        Specifies the data type of the pixel data
//!
//! @return 0 if data in Texture Buffer updated successfully
//! @return -1 if data in Texture Buffer updated unsuccessfully
int8_t Texture::update(void *pBuffer, const glm::uvec2& crDimensions, const glm::uvec2& crOffset,
                       const int32_t cFormat, const int32_t cType)
{
  if(!mBufferGenerated)
  {
    std::cout << "Buffer has not been generated for Texture ID: " << mTextureId << std::endl;
    return -1;
  }

  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
  GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, crOffset.x, crOffset.y, crDimensions.x, crDimensions.y, cFormat,
                         cType, pBuffer));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
  return 0;
}

//! @brief Binds Texture Resource and sets active slot
//!
//! @param[in] cSlot Specific Slot number to set active
//!
//! @return None
void Texture::bind(const int32_t cSlot) const
{
  //Can select different textures 0-31 depending on platform
  GLCall(glActiveTexture(GL_TEXTURE0 + cSlot));
  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
}

//! @brief Unbinds Texture Resource
//!
//! @return None
void Texture::unbind() const
{
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

//! @brief Gets Texture ID associated with Texture Resource
//!
//! @return Texture ID
uint32_t Texture::getTextureId() const
{
  return mTextureId;
}

//! @brief Gets Size of Texture
//!
//! @return Size of Texture in (l x w)
glm::uvec2 Texture::getSize() const
{
  return mSize;
}

bool Texture::operator==(const Texture& rhs) const
{
  return mTextureId == rhs.getTextureId();
}

//! @brief Destructs Texture Object
//!
//! @return None
Texture::~Texture()
{
  GLCall(glDeleteTextures(1, &mTextureId));
}