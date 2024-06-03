#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

namespace lg
{
class Color
{
  public:
    Color(const uint32_t cColor)
    {
      mRGBA = cColor;
    }

    Color(const uint8_t cRed, const uint8_t cGreen, uint8_t cBlue, const uint8_t cAlpha=255)
    {
      mRGBA = cAlpha;
      mRGBA <<= 24;
      mRGBA |= (0x000000ff & cBlue) << 16;
      mRGBA |= (0x000000ff & cGreen) << 8;
      mRGBA |= (0x000000ff & cRed);
    }
    Color(const Color &crRhs){*this = crRhs;}
    Color() : mRGBA(0) {}
    ~Color(){}
    uint8_t getAlpha() const {return (mRGBA & 0xff000000) >> 24;}
    uint8_t getBlue() const {return (mRGBA & 0x00ff0000) >> 16;}
    uint8_t getGreen() const {return (mRGBA & 0x0000ff00) >> 8;}
    uint8_t getRed() const {return (mRGBA & 0x000000ff);}
    uint32_t getRgba() const {return mRGBA;}

    void addAlpha(const uint8_t cAlpha)
    {
      uint8_t tempAlpha = (0xff000000 & mRGBA) >> 24;
      tempAlpha += cAlpha;
      mRGBA &= (0x00ffffff);
      mRGBA |= (0x000000ff & tempAlpha) << 24;
    }

    void setAlpha(const uint8_t cAlpha)
    {
      mRGBA &= (0x00ffffff);
      mRGBA |= (0x000000ff & cAlpha) << 24;
    }

    void setRed(const uint8_t cRed)
    {
      mRGBA &= (0xffffff00);
      mRGBA |= (0x000000ff & cRed);
    }

    void setGreen(const uint8_t cGreen)
    {
      mRGBA &= (0xff00ffff);
      mRGBA |= (0x000000ff & cGreen) << 8;
    }

    void setBlue(const uint8_t cBlue)
    {
      mRGBA &= (0xffff00ff);
      mRGBA |= (0x000000ff & cBlue) << 16;
    }

    Color& operator=(const Color &crRhs)
    {
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

    static uint8_t getAlpha(const uint32_t cRgba) { return (0xff000000 & cRgba) >> 24; }
   
    static void setAlpha(uint32_t& rRgba, const uint8_t cAlpha)
    {
      rRgba &= (0x00ffffff);
      rRgba |= (0x000000ff & cAlpha) << 24;
    }

    static void setRed(uint32_t& rRgba, const uint8_t cRed)
    {
      rRgba &= (0xffffff00);
      rRgba |= (0x000000ff & cRed);
    }

    static void setGreen(uint32_t& rRgba, const uint8_t cGreen)
    {
      rRgba &= (0xff00ffff);
      rRgba |= (0x000000ff & cGreen) << 8;
    }

    static void setBlue(uint32_t& rRgba, const uint8_t cBlue)
    {
      rRgba &= (0xffff00ff);
      rRgba |= (0x000000ff & cBlue) << 16;
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