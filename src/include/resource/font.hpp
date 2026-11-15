#ifndef FONT_HPP
#define FONT_HPP

#include <vector>
#include <memory>
#include <cstdint>

#include "color.hpp"
#include "lestttf/lestTtf.hpp"
#include "utility/edgeTypeDefs.hpp"
#include "renderEngine/texture2D.hpp"
#include "glm/vec2.hpp"

class Font
{
  public:
    //! @brief Default Constructor
    Font() = default;

    //! @brief Constructs Font
    //!
    //! Stores Data needed to resize glyphs
    //!
    //! @param[in] crTtfPath     Path to ttf File
    //! @param[in] cNumOfSubDivs Number of subdivisions for bezier curve generation
    //!
    //! @return Font Object
    void loadFromFile(const std::string& crTtfPath, const uint32_t cNumSubDivs=1);

    //! @brief Default Destructor
    ~Font() = default;
    
    //! @brief Deleted Copy Constructor
    Font(const Font& rhs) = delete;

    //! @brief Gets bitmap data of given character and font size
    //!
    //! @param[in] cCharSize Size of character to grab bitmap from
    //! @param[in] cChar     Character to grab bitmap from
    //!
    //! @return Bitmap data
    std::vector<uint32_t> getData(const uint8_t cCharSize, const char cChar) const;

    //! @brief Gets character dimensions for given character and size
    //!
    //! @param[in] cCharSize Size of character to get dimensions from
    //! @param[in] cChar     Character to get dimensions from
    //!
    //! @return Dimensions of character in Vector2 format
    glm::uvec2 getCharacterDimensions(const uint8_t cCharSize, const char cChar) const;

    //! @brief Generate outline of glyph
    //!
    //! TODO: Remove as this does not go here
    //!
    //! @param[in] cChar     Character to rasterize
    //! @param[in] cCharSize Font Size to generate glyph
    void fillGeneratedPointColor(const char cChar, const uint8_t cCharSize);

    //! @brief Fills polygon with a Seed Fill TODO: Add seed coordinate
    //!
    //! TODO: This does not belong here
    //!
    //! @param[in] cChar     Character to rasterize
    //! @param[in] cCharSize Font Size of glyph
    void fillColor(const char cChar, const uint8_t cCharSize);

    void writeGenPoints(const char cChar, const uint8_t cCharSize);

    //! @brief Deleted assignment operator
    Font& operator=(const Font& rhs) = delete;

    //! @brief Gets YHint from character in font size map
    //!
    //! @param[in] cChar     Character to grab YHint from
    //! @param[in] cCharSize Character size to grab YHint from
    //!
    //! @return YHint
    int32_t getYHint(const char cChar, const uint8_t cCharSize) const;

    //! @brief Gets LeftSideBearing from character in font size map
    //!
    //! @param[in] cChar     Character to grab LeftSideBearing from
    //! @param[in] cCharSize Character size to grab LeftSideBearing from
    //!
    //! @return LeftSideBearing
    int16_t getLeftSideBearing(const char cChar, const uint8_t cCharSize) const;

    //! @brief Gets Advance Width from character in font size map
    //!
    //! @param[in] cChar     Character to grab Advance Width from
    //! @param[in] cCharSize Character size to grab Advance Width from
    //!
    //! @return Advance Width
    int16_t getAdvancedWidth(const char cChar, const uint8_t cCharSize) const;

    //! @brief Loads glyph data for given character size
    //!
    //! @param[in] cCharSize      Size of character to load Glyphs
    //! @param[in] prResourceMngr Resource Manager
    void loadGlyphs(const uint32_t cCharSize) const;

    //! @brief Determines if Font has been loaded with given Char Size
    //!
    //! @param[in] cCharSize Character size to check against map
    //!
    //! @return true if glyphs are loaded
    //! @return false if glyphs are not loaded
    bool hasGlyphsLoaded(const uint8_t cCharSize) const;

    //! @brief Get Offset from FontTable of character size
    //!        This offset will be used to determine texture coordinates
    //!
    //! @param[in] cChar     Character to grab offset from
    //! @param[in] cCharSize Character size to get character offset from specific map
    //!
    //! @return Offset for Texture buffer
    glm::uvec2 getOffset(const char cChar, const uint8_t cCharSize) const;

    //! @brief Get Texture from Texture map of character size
    //!
    //! @param[in] cCharSize Character size to get resource from specific map
    //!
    //! @return Texture
    const Texture2D& getTexture(const uint8_t cCharSize) const;

    //! @brief Returns the Advanced Width value
    //!
    //! @param[in] cCharSize Character size to get resource from specific map
    //!
    //! @return Advanced Width
    uint16_t getAdvancedWidth(const uint8_t cCharSize) const;

    //! @brief Gets Capital Height
    //!
    //! @param[in] cCharSize Character size to get resource from specific map
    //!
    //! @return Capital Height
    int32_t getCapitalHeight(const uint8_t cCharSize) const;
    
    //! @brief Gets Max Height
    //!
    //! @param[in] cCharSize Character size to get resource from specific map
    //!
    //! @return Max Height
    int32_t getMaxHeight(const uint8_t cCharSize) const;

    //! @brief Gets Max Width
    //!
    //! @param[in] cCharSize Character size to get resource from specific map
    //!
    //! @return Max Width
    int32_t getMaxWidth(const uint8_t cCharSize) const;
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

    //! @brief Updates the number of contours provided from ttf with the bezier curve points considered
    //!
    //! @param[in] cChar Character to perform operations for
    void updateNumberOfContours(const char cChar);

    //! @brief Generates Points as hinted by Ttf File
    //!
    //! @param[in] cChar Character to generate glyph points
    //!
    //! @return Number of points generated
    int32_t generateGlyphPoints(const char cChar);

    //! @brief Generates edges from Generated Points
    //!
    //! @param[in] cChar     Character to generate edges for
    //! @param[in] cCharSize Size of character to generate edges for
    void generateEdges(const char cChar, const uint8_t cCharSize) const;

    //! @brief Fills in bitmap for glyph using scanline fill algorithm
    //!
    //! Applies Sub-Pixel AA
    //!
    //! @param[in] cChar     Character to rasterize
    //! @param[in] cCharSize Font Size to generate glyph
    void scanLineFill(const char cChar, const uint8_t cCharSize) const;

    //! @brief Reads in TTF file data
    //!
    //! @param[in] crPath  Path to TTF file
    //! @param[out] rTtf   Object that stores data read from TTF file
    void readTtfFile(const std::string& crPath, LestTrueType& rTtf);

    //! @brief Generates Glyf Data for given character
    //!
    //! @param[in] cChar Character to generate Glyf Data for
    void generateGlyfData(const char cChar);

    //! @brief Updates edges scaled down to cCharSize
    //!
    //! @param[in] cChar     Character to scale down edges
    //! @param[in] cCharSize Size to scale down edges
    void updateEdges(const char cChar, const uint8_t cCharSize) const;

    //! @brief Grabs GlyfHeader for given character
    //!
    //! @param[in] cChar Character to grab GlyfHeaader for
    //! @param[in] crTtf TTF object containing Glyf data
    //!
    //! @return GlyfHeader for given Character
    GlyfHeader getCharGlyfHeader(const char cChar, const LestTrueType& crTtf);

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
    int16_t mXHeight = 0;
    uint16_t mAdvancedWidth = 0;
    uint16_t mUnitsPerEm = 0;
    uint16_t mSmallestPointSize = 0;
    std::string mFontFamily;
};

#endif