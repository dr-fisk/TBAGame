#ifndef FONT_H
#define FONT_H

#include "common.h"
#include "Rectangle.h"
#include "png.h"

class Font {
  public:
  Font() {}
    Font(GLfloat wWidth, GLfloat wHeight, std::string pngFilePath);
    ~Font();
    std::vector<RectVertexData> operator[](const char &rhs);
  private:
    void initCharVecSize();
    void insertFontData( uint8_t pixelPos, uint8_t currLetter, std::vector<RectVertexData> &data);

    std::map<char, std::vector<RectVertexData>> fontData;
};

#endif