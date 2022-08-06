#include "rectangle.h"

/* Function:    Rect
   Description: Default Constructor
   Parameters:  None
   Returns:     None
 */
Rect::Rect() {
  this->left   = 0;
  this->top    = 0;
  this->width  = 0;
  this->height = 0;
  this->rgba = lg::Color(0, 0, 0);
}

/* Function:    Rect
   Description: Creates rectangle shape
   Parameters:  uint32_t - leftmost coordinate
                uint32_t - topmost coordinate
                uint32_t - height of rect
                uint32_t - width of rect
   Returns:     None
 */
Rect::Rect(uint32_t left, uint32_t top, uint32_t height, uint32_t width) {
  this->left   = left;
  this->top    = top;
  this->width  = width;
  this->height = height;
}

/* Function:    setColor
   Description: Sets the color for the rectangle
   Parameters:  uint8_t - Red color attribute
                uint8_t - Green color attribute
                uint8_t - Blue color attribute
   Returns:     None
 */
void Rect::setColor(uint8_t red, uint8_t green, uint8_t blue) {
  this->rgba = lg::Color(red, green, blue);
}

/* Function:    setColor
   Description: Sets the color for the rectangle
   Parameters:  Color - Pre-defined color attribute
   Returns:     None
 */
void Rect::setColor(lg::Color color) {
  this->rgba = color;
}

/* Function:    getRBGA
   Description: Returns the color attached to the rect shape
   Parameters:  None
   Returns:     Color - Color of rectangle
 */
lg::Color Rect::getRGBA() {
  return rgba;
}

/* Function:    getDimensions
   Description: Assigns dimensions of rectangle use function with either pointers
                or pass by reference
   Parameters:  None
   Returns:     None
 */
void Rect::getDimensions(GLfloat *left, GLfloat *top, GLfloat *height, GLfloat *width) {
  *left   = this->left;
  *top    = this->top;
  *height = this->height;
  *width  = this->width;
}

/* Function:    createRectVertexData
   Description: Normalizes Rect coords to be drawn on window this allows us
                to not have to worry about resolution
   Parameters:  Rect - Rectangle shape to extract coordinates
   Returns:     RectVertexData - Vertexes from shape;
 */
RectVertexData Rect::createRectVertexData(GLfloat windWidth, GLfloat windHeight) {
  GLfloat wWidth = windWidth / 2.0f;
  GLfloat wHeight = windHeight / 2.0f;

  GLfloat x1 = ((GLfloat) left / wWidth) - 1.0f;
  GLfloat x2 = (((GLfloat) left + (GLfloat) width)/ wWidth) - 1.0f;
  GLfloat y1 = -1 * (((GLfloat) top / wHeight) - 1.0f);
  GLfloat y2 = -1 * ((((GLfloat) top + (GLfloat) height) / wHeight) - 1.0f);

  return { Vector2f(x1, y2), rgba, Vector2f(x2, y2), rgba,
           Vector2f(x2, y1), rgba, Vector2f(x1, y1), rgba};
}

/* Function:    ~Rect
   Description: Destructor
   Parameters:  None
   Returns:     None
 */
Rect::~Rect() {
}