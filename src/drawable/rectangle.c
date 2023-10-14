#include "drawable/rectangle.h"
#include <cmath>

/* Function:    Rect
   Description: Default Constructor
   Parameters:  None
   Returns:     None
*/
Rect::Rect()
{
  mPos  = Vector2<int32_t>(0, 0);
  mSize = Vector2<int32_t>(0, 0);
  mRgba = lg::Color(0, 0, 0);
  mPrimitiveType = PrimitiveType::RECTANGLE;
}

/* Function:    Rect
   Description: Creates rectangle shape
   Parameters:  int32_t - leftmost coordinate
                int32_t - topmost coordinate
                int32_t - height of rect
                int32_t - width of rect
   Returns:     None
*/
Rect::Rect(const int32_t cLeft, const int32_t cTop, const int32_t cHeight, const int32_t cWidth, const lg::Color& crColor)
{
  mPos  = Vector2<int32_t>(cLeft, cTop);
  mSize = Vector2<int32_t>(cWidth, cHeight);
  mRgba = crColor;
  mPrimitiveType = PrimitiveType::RECTANGLE;
}

Rect::Rect(const Vector2<int32_t>& cPos, const int32_t cHeight, const int32_t cWidth)
{
  mPos = cPos;
  mSize = Vector2<int32_t>(cWidth, cHeight);
  mPrimitiveType = PrimitiveType::RECTANGLE;
}

/* Function:    setColor
   Description: Sets the color for the rectangle
   Parameters:  uint8_t - Red color attribute
                uint8_t - Green color attribute
                uint8_t - Blue color attribute
   Returns:     None
*/
void Rect::setColor(const uint8_t cRed, const uint8_t cGreen, const uint8_t cBlue, const uint8_t cAlpha)
{
  mRgba = lg::Color(cRed, cGreen, cBlue, cAlpha);
}

/* Function:    setColor
   Description: Sets the color for the rectangle
   Parameters:  Color - Pre-defined color attribute
   Returns:     None
*/
void Rect::setColor(const lg::Color cColor)
{
  mRgba = cColor;
}

/* Function:    getRBGA
   Description: Returns the color attached to the rect shape
   Parameters:  None
   Returns:     Color - Color of rectangle
*/
lg::Color Rect::getRGBA()
{
  return mRgba;
}

/* Function:    getDimensions
   Description: Assigns dimensions of rectangle use function with either pointers
                or pass by reference
   Parameters:  None
   Returns:     None
*/
void Rect::getDimensions(GLfloat *pLeft, GLfloat *pTop, GLfloat *pHeight, GLfloat *pWidth)
{
  *pLeft   = mPos.mX;
  *pTop    = mPos.mY;
  *pHeight = mSize.mY;
  *pWidth  = mSize.mX;
}

/* Function:    createRenderData
   Description: Normalizes Rect coords to be drawn on window this allows us
                to not have to worry about resolution
   Parameters:  Rect - Rectangle shape to extract coordinates
   Returns:     RenderData - Data that is renderable for batchbuffer;
*/
RenderData Rect::createRenderData()
{
  GLfloat wWidth = gWindowWidth / 2.0f;
  GLfloat wHeight = gWindowHeight / 2.0f;

  GLfloat x1 = ((GLfloat) mPos.mX / wWidth) - 1.0f;
  GLfloat x2 = (((GLfloat) mPos.mX + (GLfloat) mSize.mX)/ wWidth) - 1.0f;
  GLfloat y1 = -1 * (((GLfloat) mPos.mY / wHeight) - 1.0f);
  GLfloat y2 = -1 * ((((GLfloat) mPos.mY + (GLfloat) mSize.mY) / wHeight) - 1.0f);

  const Vector2<GLfloat> textCoord1(0.0f, 0.0f);
  const Vector2<GLfloat> textCoord2(1.0f, 0.0f);
  const Vector2<GLfloat> textCoord3(1.0f, 1.0f);
  const Vector2<GLfloat> textCoord4(0.0f, 1.0f);

  return { Vector2<GLfloat>(x1, y2), mRgba, textCoord1, -1.0f, Vector2<GLfloat>(x2, y2), mRgba, textCoord2, -1.0f,
           Vector2<GLfloat>(x2, y1), mRgba, textCoord3, -1.0f, Vector2<GLfloat>(x1, y1), mRgba, textCoord4, -1.0f };
}

Vector2<GLfloat> Rect::getTranslate()
{
   GLfloat wWidth = gWindowWidth / 2.0f;
   GLfloat wHeight = gWindowHeight / 2.0f;
   return Vector2<GLfloat>(((GLfloat) mPos.mX / wWidth) - 1.0f, -1 * (((GLfloat) mPos.mY / wHeight) - 1.0f));
}

void Rect::translate(Vector2<GLfloat>& rTranslate)
{
   GLfloat wWidth = gWindowWidth / 2.0f;
   GLfloat wHeight = gWindowHeight / 2.0f;
   mPos.mX = (rTranslate.mX * wWidth) + wWidth;
   mPos.mY = -1 * ((rTranslate.mY * wHeight) + wHeight);
}

// TODO: Add default params to be centered around bottom left of screen
void Rect::rotate(GLfloat theta)
{
   GLfloat wWidth = gWindowWidth / 2.0f;
   GLfloat wHeight = gWindowHeight / 2.0f;
   GLfloat x1 = ((GLfloat) mPos.mX / wWidth) - 1.0f;
   GLfloat y1 = -1 * (((GLfloat) mPos.mY / wHeight) - 1.0f);


   x1 = (x1 + 1.0f)*std::cos(theta) - (y1 + 1.0f)*std::sin(theta);
   y1 = (x1 + 1.0f)*std::sin(theta) + (y1 + 1.0f)*std::cos(theta);

   mPos.mX = x1 * wWidth + wWidth;
   mPos.mY = -y1 * wHeight - wHeight;
   // mPos.mY = -y1 * wHeight - wHeight / 2;
}

/* Function:    setPos
   Description: Updates position of Rectangle
   Parameters:  int32_t - left position of rectangle
                int32_t - top position of rectangle
   Returns:     None
*/
void Rect::setPos(const int32_t cLeft, const int32_t cTop)
{
  mPos.mX   = cLeft;
  mPos.mY    = cTop;
}

void Rect::setPos(const Vector2<int32_t>& crPos)
{
   mPos = crPos;
}

void Rect::setSize(const Vector2<int32_t>& crSize)
{
   mSize = crSize;
}

void Rect::movePos(const int32_t cLeft, const int32_t cTop)
{
  mPos.mX   += cLeft;
  mPos.mY    += cTop;
}

int32_t Rect::getLeft() const
{
   return mPos.mX;
}

int32_t Rect::getTop() const
{
   return mPos.mY;
}

Vector2<int32_t> Rect::getPos() const
{
   return mPos;
}

bool Rect::sortByXIntersection(const Rect& crP1, const Rect& crP2)
{
   if (crP1.getTop() == crP2.getTop())
   {
      return crP1.getLeft() < crP2.getLeft();
   }

   return crP1.getTop() < crP2.getTop();
}

/* Function:    getRenderData
   Description: Returns render data to be inserted into VBO
   Parameters:  None
   Returns:     RenderData - Data that is renderable for batchbuffer;
*/
std::vector<RenderData> Rect::getRenderData()
{
  return {Rect::createRenderData()};
}

/* Function:    ~Rect
   Description: Destructor
   Parameters:  None
   Returns:     None
*/
Rect::~Rect()
{
}