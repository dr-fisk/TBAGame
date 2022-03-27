#include "renderTarget.h"
#include "renderWindow.h"

enum TARGETS{RECTANGLE, TRIANGLE};

Rect::Rect() {
  this->left   = 0;
  this->top    = 0;
  this->width  = 0;
  this->height = 0;
}

/* Creates Rect coords, used int instead of normalized floats since
   it's a little easier to know where ex. (400, 400) is versus (0.0f, 0.0f) */
Rect::Rect(uint32_t left, uint32_t top, uint32_t height, uint32_t width) {
  this->left   = left;
  this->top    = top;
  this->width  = width;
  this->height = height;
}

void Rect::getDimensions(uint32_t *left, uint32_t *top, uint32_t *height, uint32_t *width) {
  *left   = this->left;
  *top    = this->top;
  *height = this->height;
  *width  = this->width;
}

Rect::~Rect() {
}

RenderTarget::RenderTarget() {
}

RenderTarget::~RenderTarget() {
}

/* Handles to opengl to draw a square */
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

void RenderTarget::render() {
}

uint32_t RenderTarget::getWindowWidth() {

}

uint32_t RenderTarget::getWindowHeight() {

}

VertexArray* RenderTarget::getVao() {

}

/* Creates Rectangle in normalized coordinates */
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

/* Bounds our coordinates so we always render inside our window */
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