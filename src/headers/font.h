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
    Font(const std::string& crTtfPath, const uint32_t cNumSubDivs=1, const lg::Color cColor=lg::White,
         const uint32_t cPixelDim=8);
    ~Font();
    std::vector<uint32_t> operator[](const char cChar);
    Vector2<int32_t> getCharacterDimensions(const char cChar);
    void fillGeneratedPointColor(const char cChar);
    void fillColor(const char cChar);
    void writeGenPoints(const char cChar);
    Font& operator=(const Font &rhs);
    int32_t getYBearing(const char cChar);
  private:
    struct FontMetaData
    {
      int32_t Ybearing;
      GlyfHeader FontHeader;
      std::vector<Vector2<float>> GeneratedPoints;
      std::vector<uint32_t> Bitmap;
      Vector2<int32_t> Dimensions;
      std::vector<Edges<float>> GenPtsEdges;
      std::vector<int32_t> ContourEnds;
    };

    void updateNumberOfContours(const char cChar);
    int32_t generateGlyphPoints(const char cChar);
    void generateEdges(const char cChar);
    void scanLineFill(const char cChar);
    void readTtfFile(const std::string& crPath);
    void generateFont(const uint32_t cPixelDim);
    void updateEdges(const char cChar, const uint32_t cPixelDim);

    std::map<char, FontMetaData> mFont;
    uint32_t mNumSubDiv;
    lg::Color mFontColor;
    GLfloat mPixelDimensions;
    int32_t mCapHeight;
};

#endif