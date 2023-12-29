#ifndef FONT_H
#define FONT_H

#include <vector>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vector.h"
#include "color.h"
#include "lestTtf.h"
#include "utility/net_utility.h"
#include "utility/plot_utility.h"
#include "renderEngine/texture.h"
#include "renderEngine/renderEngine.h"
#include "resource/textureResource.h"

class Font
{
  public:
    Font() = default;
    Font(const std::string& crTtfPath, const uint32_t cNumSubDivs=1, const lg::Color cColor=lg::Black);
    ~Font() = default;
    Font(const Font& rhs) = delete;
    std::vector<uint32_t> getData(const uint8_t cCharSize, const char cChar);
    Vector2<uint32_t> getCharacterDimensions(const uint8_t cCharSize, const char cChar);
    void fillGeneratedPointColor(const char cChar, const uint8_t cCharSize);
    void fillColor(const char cChar, const uint8_t cCharSize);
    void writeGenPoints(const char cChar, const uint8_t cCharSize);
    Font& operator=(const Font& rhs) = delete;
    int32_t getYBearing(const char cChar, const uint8_t cCharSize);
    int32_t getYDescent(const char cChar, const uint8_t cCharSize);
    void loadGlyphs(const uint32_t cCharSize, std::shared_ptr<RenderEngine>& prRenderEngine);
    bool hasGlyphsLoaded(const uint8_t cCharSize);
    Vector2<uint32_t> getOffset(const char cChar, const uint8_t cCharSize);
    std::shared_ptr<TextureResource> getResource(const uint8_t cCharSize);
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
      Vector2<uint32_t> Dimensions;
      std::vector<Edges<float>> GenPtsEdges;
      Texture GlyfTexture;
      Vector2<uint32_t> Offset;
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
    std::map<uint8_t, std::shared_ptr<TextureResource>> mTextures;
    uint32_t mNumSubDiv;
    lg::Color mFontColor;
    int32_t mCapHeight;
    int32_t mMaxWidth;
    std::string mFontFamily;
};

#endif