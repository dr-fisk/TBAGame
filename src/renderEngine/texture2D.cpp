#include <iostream>

#include "renderEngine/texture2D.hpp"
#include "glcommon.hpp"

//! @brief Default Constructor
//!
//! @return Texture2D Object
Texture2D::Texture2D()
{
  GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &mTextureId));
  std::cout << "Texture ID generated: " << mTextureId << std::endl;
  mBufferGenerated = false;
}

Texture2D::Texture2D(const Texture2D& rTexture)
{
  *this = rTexture;
}

//! @brief Creates Texture2D Buffer
//!
//! @param[in] cHeight         Height of Texture2D
//! @param[in] cWidth          Width of Texture2D
//! @param[in] cInternalFormat Specifies the number of color components in the texture
//! @param[in] cFormat Specifies the number of color components in the texture
//!
//! @return 0 on successful create
//! @return -1 on failed create 
int8_t Texture2D::create(const uint32_t cHeight, const uint32_t cWidth, const int32_t cInternalFormat,
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
    std::cout << "Error generating Texture2D buffer." << std::endl;
    return -1;
  }

  mSize = glm::uvec2(cWidth, cHeight);
  mBufferGenerated = true;

  return 0;
}

//! @brief Update specific part of Buffer from Texture2D
//!
//! @param[in] pBuffer      Data to place into Texture2D Buffer
//! @param[in] crDimensions Dimensions of Buffer Data (L x W)
//! @param[in] crOffset     Offset in Texture2D Buffer to store data in
//! @param[in] cFormat      Specifies the format of the pixel data
//! @param[in] cType        Specifies the data type of the pixel data
//!
//! @return 0 if data in Texture2D Buffer updated successfully
//! @return -1 if data in Texture2D Buffer updated unsuccessfully
int8_t Texture2D::update(void *pBuffer, const glm::uvec2& crDimensions, const glm::uvec2& crOffset,
                       const int32_t cFormat, const int32_t cType)
{
  if(!mBufferGenerated)
  {
    std::cout << "Buffer has not been generated for Texture2D ID: " << mTextureId << std::endl;
    return -1;
  }

  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
  GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, crOffset.x, crOffset.y, crDimensions.x, crDimensions.y, cFormat,
                         cType, pBuffer));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
  return 0;
}

//! @brief Binds Texture2D Resource and sets active slot
//!
//! @param[in] cSlot Specific Slot number to set active
//!
//! @return None
void Texture2D::bind(const int32_t cSlot) const
{
  //Can select different textures 0-31 depending on platform
  GLCall(glActiveTexture(GL_TEXTURE0 + cSlot));
  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
}

//! @brief Unbinds Texture2D Resource
//!
//! @return None
void Texture2D::unbind() const
{
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

//! @brief Gets Texture2D ID associated with Texture2D Resource
//!
//! @return Texture2D ID
uint32_t Texture2D::getTextureId() const
{
  return mTextureId;
}

//! @brief Gets Size of Texture2D
//!
//! @return Size of Texture2D in (l x w)
glm::uvec2 Texture2D::getSize() const
{
  return mSize;
}

void Texture2D::operator=(const Texture2D& rhs)
{
  mTextureId = rhs.mTextureId;
  mSize = rhs.mSize;
  mBpp = rhs.mBpp;
  mBufferGenerated = rhs.mBufferGenerated;
  mBuffer = rhs.mBuffer;
}

bool Texture2D::operator==(const Texture2D& rhs) const
{
  return mTextureId == rhs.getTextureId();
}

//! @brief Destructs Texture2D Object
//!
//! @return None
Texture2D::~Texture2D()
{
  std::cout << "Deleting this cunt: " << mTextureId << std::endl;
  GLCall(glDeleteTextures(1, &mTextureId));
}