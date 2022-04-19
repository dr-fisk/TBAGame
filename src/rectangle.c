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
   Parameters:  None
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

/* Function:    ~Rect
   Description: Destructor
   Parameters:  None
   Returns:     None
 */
Rect::~Rect() {
}