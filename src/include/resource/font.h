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
#include "renderEngine/texture.h"

class Font
{
  public:
    Font() = default;
    Font(const std::string& crTtfPath, const uint32_t cNumSubDivs=1, const lg::Color cColor=lg::Black);
    ~Font() = default;
    std::vector<uint32_t> getData(const uint8_t cCharSize, const char cChar);
    Vector2<int32_t> getCharacterDimensions(const uint8_t cCharSize, const char cChar);
    void fillGeneratedPointColor(const char cChar, const uint8_t cCharSize);
    void fillColor(const char cChar, const uint8_t cCharSize);
    void writeGenPoints(const char cChar, const uint8_t cCharSize);
    Font& operator=(const Font &rhs);
    int32_t getYBearing(const char cChar, const uint8_t cCharSize);
    int32_t getYDescent(const char cChar, const uint8_t cCharSize);
    void loadGlyphs(const uint32_t cCharSize);
    int32_t getTexture(const char cChar, const uint8_t cCharSize);
  private:
    struct GlyfRawData
    {
      GlyfHeader FontHeader;
      std::vector<Vector2<float>> GeneratedPoints;
      std::vector<int32_t> Contours;
    };

    struct FontPage
    {
      int32_t Ybearing;
      int32_t Ydescent;
      std::vector<uint32_t> Bitmap;
      Vector2<int32_t> Dimensions;
      std::vector<Edges<float>> GenPtsEdges;
      Texture GlyfTexture;
    };

    void updateNumberOfContours(const char cChar);
    int32_t generateGlyphPoints(const char cChar);
    void generateEdges(const char cChar, const uint8_t cCharSize);
    void scanLineFill(const char cChar, const uint8_t cCharSize);
    void readTtfFile(const std::string& crPath, LestTrueType& rTtf);
    void generateGlyfData(const char cChar);
    void updateEdges(const char cChar, const uint8_t cCharSize);
    GlyfHeader getCharGlyfHeader(const char cChar, const LestTrueType& crTtf);

    // Character raw generated point data, use this to generate new edges with the given size
    typedef std::map<char, FontPage> FontTable;
    std::map<char, GlyfRawData> mGlyfData;
    std::map<uint8_t, FontTable> mFont;
    // std::map<uint8_t, Texture> mTextures;
    uint32_t mNumSubDiv;
    lg::Color mFontColor;
    int32_t mCapHeight;
    int32_t mMaxWidth;
};

#endif