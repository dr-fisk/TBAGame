#include "renderTarget.h"
#include "renderWindow.h"

enum TARGETS{RECTANGLE, TRIANGLE};

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

/* Function:    getDimensions
   Description: Assigns dimensions of rectangle use function with either pointers
                or pass by reference
   Parameters:  None
   Returns:     None 
 */
void Rect::getDimensions(uint32_t *left, uint32_t *top, uint32_t *height, uint32_t *width) {
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

/* Function:    RenderTarget
   Description: Default Contructor
   Parameters:  None
   Returns:     None 
 */
RenderTarget::RenderTarget() {
}

/* Function:    ~RenderTarget
   Description: Destructor
   Parameters:  None
   Returns:     None 
 */
RenderTarget::~RenderTarget() {
}

/* Function:    draw
   Description: TBD since might get deleted
   Parameters:  None
   Returns:     None 
 */
void RenderTarget::draw(Rect shape) {
  uint32_t left, top, width, height;
  Vector2f vertices[4] = {};
  shape.getDimensions(&left, &top, &width, &height);
  createRectTarget(vertices, (GLfloat) left, (GLfloat) top, (GLfloat) width, (GLfloat) height);
  /*glBufferData(GL_ARRAY_BUFFER, SQUARE_BYTE_SIZE, vertices, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 2,  GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0 );*/
  render();
}

/* Function:    render
   Description: Virtual Function
   Parameters:  None
   Returns:     None 
 */
void RenderTarget::render() {
}

/* Function:    getWindowWidth
   Description: Virtual Function
   Parameters:  None
   Returns:     None 
 */
uint32_t RenderTarget::getWindowWidth() {
}

/* Function:    getWindowHeight
   Description: Virtual Function
   Parameters:  None
   Returns:     None 
 */
uint32_t RenderTarget::getWindowHeight() {
}

/* Function:    getVao
   Description: Virtual Function
   Parameters:  None
   Returns:     None 
 */
VertexArray* RenderTarget::getVao() {
}

/* Function:    createRectTarget
   Description: Normalizes Rect coords to be drawn on window this allows us
                to not have to worry about resolution
   Parameters:  Vector2f - Buffer to store normalized rect coordinates
                GLfloat  - Rect left coord
                GLfloat  - Rect top coord
                GLfloat  - Rect width
                GLfloat  - Rect height
   Returns:     None 
 */
void RenderTarget::createRectTarget(Vector2f *vertices, GLfloat left, GLfloat top, GLfloat width, 
                                GLfloat height) {
  GLfloat wWidth = (GLfloat) getWindowWidth() / 2.0f;
  GLfloat wHeight = (GLfloat) getWindowHeight() / 2.0f;

  boundCoords(&left, &width, &top, &height);

  GLfloat x1 = (left / wWidth) - 1.0f;
  GLfloat x2 = ((left + width)/ wWidth) - 1.0f;
  GLfloat y1 = -1 * ((top / wHeight) - 1.0f);
  GLfloat y2 = -1 * (((top + height) / wHeight) - 1.0f);
  
  vertices[0] = Vector2f(x1, y1);
  vertices[1] = Vector2f(x1, y2);
  vertices[2] = Vector2f(x2, y2);
  vertices[3] = Vector2f(x2, y1);
}

/* Function:    boundCoords
   Description: Ensures coordinates are never out of bounds from resolution
   Parameters:  None
   Returns:     None 
 */
void RenderTarget::boundCoords(GLfloat *left, GLfloat *width, GLfloat *top, GLfloat *height) {
  uint32_t wWidth = getWindowWidth();
  uint32_t wHeight = getWindowHeight();

  if (*width > wWidth)
    *width = wWidth;

  if (*height > wHeight)
    *height = wHeight;

  if (*left > wWidth)
    *left = wWidth;
  
  if (*height > wHeight)
    *height = wHeight;

  if ((*left + *width) > wWidth) {
    *left -= *width;

    if (*left < 0.0f)
      *left = 0.0f;
  }

  if ((*top + *height) > wHeight) {
    *top -= *height;

    if (*top < 0.0f)
      *top = 0.0f;
  }
}