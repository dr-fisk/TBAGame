#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "common.h"
#include "glcommon.h"
#include "Drawable.h"

#define PIXEL_SIZE 1

class Rect : public Drawable {
  public:
    Rect();
    Rect(const int32_t cLeft, const int32_t cTop, const int32_t cWidth=1, const int32_t cHeight=1);
    Rect(const Vector2<int32_t>& cPos, const int32_t cHeight=1, const int32_t cWidth=1);
    virtual ~Rect();
    void getDimensions(GLfloat *pLeft, GLfloat *pTop, GLfloat *pWidth, GLfloat *pHeight);
    void setColor(const uint8_t cRed, const uint8_t cGreen, const uint8_t cBlue, const uint8_t cAlpha=255);
    void setColor(const lg::Color cColor);
    void setPos(const int32_t cLeft, const int32_t cTop);
    void setPos(const Vector2<int32_t>& crPos);
    void setSize(const Vector2<int32_t>& crSize);
    void movePos(const int32_t cLeft, const int32_t cTop);
    int32_t getLeft() const;
    int32_t getTop() const;
    Vector2<int32_t> getPos() const;
    lg::Color getRGBA();
    RenderData createRenderData();
    virtual std::vector<RenderData> getRenderData();
    void rotate(GLfloat theta);
    Vector2<GLfloat> getTranslate();
    void translate(Vector2<GLfloat>& rTranslate);
    static bool sortByXIntersection(const Rect& crP1, const Rect& crP2);
  private:
    Vector2<int32_t> mPos;
    Vector2<int32_t> mSize;
    lg::Color mRgba;
};

#endif