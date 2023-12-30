#ifndef PNG_FONT_H
#define PNG_FONT_H

#include <map>
#include <string>

#include "drawable/rectangle.h"
#include "utility/net_utility.h"

struct FontAttrib {
  int8_t glyphLeft;
  int8_t glyphTop;
  int8_t glyphRight;
  int8_t glyphBottom;
};

class PngFont
{
  public:
  PngFont() {}
    PngFont(const std::string &crPngFilePath);
    ~PngFont();
    std::vector<Vertex> operator[](const char &crRhs);
  private:
    void initCharVecSize();
    void insertFontData(const uint8_t cPixelPos, const uint8_t cCurrLetter, const std::vector<Vertex> &crData);

    std::map<char, std::vector<Vertex>> mFontData;
    std::map<char, FontAttrib> mFontAttribute;
};

#endif