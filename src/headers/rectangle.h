#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "common.h"

struct RectVertices {
  Vector2f bottomLeft;
  Vector2f bottomRight;
  Vector2f topRight;
  Vector2f topLeft;
};

class Rect {
  public:
    Rect();
    Rect(uint32_t left, uint32_t top, uint32_t width, uint32_t height);
    ~Rect();
    void getDimensions(GLfloat *left, GLfloat *top, GLfloat *width, GLfloat *height);
  private:
    uint32_t left;
    uint32_t top;
    uint32_t height;
    uint32_t width;
};

#endif