#ifndef VECTOR2F_H
#define VECTOR2F_H

#include "common.h"

class Vector2f {
  public:
    Vector2f(GLfloat xPos, GLfloat yPos) {x = xPos; y = yPos;}
    Vector2f(){}
    ~Vector2f(){}
    GLfloat getXPos(){return x;}
    GLfloat getYPos(){return y;}
    Vector2f& operator=(const Vector2f &rhs){x = rhs.x; y = rhs.y; return *this;}
    bool operator==(const Vector2f &rhs){return (x == rhs.x) && (y == rhs.y);}
  private:
    GLfloat x;
    GLfloat y;
};

class Vector2i {
  public:
    Vector2i(uint32_t xPos, uint32_t yPos) {x = xPos; y = yPos;}
    Vector2i(){}
    ~Vector2i(){}
    uint32_t getXPos(){return x;}
    uint32_t getYPos(){return y;}
    Vector2i& operator=(const Vector2i &rhs){x = rhs.x; y = rhs.y; return *this;}
    bool operator==(const Vector2i &rhs){return (x == rhs.x) && (y == rhs.y);}
  private:
    uint32_t x;
    uint32_t y;
};

#endif