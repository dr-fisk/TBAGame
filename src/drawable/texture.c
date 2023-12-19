#include "drawable/texture.h"
#include "glcommon.h"
#include "png.h"

Texture::Texture(const uint32_t cSlot)
{
  GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &mTextureId));
  // GLCall(glActiveTexture(GL_TEXTURE0 + cSlot));
  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
  // GLCall(glBindTextureUnit(cSlot, mTextureId));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::loadTexture(void *pBuffer, const uint32_t cHeight, const uint32_t cWidth, const uint32_t cBpp)
{
  mWidth = cWidth;
  mHeight = cHeight;
  mBpp = cBpp;

  mBuffer.resize(mHeight * mWidth * sizeof(uint32_t));
  memcpy(mBuffer.data(), pBuffer, mBuffer.size());

  auto internalFormat = GL_RGBA8;
  auto format = GL_RGBA;

  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, mBuffer.data()));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::loadTexture(const std::string &crPath)
{
  Png::IHDR ihdr;
  Png png(crPath);
  // png.reverseImg();
  mBuffer = png.getImgData();
  ihdr = png.getIhdr();

  mWidth = ihdr.width;
  mHeight = ihdr.height;
  mBpp = ihdr.bitDepth;

  auto internalFormat = GL_RGBA8;
  auto format = GL_RGBA;

  if (Png::ColorType::RGBTRIP == ihdr.colorType)
  {
    internalFormat = GL_RGB8;
    format = GL_RGB;
  }

  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, mBuffer.data()));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::bind(const uint32_t cSlot) const
{
  //Can select different textures 0-31
  GLCall(glBindTextureUnit(cSlot, mTextureId));
}

void Texture::unbind()
{
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture()
{
  GLCall(glDeleteTextures(1, &mTextureId));
}