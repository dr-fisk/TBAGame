#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "common.h"
#include "glcommon.h"
#include "Drawable.h"

#define PIXEL_SIZE 1

class Rect : public Drawable {
  public:
    Rect();
    Rect(const uint32_t cLeft, const uint32_t cTop, const uint32_t cWidth=1, const uint32_t cHeight=1);
    virtual ~Rect();
    void getDimensions(GLfloat *pLeft, GLfloat *pTop, GLfloat *pWidth, GLfloat *pHeight);
    void setColor(const uint8_t cRed, const uint8_t cGreen, const uint8_t cBlue, const uint8_t cAlpha=255);
    void setColor(const lg::Color cColor);
    void setPos(const uint32_t cLeft, const uint32_t cTop);
    lg::Color getRGBA();
    RenderData createRenderData();
    virtual std::vector<RenderData> getRenderData();
  private:
    uint32_t mLeft;
    uint32_t mTop;
    uint32_t mHeight;
    uint32_t mWidth;
    lg::Color mRgba;
};

#endif