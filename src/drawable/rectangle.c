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

//!   @brief Assigns dimensions of rectangle use function with either pointers
//!                or pass by reference
//!   Parameters:  None
//!   @return     None
void Rect::getDimensions(GLfloat *pLeft, GLfloat *pTop, GLfloat *pHeight, GLfloat *pWidth)
{
  *pLeft   = mPos.x;
  *pTop    = mPos.y;
  *pHeight = mSize.y;
  *pWidth  = mSize.x;
}

Vector2<GLfloat> Rect::getTranslate()
{
   GLfloat wWidth = gWindowWidth / 2.0f;
   GLfloat wHeight = gWindowHeight / 2.0f;
   return Vector2<GLfloat>((static_cast<GLfloat>(mPos.x) / wWidth) - 1.0f,
                           -1 * ((static_cast<GLfloat>(mPos.y) / wHeight) - 1.0f));
}

void Rect::translate(Vector2<GLfloat>& rTranslate)
{
   GLfloat wWidth = gWindowWidth / 2.0f;
   GLfloat wHeight = gWindowHeight / 2.0f;
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
   // mPos.y = -y1 * wHeight - wHeight / 2;
}

//!   @brief Updates position of Rectangle
//!   Parameters:  float - left position of rectangle
//!                float - top position of rectangle
//!   @return     None
void Rect::setPos(const float cLeft, const float cTop)
{
  mPos.x   = cLeft;
  mPos.y    = cTop;
}

void Rect::setPos(const Vector2<float>& crPos)
{
   mPos = crPos;
}

void Rect::setSize(const Vector2<float>& crSize)
{
   mSize = crSize;
}

void Rect::movePos(const float cLeft, const float cTop)
{
  mPos.x   += cLeft;
  mPos.y   += cTop;
}

float Rect::getLeft() const
{
   return mPos.x;
}

float Rect::getTop() const
{
   return mPos.y;
}

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