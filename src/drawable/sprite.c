#include <iostream>

#include "drawable/sprite.h"
#include "resource/image.h"
#include "utility/vertexUtility.h"

Sprite::Sprite(const std::string& crPath, std::shared_ptr<RenderEngine>& prRenderEngine,
               std::shared_ptr<BatchBuffer>& prBatch, const float cTop, const float cLeft,
               const float cHeight, const float cWidth) : Drawable(prBatch)
{
  Image temp(crPath);
  std::cout << temp.getDimensions();
  mTexture = std::make_shared<TextureResource>(temp.getName(), prRenderEngine, temp.getDimensions(),
                                               temp.getInternalFormat());

  mColor = lg::Transparent;
  mPos.x = cLeft;
  mPos.y = cTop;
  mDimensions.x = cWidth;
  mDimensions.y = cHeight;

  mTexture->update(temp.getImgData().data(), temp.getDimensions(), temp.getOffset(), temp.getFormat(), temp.getType());
  VertexUtility::createVertex(mVertex, mPos, mDimensions, mColor, mTexture->getCacheId());
  VertexUtility::updateTextureCoordinates(mVertex, temp.getDimensions(), temp.getOffset(),
                                          mTexture->getSize());
}

Sprite::Sprite(std::shared_ptr<BatchBuffer>& prBatch, const float cTop, const float cLeft, const float cHeight,
               const float cWidth, const lg::Color& crColor)
: Drawable(prBatch)
{
  mColor = crColor;
  mPos.x = cLeft;
  mPos.y = cTop;
  mDimensions.x = cWidth;
  mDimensions.y = cHeight;
  Vector2<float> offset(0.0f, 0.0f);
  VertexUtility::createVertex(mVertex, mPos, mDimensions, mColor, -1.0f);
  VertexUtility::updateTextureCoordinates(mVertex, mDimensions, offset, mDimensions);
}

std::shared_ptr<TextureResource> Sprite::getResource()
{
  return mTexture;
}

bool Sprite::needUpdate()
{
  return false;
}

void Sprite::getVertex(std::vector<Vertex>& rBatchVertexes, uint32_t& rVertexIdx)
{
  if(mNeedUpdate)
  {
    VertexUtility::updateVertex(mVertex, mPos, mDimensions);
  }

  if(nullptr != mTexture && mTexture->updateTextureIndex())
  {
    VertexUtility::setVertexTextureIndex(mVertex, static_cast<float>(mTexture->getCacheId()));
  }

  rBatchVertexes[rVertexIdx] = mVertex;
  rVertexIdx ++;
}

bool Sprite::hasResource()
{
  return (nullptr != mTexture);
}

bool Sprite::textureBounded()
{
  return mTexture->isBounded();
}

void Sprite::movePos(float cX, float cY)
{
  mPos.x += cX;
  mPos.y += cY;

  mNeedUpdate = true;
}