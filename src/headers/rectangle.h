#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "common.h"

struct RectVertexData {
  Vector2f bottomLeft;
  lg::Color rgba1;
  Vector2f bottomRight;
  lg::Color rgba2;
  Vector2f topRight;
  lg::Color rgba3;
  Vector2f topLeft;
  lg::Color rgba4;
};

class Rect {
  public:
    Rect();
    Rect(uint32_t left, uint32_t top, uint32_t width, uint32_t height);
    ~Rect();
    void getDimensions(GLfloat *left, GLfloat *top, GLfloat *width, GLfloat *height);
    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    void setColor(lg::Color color);
    lg::Color getRGBA();
  private:
    uint32_t left;
    uint32_t top;
    uint32_t height;
    uint32_t width;
    lg::Color rgba;
};

#endif