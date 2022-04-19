#ifndef COLOR_H
#define COLOR_H

#include "common.h"
namespace lg {
class Color {
  public:
    Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f) {
      red = r / 255.0f;
      green = g / 255.0f;
      blue = b / 255.0f;
      alpha = a;
    }
    Color(){}
    ~Color(){}
    GLfloat getRed(){return red;}
    GLfloat getGreen(){return green;}
    GLfloat getBlue(){return blue;}
    GLfloat getalpha(){return alpha;}
    Color& operator=(const Color &rhs) {
      this->red = rhs.red;
      this->green = rhs.green;
      this->blue = rhs.blue;
      this->alpha = rhs.alpha;
      return *this;
    }

    static const Color Red;
    static const Color Black;
    static const Color White;
    static const Color Orange;
    static const Color Blue;
    static const Color Green;
    static const Color Yellow;
    static const Color Purple;
    static const Color Pink;
  private:
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat alpha;
};
  const Color Red = Color(255.0f, 0.0f, 0.0f);
  const Color Black = Color(0.0f, 0.0f, 0.0f);
  const Color Blue = Color(0.0f, 0.0f, 255.0f);
  const Color White = Color(255.0f, 255.0f, 255.0f);
  const Color Orange = Color(255.0f, 153.0f, 51.0f);
  const Color Yellow = Color(255.0f, 255.0f, 0.0f);
  const Color Green = Color(0.0f, 255.0f, 0.0f);
  const Color Purple = Color(204.0f, 0.0f, 204.0f);
  const Color Pink = Color(255.0f, 153.0f, 204.0f);
}



#endif