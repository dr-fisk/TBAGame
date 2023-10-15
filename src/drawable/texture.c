#include "drawable/texture.h"
#include "glcommon.h"
#include "png.h"

// All this needs to be more dynamic
Texture::Texture(const std::string &crPath)
{
  mTextureId = 0;

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

  GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &mTextureId));
  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, mBuffer.data()));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::bind(const uint32_t cSlot) const
{
  //Can select different textures 0-31
  // GLCall(glActiveTexture(GL_TEXTURE0 + cSlot));
  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
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