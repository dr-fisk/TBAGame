#include "drawable/texture.h"
#include "glcommon.h"
#include "png.h"

Texture::Texture()
{
  GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &mTextureId));
  mBufferGenerated = false;
}

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

int8_t Texture::loadTexture(void *pBuffer, const uint32_t cHeight, const uint32_t cWidth, const uint32_t cBpp)
{
  if(!mBufferGenerated)
  {
    std::cout << "Buffer has not been generated for Texture ID: " << mTextureId << std::endl;
    return -1;
  }

  mBpp = cBpp;

  mBuffer.resize(mSize.y * mSize.x * sizeof(uint32_t));
  memcpy(mBuffer.data(), pBuffer, mBuffer.size());

  auto internalFormat = GL_RGBA8;
  auto format = GL_RGBA;
  GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
  GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mSize.x, mSize.y, format, GL_UNSIGNED_BYTE, mBuffer.data()));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));

  return 0;
}

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

void Texture::bind(const uint32_t cSlot) const
{
  //Can select different textures 0-31
  GLCall(glBindTextureUnit(cSlot, mTextureId));
}

void Texture::unbind()
{
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

int32_t Texture::getTextureId()
{
  return mTextureId;
}

Texture::~Texture()
{
  GLCall(glDeleteTextures(1, &mTextureId));
}