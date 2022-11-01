#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "common.h"
#include "Drawable.h"

#define PIXEL_SIZE 1

class Rect : public Drawable {
  public:
    Rect();
    Rect(uint32_t left, uint32_t top, uint32_t width=1, uint32_t height=1);
    virtual ~Rect();
    void getDimensions(GLfloat *left, GLfloat *top, GLfloat *width, GLfloat *height);
    void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha=255);
    void setColor(lg::Color color);
    void setPos(uint32_t left, uint32_t top);
    lg::Color getRGBA();
    RenderData createRenderData();
    virtual std::vector<RenderData> getRenderData();
  private:
    uint32_t left;
    uint32_t top;
    uint32_t height;
    uint32_t width;
    lg::Color rgba;
};

#endif