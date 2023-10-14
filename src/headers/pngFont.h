#ifndef PNG_FONT_H
#define PNG_FONT_H

#include "common.h"
#include "drawable/rectangle.h"
#include "png.h"

struct FontAttrib {
  int8_t glyphLeft;
  int8_t glyphTop;
  int8_t glyphRight;
  int8_t glyphBottom;
};

class PngFont {
  public:
  PngFont() {}
    PngFont(const std::string &crPngFilePath);
    ~PngFont();
    std::vector<Rect> operator[](const char &crRhs);
  private:
    void initCharVecSize();
    void insertFontData(const uint8_t cPixelPos, const uint8_t cCurrLetter, const std::vector<Rect> &crData);

    std::map<char, std::vector<Rect>> mFontData;
    std::map<char, FontAttrib> mFontAttribute;
};

#endif