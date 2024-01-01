#include <iostream>

#include "drawable/sprite.h"
#include "resource/image.h"
#include "utility/vertexUtility.h"

//! @brief Sprite Constructor
//!
//! @param[in]  crPath         Path of image
//! @param[out] prRenderEngine Resource Manager to create Texture Resource
//! @param[out] prBatch        BatchBuffer to register drawable
//! @param[in]  cTop           Top position of Sprite
//! @param[in]  cLeft          Left Position of Sprite
//! @param[in]  cHeight        Height of Sprite
//! @param[in]  cWidth         Width of Sprite
//!
//! @return Sprite Object 
Sprite::Sprite(const std::string& crPath, std::shared_ptr<RenderEngine>& prRenderEngine,
               std::shared_ptr<BatchBuffer>& prBatch, const float cTop, const float cLeft,
               const float cHeight, const float cWidth)
{
  Image temp(crPath);
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
  registerDrawable(prBatch, mTexture->getTextureId());
}

//! @brief Sprite Constructor
//!        Use this constructor if you do not want a Texture on Sprite
//!
//! @param[out] prBatch        BatchBuffer to register drawable
//! @param[in]  cTop           Top position of Sprite
//! @param[in]  cLeft          Left Position of Sprite
//! @param[in]  cHeight        Height of Sprite
//! @param[in]  cWidth         Width of Sprite
//! @param[in]  crColor        Color of Sprite
//!
//! @return Sprite Object 
Sprite::Sprite(std::shared_ptr<BatchBuffer>& prBatch, const float cTop, const float cLeft, const float cHeight,
               const float cWidth, const lg::Color& crColor)
{
  mColor = crColor;
  mPos.x = cLeft;
  mPos.y = cTop;
  mDimensions.x = cWidth;
  mDimensions.y = cHeight;
  Vector2<float> offset(0.0f, 0.0f);
  VertexUtility::createVertex(mVertex, mPos, mDimensions, mColor, -1.0f);
  VertexUtility::updateTextureCoordinates(mVertex, mDimensions, offset, mDimensions);
  registerDrawable(prBatch, 0);
}

//! @brief Get Texture Resource for Drawable
//!
//! @return Texture Resource
std::shared_ptr<TextureResource> Sprite::getResource()
{
  return mTexture;
}

//! @brief Grab all vertexes from Sprite Object
//!        Performs all updates needed for rendering
//!
//! @param[out] rBatchVertexes Vertex list
//! @param[out] rVertexIdx     Current index in vertex list
//!
//! @return None
void Sprite::getVertex(std::vector<Vertex>& rBatchVertexes, uint32_t& rVertexIdx)
{
  if(mNeedUpdate)
  {
    VertexUtility::updateVertex(mVertex, mPos, mDimensions, mColor);
    mNeedUpdate = false;
  }

  if(nullptr != mTexture && mTexture->updateTextureIndex())
  {
    VertexUtility::setVertexTextureIndex(mVertex, static_cast<float>(mTexture->getCacheId()));
  }

  rBatchVertexes[rVertexIdx] = mVertex;
  rVertexIdx ++;
}

//! @brief Returns if Sprite has a Texture
//!
//! @return true if Sprite has a Texture false otherwise
bool Sprite::hasResource()
{
  return (nullptr != mTexture);
}

//! @brief Returns if Texture is bounded
//!
//! @return true if Texture is bounded false otherwise
bool Sprite::textureBounded()
{
  return mTexture->isBounded();
}

//! @brief Moves Position by adding x and y values
//!
//! @param[in] cX X value to add
//! @param[in] cY Y value to add
//!
//! @return None
void Sprite::movePos(const float cX, const float cY)
{
  mPos.x += cX;
  mPos.y += cY;

  mNeedUpdate = true;
}

//! @brief Sets Position
//!
//! @param[in] cLeft Left Position
//! @param[in] cTop  Top Position
//!
//! @return None
void Sprite::setPos(const float cLeft, const float cTop)
{
  mPos.x = cLeft;
  mPos.y = cTop;

  mNeedUpdate = true;
}

//! @brief Sets Color of Sprite
//!        Only useful for Sprites without Textures
//!
//! @param[in] crColor Color to set Sprite
//!
//! @return None
void Sprite::setColor(const lg::Color& crColor)
{
  mColor = crColor;
  mNeedUpdate = true;
}

//! @brief Gets the Size of Sprite
//!
//! @return Size of Sprite
Vector2<uint32_t> Sprite::getSize()
{
  return mDimensions;
}

//! @brief Returns position of Sprite
//!
//! @return Sprite Position
Vector2<float> Sprite::getPos()
{
  return mPos;
}

//! @brief Sets Sprite Size
//!
//! @param cWidth  New Width
//! @param cHeight New Height
//!
//! @return None
void Sprite::setSize(const uint32_t cWidth, const uint32_t cHeight)
{
  mDimensions.x = cWidth;
  mDimensions.y = cHeight;
  mNeedUpdate = true;
}

//! @brief Default Destructor
//!        Unregisters Sprite from Render List
//!
//! @return None
Sprite::~Sprite()
{
  if(0 != mRenderId)
  {
    uint32_t id = 0;
    if(nullptr != mTexture)
    {
      id = mTexture->getTextureId();
    }

    mpBatch->unregisterDrawable(mRenderId, id);
  }
}