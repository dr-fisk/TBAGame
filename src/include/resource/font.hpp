#ifndef FONT_HPP
#define FONT_HPP

#include <vector>
#include <memory>
#include <cstdint>

#include "color.hpp"
#include "lestTtf.h"
#include "utility/plot_utility.hpp"
#include "renderEngine/texture2D.hpp"
#include "glm/vec2.hpp"

class Font
{
  public:
    Font() = default;
    void loadFromFile(const std::string& crTtfPath, const uint32_t cNumSubDivs=1);
    ~Font() = default;
    Font(const Font& rhs) = delete;
    std::vector<uint32_t> getData(const uint8_t cCharSize, const char cChar) const;
    glm::uvec2 getCharacterDimensions(const uint8_t cCharSize, const char cChar) const;
    void fillGeneratedPointColor(const char cChar, const uint8_t cCharSize);
    void fillColor(const char cChar, const uint8_t cCharSize);
    void writeGenPoints(const char cChar, const uint8_t cCharSize);
    Font& operator=(const Font& rhs) = delete;
    int32_t getYBearing(const char cChar, const uint8_t cCharSize) const;
    int32_t getYDescent(const char cChar, const uint8_t cCharSize) const;
    void loadGlyphs(const uint32_t cCharSize) const;
    bool hasGlyphsLoaded(const uint8_t cCharSize) const;
    glm::uvec2 getOffset(const char cChar, const uint8_t cCharSize) const;
    const Texture2D& getTexture(const uint8_t cCharSize) const;
    uint16_t getAdvancedWidth() const;
    int32_t getCapitalHeight() const;
    int32_t getMaxHeight() const;
    int32_t getMaxWidth() const;
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
    void generateEdges(const char cChar, const uint8_t cCharSize) const;
    void scanLineFill(const char cChar, const uint8_t cCharSize) const;
    void readTtfFile(const std::string& crPath, LestTrueType& rTtf);
    void generateGlyfData(const char cChar);
    void updateEdges(const char cChar, const uint8_t cCharSize) const;
    GlyfHeader getCharGlyfHeader(const char cChar, const LestTrueType& crTtf);
    void getFontScale(const char cChar, float& rScaleX, float& rScaleY) const;

    // Character raw generated point data, use this to generate new edges with the given size
    typedef std::map<char, FontPage> FontTable;
    mutable std::map<char, GlyfRawData> mGlyfData;
    mutable std::map<uint8_t, FontTable> mFont;
    mutable std::map<uint8_t, Texture2D> mTextures;
    uint32_t mNumSubDiv;
    int32_t mCapHeight;
    int32_t mMaxWidth;
    int32_t mMaxHeight;
    int32_t mLeftSideBearing;
    int32_t mRightSideBearing;
    int32_t mAscender;
    int32_t mDescender;
    uint16_t mAdvancedWidth;
    float mUpm;
    std::string mFontFamily;
};

#endif