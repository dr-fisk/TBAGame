#ifndef VECTOR2F_H
#define VECTOR2F_H

#include "common.h"
#include "glcommon.h"

class Vector2f {
  public:
    Vector2f(const GLfloat cXPos, const GLfloat cYPos) {mX = cXPos; mY = cYPos;}
    Vector2f(const Vector2f &crRhs){*this = crRhs;}
    Vector2f(){}
    ~Vector2f(){}
    GLfloat getXPos(){return mX;}
    GLfloat getYPos(){return mY;}
    Vector2f& operator=(const Vector2f &crRhs){mX = crRhs.mX; mY = crRhs.mY; return *this;}
    bool operator==(const Vector2f &crRhs){return (mX == crRhs.mX) && (mY == crRhs.mY);}
  private:
    GLfloat mX;
    GLfloat mY;
};

class Vector2i {
  public:
    Vector2i(const uint32_t cXPos, const uint32_t cYPos) {mX = cXPos; mY = cYPos;}
    Vector2i(const Vector2i &crRhs){*this = crRhs;}
    Vector2i(){}
    ~Vector2i(){}
    uint32_t getXPos(){return mX;}
    uint32_t getYPos(){return mY;}
    Vector2i& operator=(const Vector2i &crRhs){mX = crRhs.mX; mY = crRhs.mY; return *this;}
    bool operator==(const Vector2i &crRhs){return (mX == crRhs.mX) && (mY == crRhs.mY);}
  private:
    uint32_t mX;
    uint32_t mY;
};

#endif