#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

namespace lg {
class Color {
  public:
    Color(const uint8_t cRed, const uint8_t cGreen, uint8_t cBlue, const uint8_t cAlpha=255) {
      mRGBA = cAlpha;
      mRGBA <<= 24;
      mRGBA |= (0x000000ff & cBlue) << 16;
      mRGBA |= (0x000000ff & cGreen) << 8;
      mRGBA |= (0x000000ff & cRed);
    }
    Color(const Color &crRhs){*this = crRhs;}
    Color(){}
    ~Color(){}
    uint8_t getAlpha() const {return (mRGBA & 0xff000000) >> 24;}
    uint8_t getBlue() const {return (mRGBA & 0x00ff0000) >> 16;}
    uint8_t getGreen() const {return (mRGBA & 0x0000ff00) >> 8;}
    uint8_t getRed() const {return (mRGBA & 0x000000ff);}
    uint32_t getRgba() const {return mRGBA;}
    Color& operator=(const Color &crRhs) {
      mRGBA = crRhs.mRGBA;
      return *this;
    }

    bool operator==(const Color &crRhs) const
    {
      return crRhs.mRGBA == mRGBA; 
    }

    bool operator==(const uint32_t crRhs) const
    {
      return crRhs == mRGBA; 
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
    static const Color Transparent;
  private:
    uint32_t mRGBA;
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
  const Color Transparent = Color(0.0f, 0.0f, 0.0f, 0.0f);
}



#endif