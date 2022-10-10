#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "common.h"
#define PIXEL_SIZE 1

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
    Rect(uint32_t left, uint32_t top, uint32_t width=1, uint32_t height=1);
    ~Rect();
    void getDimensions(GLfloat *left, GLfloat *top, GLfloat *width, GLfloat *height);
    void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha=255);
    void setColor(lg::Color color);
    lg::Color getRGBA();
    RectVertexData createRectVertexData(GLfloat windWidth, GLfloat windHeight);
  private:
    uint32_t left;
    uint32_t top;
    uint32_t height;
    uint32_t width;
    lg::Color rgba;
};

#endif