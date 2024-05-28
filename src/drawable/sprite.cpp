#include <iostream>

#define GLM_FORCE_CTOR_INIT
#include "drawable/sprite.hpp"
#include "resource/image.hpp"
#include "renderer/renderer2D.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

//! @brief Default Constructor
//!
//! @return Sprite Object
Sprite::Sprite()
{
  mpTexture = nullptr;
  mDrawFunc = std::bind(&Sprite::drawUntexturedSprite, this);
}

//! @brief Registers lambda function to bind member functions to std::function
//!
//! @param Callback Lambda function to register member function
//!
//! @return Function pointer 
std::function<void(const Transform&)> Sprite::RegisterDrawCall(std::function<void(const Transform&)> Callback)
{
  return Callback;
}

Sprite::Sprite(const Sprite& rSprite)
{
  *this = rSprite;
}

Sprite& Sprite::operator=(const Sprite& rhs)
{
  if(this == &rhs)
  {
    return *this;
  }

  
  mBox = rhs.mBox;
  mPrevPos = rhs.mPrevPos;
  mVertexes = rhs.mVertexes;
  mpTexture = rhs.mpTexture;
  mTransform = rhs.mTransform;
  if(!mpTexture)
  {
    mDrawFunc = std::bind(&Sprite::drawUntexturedSprite, this);
  }
  else
  {
    mDrawFunc = std::bind(&Sprite::drawTexturedSprite, this);
  }
  return *this;
}

//! @brief Sprite Constructor
//!
//! @param[in] crTexture Texture of Sprite
//! @param[in] crBox     Dimensions of Sprite
//!
//! @return Sprite Object
Sprite::Sprite(const Texture2D& crTexture, const Box<glm::vec2>& crBox)
{
  mpTexture = &crTexture;
  mBox = crBox;
  mTransform.setPos(crBox.getPos());
  mTransform.setScale(crBox.getSize());
  mPrevPos = mBox.getPos();
  updateTextureCoordinates(glm::vec2(0.0f, 0.0f), crTexture.getSize());
  mGeometryNeedUpdate = true;
  mDrawFunc = std::bind(&Sprite::drawTexturedSprite, this);
}

//! @brief Sprite Constructor
//!
//! @param[in] crColor   Color of Sprite
//! @param[in] crBox     Dimensions of Sprite
//!
//! @return Sprite Object
Sprite::Sprite(const lg::Color& crColor, const Box<glm::vec2>& crBox)
{
  mpTexture = nullptr;
  mBox = crBox;
  mTransform.setPos(crBox.getPos());
  mTransform.setScale(crBox.getSize());
  mPrevPos = mBox.getPos();
  setColor(crColor);
  mGeometryNeedUpdate = true;
  mDrawFunc = std::bind(&Sprite::drawUntexturedSprite, this);
}

//! @brief Get Texture for Drawable
//!
//! @return Texture
const Texture2D& Sprite::getTexture() const
{
  return *mpTexture;
}

//! @brief Draws the Sprite
//!
//! @return None
void Sprite::draw()
{
  if(mRender)
  {
    mDrawFunc();
    mGeometryNeedUpdate = false;
  }
}

//! @brief Sets Color of Sprite
//!        Only useful for Sprites without Textures
//!
//! @param[in] crColor Color to set Sprite
//!
//! @return None
Sprite& Sprite::setColor(const lg::Color& crColor)
{
  for(auto& vertex : mVertexes)
  {
    vertex.Rgba = crColor;
  }

  mGeometryNeedUpdate = true;
  return *this;
}

//! @brief Returns position of Sprite
//!
//! @return Sprite Position
glm::vec2 Sprite::getPos() const
{
  return mTransform.getPos();
}

//! @brief Moves Sprite
//!
//! @param[in] crMoveVector Vector to add to Sprite
//!
//! @return None
void Sprite::movePos(const glm::vec2& crMoveVector)
{
  mTransform += crMoveVector;
  mGeometryNeedUpdate = true;
}

