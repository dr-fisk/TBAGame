#ifndef FONT_H
#define FONT_H

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vector2D.h"
#include "color.h"
#include "lestTtf.h"
#include "net_utility.h"

class Font
{
  public:
    Font();
    Font(std::string ttfPath, const uint32_t cNumSubDivs=1, const lg::Color cColor=lg::White, const uint32_t cPixelDim=8);
    ~Font();
    std::vector<Vector2<int32_t>> operator[](const char cLetter);
    Vector2<int32_t> getCharacterMaxCoords(const char cLetter);
    void writeCharDataToFile(const char cLetter);
    void fillGeneratedPointColor(const char cCharacter);
    void fillColor(const char cCharacter);
  private:
    struct FontMetaData
    {
      std::vector<Vector2<int32_t>> GeneratedPoints;
      std::vector<uint32_t> ColorMap;
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