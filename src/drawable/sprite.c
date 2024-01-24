#include <iostream>

#include "drawable/sprite.h"
#include "resource/image.h"
#include "renderer/renderer2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

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
  mBox.setTopLeft(temp2);
  updateTextureCoordinates(glm::vec2(0.0f, 0.0f), mTexture->getSize());
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
  mBox.setTopLeft(temp);
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
  if(mRender)
  {
    // TODO: Update offset for sprites
    if(nullptr != mTexture)
    {
      Renderer2D::registerQuad(mBox.getTopLeft(), mBox.getSize(), mVertexes, mTexture, mGeometryNeedUpdate);
    }
    else
    {
      Renderer2D::registerQuad(mBox.getTopLeft(), mBox.getSize(), mVertexes, mColor, mGeometryNeedUpdate);
    }

    mGeometryNeedUpdate = false;
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
  mGeometryNeedUpdate = true;
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
  glm::ivec2 temp;
  // temp.x = round(mBox.getTopLeft().x);
  // temp.y = round(mBox.getTopLeft().y);
  // mBox.setTopLeft(temp);
  mGeometryNeedUpdate = true;
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
  // glm::ivec2 temp;
  // temp.x = round(mBox.getTopLeft().x);
  // temp.y = round(mBox.getTopLeft().y);
  // mBox.setTopLeft(temp);
  mGeometryNeedUpdate = true;
}

//! @brief Sets Size of Sprite
//!
//! @param[in] crSize New Sprite Size
//!
//! @return None
void Sprite::setSize(const glm::vec2& crSize)
{
  mBox.setSize(crSize);
  mGeometryNeedUpdate = true;
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
//! TODO: Add the size of the texture to set
//!
//! @param[in] crpTexture Texture to set on Sprite
//! @param[in] cInvert    Inverts texture coordinates
//!
//! @return None 
void Sprite::setTexture(const std::shared_ptr<TextureResource>& crpTexture, const bool cInvert)
{
  glm::vec2 offset(0, 0); // Update offset

  mTexture = crpTexture;

  updateTextureCoordinates(offset, mTexture->getSize());
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

//! @brief  Updates texture coordinates for Sprite
//!
//! @param[in] crOffset      Offset of Texture within Texture resource 
//! @param[in] crTextureSize Total Texture Size
//!
//! @return None 
void Sprite::updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize)
{
    const float xMax = static_cast<float>(crTextureSize.x + crOffset.x) / static_cast<float>(mTexture->getSize().x);
    const float yMax = static_cast<float>(crTextureSize.y + crOffset.y) / static_cast<float>(mTexture->getSize().y);
    const float xMin = static_cast<float>(crOffset.x) / static_cast<float>(mTexture->getSize().x);
    const float yMin = static_cast<float>(crOffset.y) / static_cast<float>(mTexture->getSize().y);

    mVertexes[0].TextCoord = glm::vec2(xMin, yMin);
    mVertexes[1].TextCoord = glm::vec2(xMax, yMin);
    mVertexes[2].TextCoord = glm::vec2(xMax, yMax);
    mVertexes[3].TextCoord = glm::vec2(xMin, yMax);
}

//! @brief 
//! @param crCamera 
//! @return 
Box<glm::vec2> Sprite::getGlobalBounds(const OrthCamera& crCamera)
{
  const glm::vec4 TOP_LEFT = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  const glm::vec4 BOTTOM_RIGHT = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(mBox.getTopLeft(), 0.0f)) * glm::scale(glm::mat4(1.0f),
                                      {mBox.getSize().x, mBox.getSize().y, 1.0f});

  glm::vec2 topLeft = crCamera.getViewProjectionMatrix() * transform * TOP_LEFT;
  glm::vec2 size = crCamera.getViewProjectionMatrix() * transform * BOTTOM_RIGHT;
  size = abs(size - topLeft);
  return Box<glm::vec2>::createBoxTopLeft(topLeft, size);
}