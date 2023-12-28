#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "common.h"
#include "glcommon.h"
#include "drawable/drawable.h"
#include "resource/textureResource.h"

const uint8_t PIXEL_SIZE = 1;

class Rect : public Drawable
{
  public:
    Rect();
    Rect(const float cLeft, const float cTop, const float cHeight=1, const float cWidth=1,
         const lg::Color& crColor=lg::Black);
    Rect(const Vector2<float>& cPos, const float cHeight=1, const float cWidth=1);
    virtual ~Rect();
    void getDimensions(GLfloat *pLeft, GLfloat *pTop, GLfloat *pWidth, GLfloat *pHeight);
    void setColor(const uint8_t cRed, const uint8_t cGreen, const uint8_t cBlue, const uint8_t cAlpha=255);
    void setColor(const lg::Color cColor);
    void setPos(const float cLeft, const float cTop);
    void setPos(const Vector2<float>& crPos);
    void setSize(const Vector2<float>& crSize);
    void movePos(const float cLeft, const float cTop);
    float getLeft() const;
    float getTop() const;
    Vector2<float> getPos() const;
    lg::Color getRGBA();
    Vertex createVertex();
    std::vector<Vertex> getVertex();
    TextureResource& getResource() {}
    virtual std::vector<VertexData> getVertexData() { return std::vector<VertexData>();}
    void rotate(GLfloat theta);
    Vector2<GLfloat> getTranslate();
    void translate(Vector2<GLfloat>& rTranslate);
    static bool sortByXIntersection(const Rect& crP1, const Rect& crP2);
    static void SetVertexTextureIndex(Vertex &rData, const float cTextureIndex=-1.0f);
  private:
    Vector2<float> mPos;
    Vector2<float> mSize;
    lg::Color mRgba;
    PrimitiveType mPrimitiveType;
};

#endif