#ifndef COLOR_H
#define COLOR_H

#include "common.h"
#include "glcommon.h"

namespace lg {
class Color {
  public:
    Color(const GLfloat cRed, const GLfloat cGreen, GLfloat cBlue, const GLfloat cAlpha=255.0f) {
      mRed = cRed / 255.0f;
      mGreen = cGreen / 255.0f;
      mBlue = cBlue / 255.0f;
      mAlpha = cAlpha / 255.0f;
    }
    Color(const Color &crRhs){*this = crRhs;}
    Color(){}
    ~Color(){}
    GLfloat getRed() const {return mRed;}
    GLfloat getGreen() const {return mGreen;}
    GLfloat getBlue() const {return mBlue;}
    GLfloat getalpha(){return mAlpha;}
    Color& operator=(const Color &crRhs) {
      mRed = crRhs.mRed;
      mGreen = crRhs.mGreen;
      mBlue = crRhs.mBlue;
      mAlpha = crRhs.mAlpha;
      return *this;
    }

    bool operator==(const Color &crRhs)
    {
      return (mRed == crRhs.getRed()) && (mBlue == crRhs.getBlue()) && (mGreen == crRhs.getGreen());
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
    static const Color Grey;
  private:
    GLfloat mRed;
    GLfloat mGreen;
    GLfloat mBlue;
    GLfloat mAlpha;
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
  const Color Grey = Color(128.0f, 128.0f, 128.0f);
}



#endif