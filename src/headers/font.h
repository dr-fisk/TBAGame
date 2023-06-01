#ifndef FONT_H
#define FONT_H

#include "common.h"
#include "lestTtf.h"
#include "rectangle.h"
#include "bitmap.h"

class Font
{
  public:
    Font();
    Font(std::string ttfPath, const uint32_t cNumSubDivs=1, const lg::Color cColor=lg::White, const uint32_t cPixelDim=8);
    ~Font();
    std::vector<std::shared_ptr<Rect>> operator[](const char cLetter);
  private:
    struct FontMetaData
    {
      Bitmap FontBitmap;
      GlyfHeader FontHeader;
      Vector2<int32_t> MaxCoords;
    };

    void updateNumberOfContours(const char cLetter, std::vector<uint16_t> &rContours);
    void generateGlyphPoints(const char cLetter, std::vector<Vector2<int32_t>>& rPoints);
    void connectEdges(std::vector<Vector2<int32_t>>& rPoints, const std::vector<uint16_t>& crContourEnds);
    int32_t getStartingPoint(const char cLetter, const std::vector<Vector2<int32_t>>& crPoints);

    std::map<char, FontMetaData> mFont;
    uint32_t mNumSubDiv;
    lg::Color mFontColor;
    GLfloat mPixelDimensions;
};

#endif