#ifndef VECTOR4F_H
#define VECTOR4F_H

#include "common.h"

class Vector4f {
  public:
    Vector4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {red = r; green = g; blue = b; alpha = a;}
    Vector4f(){}
    ~Vector4f(){}
    GLfloat getRed(){return red;}
    GLfloat getGreen(){return green;}
    GLfloat getBlue(){return blue;}
    GLfloat getalpha(){return alpha;}
    Vector4f& operator=(const Vector4f &rhs){red = rhs.red; green = rhs.green; blue = rhs.blue; alpha = rhs.alpha; return *this;}
  private:
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat alpha;
};

#endif