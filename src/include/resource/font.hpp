#ifndef FONT_HPP
#define FONT_HPP

#include <vector>
#include <memory>
#include <cstdint>

#include "color.hpp"
#include "lestTtf.h"
#include "utility/plot_utility.hpp"
#include "renderEngine/texture.hpp"
#include "renderEngine/renderEngine.hpp"
#include "resource/textureResource.hpp"
#include "glm/vec2.hpp"

class Font
{
  public:
    Font() = default;
    Font(const std::string& crTtfPath, const uint32_t cNumSubDivs=1);
    ~Font() = default;
    Font(const Font& rhs) = delete;
    std::vector<uint32_t> getData(const uint8_t cCharSize, const char cChar);
    glm::uvec2 getCharacterDimensions(const uint8_t cCharSize, const char cChar);
    void fillGeneratedPointColor(const char cChar, const uint8_t cCharSize);
    void fillColor(const char cChar, const uint8_t cCharSize);
    void writeGenPoints(const char cChar, const uint8_t cCharSize);
    Font& operator=(const Font& rhs) = delete;
    int32_t getYBearing(const char cChar, const uint8_t cCharSize);
    int32_t getYDescent(const char cChar, const uint8_t cCharSize);
    void loadGlyphs(const uint32_t cCharSize, std::shared_ptr<RenderEngine>& prRenderEngine);
    bool hasGlyphsLoaded(const uint8_t cCharSize);
    glm::uvec2 getOffset(const char cChar, const uint8_t cCharSize);
    std::shared_ptr<TextureResource> getResource(const uint8_t cCharSize);
    uint16_t getAdvancedWidth();
    int32_t getCapitalHeight();
    int32_t getMaxHeight();
    int32_t getMaxWidth();
  private:
    struct GlyfRawData
    {
      GlyfHeader FontHeader;
      std::vector<glm::vec2> GeneratedPoints;
      std::vector<int32_t> Contours;
    };

    struct FontPage
    {
      int32_t Ybearing;
      int32_t Ydescent;
      std::vector<uint32_t> Bitmap;
      glm::uvec2 Dimensions;
      std::vector<Edges<glm::vec2>> GenPtsEdges;
      glm::uvec2 Offset;
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
    int32_t mCapHeight;
    int32_t mMaxWidth;
    int32_t mMaxHeight;
    uint16_t mAdvancedWidth;
    std::string mFontFamily;
};

#endif