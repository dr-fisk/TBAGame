#ifndef FONT_HPP
#define FONT_HPP

#include <vector>
#include <memory>
#include <cstdint>

#include "color.hpp"
#include "lestTtf.hpp"
#include "utility/edgeTypeDefs.hpp"
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
    int32_t getYHint(const char cChar, const uint8_t cCharSize) const;
    int16_t getLeftSideBearing(const char cChar, const uint8_t cCharSize) const;
    int16_t getAdvancedWidth(const char cChar, const uint8_t cCharSize) const;
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
      LongHorMetric HorMetrics;
      std::vector<glm::vec2> GeneratedPoints;
      std::vector<int32_t> Contours;
    };

    struct FontPage
    {
      std::vector<uint32_t> Bitmap;
      glm::uvec2 Dimensions;
      std::vector<Edges<glm::vec2>> GenPtsEdges;
      glm::uvec2 Offset;
      uint16_t AdvanceWidth;
      int16_t LeftSideBearing;
      int32_t YHint;
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

    typedef std::map<char, FontPage> FontTable;
    mutable std::map<char, GlyfRawData> mGlyfData;
    mutable std::map<uint8_t, FontTable> mFont;
    mutable std::map<uint8_t, Texture2D> mTextures;
    uint32_t mNumSubDiv = 0;
    int32_t mCapHeight = 0;
    int32_t mLowerCaseHeight = 0;
    int32_t mMaxWidth = 0;
    int32_t mMaxHeight = 0;
    int32_t mLeftSideBearing = 0;
    int32_t mRightSideBearing = 0;
    int32_t mAscender = 0;
    int32_t mDescender = 0;
    uint16_t mAdvancedWidth = 0;
    uint16_t mUnitsPerEm = 0;
    uint16_t mSmallestPointSize = 0;
    std::string mFontFamily;
};

#endif