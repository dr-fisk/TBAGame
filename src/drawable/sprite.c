#include <iostream>

#include "drawable/sprite.h"
#include "resource/image.h"
#include "utility/vertexUtility.h"

//! @brief Sprite Constructor
//!
//! @param[in]  crPath         Path of image
//! @param[out] prRenderEngine Resource Manager to create Texture Resource
//! @param[out] prBatch        BatchBuffer to register drawable
//! @param[in]  crPos          Position of Sprite
//! @param[in]  crSize         Size of Sprite
//!
//! @return Sprite Object 
Sprite::Sprite(const std::string& crPath, std::shared_ptr<RenderEngine>& prRenderEngine,
               std::shared_ptr<BatchBuffer>& prBatch, const Vector2<float>& crPos, const Vector2<float>& crSize)
{
  Image temp(crPath);
  mTexture = std::make_shared<TextureResource>(temp.getName(), prRenderEngine, temp.getDimensions(),
                                               temp.getInternalFormat());

  mColor = lg::Transparent;
  mBox.setBox(crPos, crSize);

  mTexture->update(temp.getImgData().data(), temp.getDimensions(), temp.getOffset(), temp.getFormat(), temp.getType());
  VertexUtility::createVertex(mVertex, mBox.getTopLeft(), mBox.getSize(), mColor, mTexture->getCacheId());
  VertexUtility::updateTextureCoordinates(mVertex, temp.getDimensions(), temp.getOffset(),
                                          mTexture->getSize());
  registerDrawable(prBatch, mTexture->getTextureId());
}

//! @brief Sprite Constructor
//!        Use this constructor if you do not want a Texture on Sprite
//!
//! @param[out] prBatch        BatchBuffer to register drawable
//! @param[in]  crPos          Position of Sprite
//! @param[in]  crSize         Size of Sprite
//! @param[in]  crColor        Color of Sprite
//!
//! @return Sprite Object 
Sprite::Sprite(std::shared_ptr<BatchBuffer>& prBatch, const Vector2<float>& crPos, const Vector2<float>& crSize,
               const lg::Color& crColor)
{
  mColor = crColor;
  Vector2<float> offset(0.0f, 0.0f);
  mBox.setBox(crPos, crSize);
  VertexUtility::createVertex(mVertex, mBox.getTopLeft(), mBox.getSize(), mColor, -1.0f);
  VertexUtility::updateTextureCoordinates(mVertex, mBox.getSize(), offset, mBox.getSize());
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
    VertexUtility::updateVertex(mVertex, mBox.getTopLeft(), mBox.getSize(), mColor);
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

//! @brief Returns position of Sprite
//!
//! @return Sprite Position
Vector2<float> Sprite::getPos()
{
  return mBox.getPos();
}

//! @brief Moves Sprite
//!
//! @param[in] crMoveVector Vector to add to Sprite
//!
//! @return None
void Sprite::movePos(const Vector2<float>& crMoveVector)
{
  mBox.movePos(crMoveVector);
  mNeedUpdate = true;
}

//! @brief Sets the Sprite Positition
//!        Note: This works by setting the Center Position
//!
//! @param crPos New Sprite Position
//!
//! @return None
void Sprite::setPos(const Vector2<float>& crPos)
{
  mBox.setPos(crPos);
  mNeedUpdate = true;
}

//! @brief Sets Size of Sprite
//!
//! @param crSize New Sprite Size
//!
//! @return None
void Sprite::setSize(const Vector2<float>& crSize)
{
  mBox.setSize(crSize);
  mNeedUpdate = true;
}

//! @brief Gets the Box corresponding to Sprite
//!
//! @return Box of Sprite 
Box<float>& Sprite::getBox()
{
  return mBox;
}

//! @brief Gets the Size of Sprite
//!
//! @return Size of Sprite
Vector2<float> Sprite::getSize()
{
  return mBox.getSize();
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