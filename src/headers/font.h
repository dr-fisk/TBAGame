#ifndef FONT_H
#define FONT_H

#include "common.h"
#include "lestTtf.h"
#include "drawable/rectangle.h"
#include "bitmap.h"

class Font
{
  public:
    Font();
    Font(std::string ttfPath, const uint32_t cNumSubDivs=1, const lg::Color cColor=lg::White, const uint32_t cPixelDim=8);
    ~Font();
    std::vector<Vector2<int32_t>> operator[](const char cLetter);
    Vector2<int32_t> getCharacterMaxCoords(const char cLetter);
  private:
    struct FontMetaData
    {
      std::vector<Vector2<int32_t>> GeneratedPoints;
      GlyfHeader FontHeader;
      Vector2<int32_t> MaxCoords;
      int32_t StartingPoint;
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