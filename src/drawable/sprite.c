#include <iostream>

#include "drawable/sprite.h"
#include "resource/image.h"
#include "utility/vertexUtility.h"
#include "renderer/renderer2D.h"

//! @brief Sprite Constructor
//!
//! @param[in]  crPath         Path of image
//! @param[out] prRenderEngine Resource Manager to create Texture Resource
//! @param[in]  crPos          Position of Sprite
//! @param[in]  crSize         Size of Sprite
//!
//! @return Sprite Object 
Sprite::Sprite(const std::string& crPath, std::shared_ptr<RenderEngine>& prRenderEngine,
               const glm::vec2& crPos, const glm::vec2& crSize)
{
  Image temp(crPath);
  mTexture = std::make_shared<TextureResource>(temp.getName(), prRenderEngine, temp.getDimensions(),
                                               temp.getInternalFormat());
  mLayer = 0;
  mColor = lg::Transparent;
  mBox.setBox(crPos, crSize);
  glm::ivec2 temp2;
  temp2.x = round(mBox.getTopLeft().x);
  temp2.y = round(mBox.getTopLeft().y);
  mTexture->update(temp.getImgData().data(), temp.getDimensions(), temp.getOffset(), temp.getFormat(), temp.getType());
  VertexUtility::createVertex(mVertex, temp2, mBox.getSize(), mColor, mTexture->getCacheId());
  VertexUtility::updateTextureCoordinates(mVertex, temp.getDimensions(), temp.getOffset(),
                                          mTexture->getSize());
}

//! @brief Sprite Constructor
//!        Use this constructor if you do not want a Texture on Sprite
//!
//! @param[in]  crPos          Position of Sprite
//! @param[in]  crSize         Size of Sprite
//! @param[in]  crColor        Color of Sprite
//!
//! @return Sprite Object 
Sprite::Sprite(const glm::vec2& crPos, const glm::vec2& crSize, const lg::Color& crColor)
{
  mColor = crColor;
  glm::vec2 offset(0.0f, 0.0f);
  mBox.setBox(crPos, crSize);
  glm::ivec2 temp;
  temp.x = round(mBox.getTopLeft().x);
  temp.y = round(mBox.getTopLeft().y);
  VertexUtility::createVertex(mVertex, temp, mBox.getSize(), mColor, -1.0f);
  VertexUtility::updateTextureCoordinates(mVertex, mBox.getSize(), offset, mBox.getSize());
}

//! @brief Get Texture Resource for Drawable
//!
//! @return Texture Resource
std::shared_ptr<TextureResource> Sprite::getResource()
{
  return mTexture;
}

//! @brief Draws the Sprite
//!
//! @return None
void Sprite::draw()
{
  if(mNeedUpdate)
  {
    glm::ivec2 temp;
    temp.x = round(mBox.getTopLeft().x);
    temp.y = round(mBox.getTopLeft().y);
    VertexUtility::updateVertex(mVertex, mBox.getTopLeft(), mBox.getSize(), mColor);
    mNeedUpdate = false;
  }

  if(mRender)
  {
    Renderer2D::registerQuad(mVertex, mTexture);
  }
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
glm::vec2 Sprite::getPos()
{
  return mBox.getPos();
}

//! @brief Moves Sprite
//!
//! @param[in] crMoveVector Vector to add to Sprite
//!
//! @return None
void Sprite::movePos(const glm::vec2& crMoveVector)
{
  mBox.movePos(crMoveVector);
  mNeedUpdate = true;
}

//! @brief Sets the Sprite Positition
//!        Note: This works by setting the Center Position
//!
//! @param[in] crPos New Sprite Position
//!
//! @return None
void Sprite::setPos(const glm::vec2& crPos)
{
  mBox.setPos(crPos);
  mNeedUpdate = true;
}

//! @brief Sets Size of Sprite
//!
//! @param[in] crSize New Sprite Size
//!
//! @return None
void Sprite::setSize(const glm::vec2& crSize)
{
  mBox.setSize(crSize);
  mNeedUpdate = true;
}

//! @brief Gets the Box corresponding to Sprite
//!
//! @return Box of Sprite 
Box<glm::vec2>& Sprite::getBox()
{
  return mBox;
}

//! @brief Gets the Size of Sprite
//!
//! @return Size of Sprite
glm::vec2 Sprite::getSize()
{
  return mBox.getSize();
}

//! @brief Default Destructor
//!        Unregisters Sprite from Render List
//!
//! @return None
Sprite::~Sprite()
{
}

//! @brief Sets Texture for Sprite
//!
//! @param[in] crpTexture Texture to set on Sprite
//! @param[in] cInvert    Inverts texture coordinates
//!
//! @return None 
void Sprite::setTexture(const std::shared_ptr<TextureResource>& crpTexture, const bool cInvert)
{
  glm::vec2 offset(0, 0); // Update offset

  mTexture = crpTexture;
  VertexUtility::updateTextureCoordinates(mVertex, mTexture->getSize(), offset,
                                          mTexture->getSize(), cInvert);
}

//! @brief Setst the Layer for the Sprite
//!        Handles Reregistering into Map of Drawables for sorting
//!
//! @param cLayer Layer to set Sprite Draw, Higher Layers means Quad will render over lower Layer Quads
//!        Think of Layer = 0 as Background
//!
//! @return None
void Sprite::setLayer(const uint32_t cLayer)
{
  mLayer = cLayer;
}