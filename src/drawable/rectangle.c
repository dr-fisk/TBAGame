#include "rectangle.h"

/* Function:    Rect
   Description: Default Constructor
   Parameters:  None
   Returns:     None
*/
Rect::Rect() {
  mLeft   = 0;
  mTop    = 0;
  mWidth  = 0;
  mHeight = 0;
  mRgba = lg::Color(0, 0, 0);
}

/* Function:    Rect
   Description: Creates rectangle shape
   Parameters:  uint32_t - leftmost coordinate
                uint32_t - topmost coordinate
                uint32_t - height of rect
                uint32_t - width of rect
   Returns:     None
*/
Rect::Rect(const uint32_t cLeft, const uint32_t cTop, const uint32_t cHeight, const uint32_t cWidth) {
  mLeft   = cLeft;
  mTop    = cTop;
  mWidth  = cWidth;
  mHeight = cHeight;
}

/* Function:    setColor
   Description: Sets the color for the rectangle
   Parameters:  uint8_t - Red color attribute
                uint8_t - Green color attribute
                uint8_t - Blue color attribute
   Returns:     None
*/
void Rect::setColor(const uint8_t cRed, const uint8_t cGreen, const uint8_t cBlue, const uint8_t cAlpha) {
  mRgba = lg::Color(cRed, cGreen, cBlue, cAlpha);
}

/* Function:    setColor
   Description: Sets the color for the rectangle
   Parameters:  Color - Pre-defined color attribute
   Returns:     None
*/
void Rect::setColor(const lg::Color cColor) {
  mRgba = cColor;
}

/* Function:    getRBGA
   Description: Returns the color attached to the rect shape
   Parameters:  None
   Returns:     Color - Color of rectangle
*/
lg::Color Rect::getRGBA() {
  return mRgba;
}

/* Function:    getDimensions
   Description: Assigns dimensions of rectangle use function with either pointers
                or pass by reference
   Parameters:  None
   Returns:     None
*/
void Rect::getDimensions(GLfloat *pLeft, GLfloat *pTop, GLfloat *pHeight, GLfloat *pWidth) {
  *pLeft   = mLeft;
  *pTop    = mTop;
  *pHeight = mHeight;
  *pWidth  = mWidth;
}

/* Function:    createRenderData
   Description: Normalizes Rect coords to be drawn on window this allows us
                to not have to worry about resolution
   Parameters:  Rect - Rectangle shape to extract coordinates
   Returns:     RenderData - Data that is renderable for batchbuffer;
*/
RenderData Rect::createRenderData() {
  GLfloat wWidth = gWindowWidth / 2.0f;
  GLfloat wHeight = gWindowHeight / 2.0f;

  GLfloat x1 = ((GLfloat) mLeft / wWidth) - 1.0f;
  GLfloat x2 = (((GLfloat) mLeft + (GLfloat) mWidth)/ wWidth) - 1.0f;
  GLfloat y1 = -1 * (((GLfloat) mTop / wHeight) - 1.0f);
  GLfloat y2 = -1 * ((((GLfloat) mTop + (GLfloat) mHeight) / wHeight) - 1.0f);

  return { Vector2f(x1, y2), mRgba, Vector2f(x2, y2), mRgba,
           Vector2f(x2, y1), mRgba, Vector2f(x1, y1), mRgba};
}

/* Function:    setPos
   Description: Updates position of Rectangle
   Parameters:  uint32_t - left position of rectangle
                uint32_t - top position of rectangle
   Returns:     None
*/
void Rect::setPos(const uint32_t cLeft, const uint32_t cTop) {
  mLeft   = cLeft;
  mTop    = cTop;
}

/* Function:    getRenderData
   Description: Returns render data to be inserted into VBO
   Parameters:  None
   Returns:     RenderData - Data that is renderable for batchbuffer;
*/
std::vector<RenderData> Rect::getRenderData() {
  return {Rect::createRenderData()};
}

/* Function:    ~Rect
   Description: Destructor
   Parameters:  None
   Returns:     None
*/
Rect::~Rect() {
}