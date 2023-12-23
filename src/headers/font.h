#ifndef FONT_H
#define FONT_H

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vector.h"
#include "color.h"
#include "lestTtf.h"
#include "utility/net_utility.h"
#include "utility/plot_utility.h"
#include "drawable/texture.h"

class Font
{
  public:
    Font();
    Font(const std::string& crTtfPath, const uint32_t cNumSubDivs=1, const lg::Color cColor=lg::Black);
    ~Font();
    std::vector<uint32_t> operator[](const char cChar);
    Vector2<int32_t> getCharacterDimensions(const char cChar);
    void fillGeneratedPointColor(const char cChar);
    void fillColor(const char cChar);
    void writeGenPoints(const char cChar);
    Font& operator=(const Font &rhs);
    int32_t getYBearing(const char cChar);
    int32_t getYDescent(const char cChar);
    void updateFontTextures(const uint32_t cCharSize);
    int32_t getTexture(const char cChar);
  private:
    struct FontMetaData
    {
      int32_t Ybearing;
      int32_t Ydescent;
      GlyfHeader FontHeader;
      std::vector<Vector2<float>> GeneratedPoints;
      std::vector<uint32_t> Bitmap;
      Vector2<int32_t> Dimensions;
      std::vector<Edges<float>> GenPtsEdges;
      std::vector<int32_t> ContourEnds;
      Texture GlyfTexture;
    };

    void updateNumberOfContours(const char cChar);
    int32_t generateGlyphPoints(const char cChar);
    void generateEdges(const char cChar);
    void scanLineFill(const char cChar);
    void readTtfFile(const std::string& crPath, LestTrueType& rTtf);
    void generateGlyfData(const char cChar);
    void updateEdges(const char cChar, const uint32_t cCharSize);
    GlyfHeader getCharGlyfHeader(const char cChar, LestTrueType& rTtf);

    std::map<char, FontMetaData> mFont;
    uint32_t mNumSubDiv;
    lg::Color mFontColor;
    GLfloat mPixelDimensions;
    int32_t mCapHeight;
    int32_t mMaxWidth;
};

#endif