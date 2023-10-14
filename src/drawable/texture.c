#include "drawable/texture.h"
#include "glcommon.h"
#include "png.h"

// All this needs to be more dynamic
Texture::Texture(const std::string &crPath)
{
  mId = 0;

  Png::IHDR ihdr;
  Png png(crPath);
  mBuffer = png.getImgData();
  ihdr = png.getIhdr();

  mWidth = ihdr.width;
  mHeight = ihdr.height;
  mBpp = ihdr.bitDepth;

  GLCall(glGenTextures(1, &mId));
  GLCall(glBindTexture(GL_TEXTURE_2D, mId));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mBuffer.data()));
  GLCall(glActiveTexture(GL_TEXTURE0));
  GLCall(glBindTextureUnit(0, mId));
}

void Texture::bind(const uint32_t cId, const uint32_t cSlot)
{
  //Can select different textures 0-31
  GLCall(glActiveTexture(GL_TEXTURE0 + cSlot));
  GLCall(glBindTextureUnit(0, mId));
}

void Texture::unbind()
{
  GLCall(glBindTextureUnit(GL_TEXTURE_2D, 0));
}

Texture::~Texture()
{
  glDeleteTextures(1, &mId);
}