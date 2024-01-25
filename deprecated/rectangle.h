#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "common.h"
#include "glcommon.h"
#include "resource/textureResource.h"

const uint8_t PIXEL_SIZE = 1;

class Rect
{
  public:
    Rect();
    Rect(const float cLeft, const float cTop, const float cHeight=1, const float cWidth=1);
    Rect(const Vector2<float>& cPos, const float cHeight=1, const float cWidth=1);
    virtual ~Rect();
    void getDimensions(GLfloat *pLeft, GLfloat *pTop, GLfloat *pWidth, GLfloat *pHeight);
    void setPos(const float cLeft, const float cTop);
    void setPos(const Vector2<float>& crPos);
    void setSize(const Vector2<float>& crSize);
    void movePos(const float cLeft, const float cTop);
    float getLeft() const;
    float getTop() const;
    Vector2<float> getPos() const;
    void rotate(GLfloat theta);
    Vector2<GLfloat> getTranslate();
    void translate(Vector2<GLfloat>& rTranslate);
  private:
    Vector2<float> mPos;
    Vector2<float> mSize;
};

#endif