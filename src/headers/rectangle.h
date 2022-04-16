#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "common.h"

struct RectVertexData {
  Vector2f bottomLeft;
  Vector4f rgba1;
  Vector2f bottomRight;
  Vector4f rgba2;
  Vector2f topRight;
  Vector4f rgba3;
  Vector2f topLeft;
  Vector4f rgba4;
};

class Rect {
  public:
    Rect();
    Rect(uint32_t left, uint32_t top, uint32_t width, uint32_t height);
    ~Rect();
    void getDimensions(GLfloat *left, GLfloat *top, GLfloat *width, GLfloat *height);
    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    Vector4f getRGBA();
  private:
    uint32_t left;
    uint32_t top;
    uint32_t height;
    uint32_t width;
    Vector4f rgba;
};

#endif