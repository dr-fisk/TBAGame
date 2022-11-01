#ifndef FONT_H
#define FONT_H

#include "common.h"
#include "Rectangle.h"
#include "png.h"

class Font {
  public:
  Font() {}
    Font(std::string pngFilePath);
    ~Font();
    std::vector<Rect> operator[](const char &rhs);
  private:
    void initCharVecSize();
    void insertFontData( uint8_t pixelPos, uint8_t currLetter, std::vector<Rect> &data);

// needs to be rects
    std::map<char, std::vector<Rect>> fontData;
};

#endif