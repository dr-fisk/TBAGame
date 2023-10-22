#ifndef FONT_H
#define FONT_H

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vector.h"
#include "color.h"
#include "lestTtf.h"
#include "net_utility.h"
#include "plot_utility.h"

class Font
{
  public:
    Font();
    Font(std::string ttfPath, const uint32_t cNumSubDivs=1, const lg::Color cColor=lg::White, const uint32_t cPixelDim=8);
    ~Font();
    std::vector<uint32_t> operator[](const char cChar);
    Vector2<int32_t> getCharacterDimensions(const char cChar);
    void fillGeneratedPointColor(const char cChar);
    void fillColor(const char cChar);
    void writeGenPoints(const char cChar);
  private:
    struct FontMetaData
    {
      std::vector<Vector2<float>> GeneratedPoints;
      std::vector<uint32_t> Bitmap;
      GlyfHeader FontHeader;
      Vector2<int32_t> Dimensions;
      std::vector<Edges<float>> GenPtsEdges;
      std::vector<int32_t> ContourEnds;
    };

    void updateNumberOfContours(const char cChar);
    int32_t generateGlyphPoints(const char cChar);
    void generateEdges(const char cChar);
    void scanLineFill(const char cChar);

    std::map<char, FontMetaData> mFont;
    uint32_t mNumSubDiv;
    lg::Color mFontColor;
    GLfloat mPixelDimensions;
};

#endif