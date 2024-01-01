#include "drawable/rectangle.h"
#include <cmath>

//! @brief Default Constructor
//!
//! @return Object
Rect::Rect()
{
  mPos  = Vector2<float>(0, 0);
  mSize = Vector2<float>(0, 0);
}

//! @brief Creates rectangle shape
//!
//! @param[in] cLeft   Leftmost coordinate
//! @param[in] cTop    Topmost coordinate
//! @param[in] cHeight Height of rect
//! @param[in] cWidth  Width of rect
//!
//! @return Rect Object
Rect::Rect(const float cLeft, const float cTop, const float cHeight, const float cWidth)
{
  mPos  = Vector2<float>(cLeft, cTop);
  mSize = Vector2<float>(cWidth, cHeight);
}

//! @brief Creates rectangle shape
//!
//! @param[in] crPos   Position of Rect
//! @param[in] cHeight Height of rect
//! @param[in] cWidth  Width of rect
//!
//! @return Rect Object
Rect::Rect(const Vector2<float>& crPos, const float cHeight, const float cWidth)
{
  mPos = crPos;
  mSize = Vector2<float>(cWidth, cHeight);
}

//! @brief Assigns dimensions of rectangle
//!
//! @param[in]  pLeft
//! @param[in]  pTop
//! @param[in]  pHeight
//! @param[in]  pWidth
//!
//! @return None
void Rect::getDimensions(GLfloat *pLeft, GLfloat *pTop, GLfloat *pHeight, GLfloat *pWidth)
{
  *pLeft   = mPos.x;
  *pTop    = mPos.y;
  *pHeight = mSize.y;
  *pWidth  = mSize.x;
}

//! @brief Returns Normalized Coordinates
//!
//! @return Normalized Coordinates
Vector2<GLfloat> Rect::getTranslate()
{
  const GLfloat wWidth = gWindowWidth / 2.0f;
  const GLfloat wHeight = gWindowHeight / 2.0f;
  return Vector2<GLfloat>((static_cast<GLfloat>(mPos.x) / wWidth) - 1.0f,
                          -1 * ((static_cast<GLfloat>(mPos.y) / wHeight) - 1.0f));
}

//! @brief Returns Normalized Coordinates
//!
//! @param[out] rTranslate Vector2 to store Normalized Coordinates
//!
//! @return None
void Rect::translate(Vector2<GLfloat>& rTranslate)
{
  const GLfloat wWidth = gWindowWidth / 2.0f;
  const GLfloat wHeight = gWindowHeight / 2.0f;
  mPos.x = (rTranslate.x * wWidth) + wWidth;
  mPos.y = -1 * ((rTranslate.y * wHeight) + wHeight);
}

// TODO: Add default params to be centered around bottom left of screen
void Rect::rotate(GLfloat theta)
{
  GLfloat wWidth = gWindowWidth / 2.0f;
  GLfloat wHeight = gWindowHeight / 2.0f;
  GLfloat x1 = (static_cast<GLfloat>(mPos.x) / wWidth) - 1.0f;
  GLfloat y1 = -1 * ((static_cast<GLfloat>(mPos.y) / wHeight) - 1.0f);


  x1 = (x1 + 1.0f)*std::cos(theta) - (y1 + 1.0f)*std::sin(theta);
  y1 = (x1 + 1.0f)*std::sin(theta) + (y1 + 1.0f)*std::cos(theta);

  mPos.x = x1 * wWidth + wWidth;
  mPos.y = -y1 * wHeight - wHeight;
}

//! @brief Updates position of Rectangle with given position
//!
//! @param[in] cLeft Left position of rectangle
//! @param[in] cTop  Top position of rectangle
//!
//! @return None
void Rect::setPos(const float cLeft, const float cTop)
{
  mPos.x   = cLeft;
  mPos.y    = cTop;
}

//! @brief Updates position of Rectangle with given position
//!
//! @param[in] crPos Position in Vector2 format
//!
//! @return None
void Rect::setPos(const Vector2<float>& crPos)
{
  mPos = crPos;
}

//! @brief Updates size of Rectangle with given size
//!
//! @param[in] crSize Size in Vector2 format
//!
//! @return None
void Rect::setSize(const Vector2<float>& crSize)
{
  mSize = crSize;
}

//! @brief Updates position of Rectangle by adding the position values given
//!
//! @param[in] cLeft Units to move X value
//! @param[in] cTop  Units to move Y value
//!
//! @return None
void Rect::movePos(const float cLeft, const float cTop)
{
  mPos.x   += cLeft;
  mPos.y   += cTop;
}

//! @brief Gets the X position of Rectangle
//!
//! @return X position
float Rect::getLeft() const
{
  return mPos.x;
}

//! @brief Gets the Y position of Rectangle
//!
//! @return Y position
float Rect::getTop() const
{
  return mPos.y;
}

//! @brief Gets Position Coordinate of Rectangle
//!
//! @return Coordinate Position
Vector2<float> Rect::getPos() const
{
  return mPos;
}

//!   @brief Destructor
//!   Parameters:  None
//!   @return     None
Rect::~Rect()
{
}