//! @brief Sets the Sprite Positition
//!        Note: This works by setting the Center Position
//!
//! @param[in] crPos New Sprite Position
//!
//! @return None
Sprite& Sprite::setPos(const glm::vec2& crPos)
{
  mTransform.setPos(crPos);
  mGeometryNeedUpdate = true;
  return *this;
}

//! @brief Sets Size of Sprite
//!
//! @param[in] crSize New Sprite Size
//!
//! @return None
Sprite& Sprite::resize(const glm::vec2& crSize)
{
  mTransform.setScale(crSize);
  mGeometryNeedUpdate = true;
  return *this;
}

//! @brief Gets the Box corresponding to Sprite
//!
//! @return Box of Sprite 
const Box<glm::vec2>& Sprite::getBox() const
{
  return mBox;
}

//! @brief Gets the Size of Sprite
//!
//! @return Size of Sprite
glm::vec2 Sprite::getSize() const
{
  return mTransform.getScale();
}

//! @brief Sets Texture for Sprite
//! TODO: Add the size of the texture to set
//!
//! @param[in] crTexture  Texture to set on Sprite
//! @param[in] cInvert    Inverts texture coordinates
//!
//! @return None 
Sprite& Sprite::setTexture(const Texture2D& crTexture, const bool cInvert)
{
  glm::vec2 offset(0, 0); // Update offset

  mpTexture = &crTexture;

  updateTextureCoordinates(offset, mpTexture->getSize());
  mGeometryNeedUpdate = true;
  mDrawFunc = std::bind(&Sprite::drawTexturedSprite, this);
  return *this;
}

Sprite& Sprite::setTransform(const Transform& crTransform)
{
  mTransform = crTransform;
  mGeometryNeedUpdate = true;
  return *this;
}

Sprite& Sprite::setBox(const Box<glm::vec2>& crBox)
{
  mBox = crBox;
  mGeometryNeedUpdate = true;
  return *this;
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
    const float xMax = static_cast<float>(crTextureSize.x + crOffset.x) / static_cast<float>(mpTexture->getSize().x);
    const float yMax = static_cast<float>(crTextureSize.y + crOffset.y) / static_cast<float>(mpTexture->getSize().y);
    const float xMin = static_cast<float>(crOffset.x) / static_cast<float>(mpTexture->getSize().x);
    const float yMin = static_cast<float>(crOffset.y) / static_cast<float>(mpTexture->getSize().y);

    mVertexes[0].TextCoord = glm::vec2(xMin, yMin);
    mVertexes[1].TextCoord = glm::vec2(xMax, yMin);
    mVertexes[2].TextCoord = glm::vec2(xMax, yMax);
    mVertexes[3].TextCoord = glm::vec2(xMin, yMax);
}

//! @brief 
//! @param crCamera 
//! @return 
Box<glm::vec2> Sprite::getGlobalBounds(const OrthCamera& crCamera) const
{
  const glm::vec4 TOP_LEFT = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  const glm::vec4 BOTTOM_RIGHT = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(mTransform.getPos() - (mTransform.getScale() / 2.0f), 0.0f)) * glm::scale(glm::mat4(1.0f),
                                      {mTransform.getScale().x, mTransform.getScale().y, 1.0f});

  glm::vec2 topLeft = crCamera.getViewProjectionMatrix() * transform * TOP_LEFT;
  glm::vec2 size = crCamera.getViewProjectionMatrix() * transform * BOTTOM_RIGHT;
  size = abs(size - topLeft);
  return Box<glm::vec2>::createBoxTopLeft(topLeft, size);
}

void Sprite::drawUntexturedSprite()
{
  Renderer2D::registerQuad(mTransform, mVertexes, mTransform.getScale() / 2.0f);
}

void Sprite::drawTexturedSprite()
{
  Renderer2D::registerQuad(mTransform, mVertexes, mpTexture, mTransform.getScale() / 2.0f);
}