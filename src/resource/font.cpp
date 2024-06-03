#include <cmath>
#include <algorithm>
#include <fstream>
#include <queue>

#include "resource/font.hpp"
#include "utility/plot_utility.hpp"
#include "utility/edgeTable.hpp"

static const int32_t ASCII_CHAR_START = 32;
static const int32_t ASCII_CHAR_END = 126;
static const uint8_t BASE_SIZE_PX = 16;
static const uint8_t BASE_SIZE_PT = 12;

float calculatePixelSize(const float cFontDimension, const float cPointSize, const uint32_t cUnitsPerEm)
{
  return (cFontDimension * cPointSize * 96.0f) / (72.0f * static_cast<float>(cUnitsPerEm)); 
}

//! @brief Constructs Font
//!
//! Stores Data needed to resize glyphs
//!
//! @param[in] crTtfPath     Path to ttf File
//! @param[in] cNumOfSubDivs Number of subdivisions for bezier curve generation
//!
//! @return Font Object
void Font::loadFromFile(const std::string& crTtfPath, const uint32_t cNumOfSubDivs)
{
  mNumSubDiv = cNumOfSubDivs;

  const char EXTENSION[] = ".ttf";
  int32_t temp2 = -1;

  if(std::string::npos != crTtfPath.find_last_of("/"))
  {
    temp2 = crTtfPath.find_last_of("/");
  }

  temp2 ++;
  mFontFamily = crTtfPath.substr(temp2, crTtfPath.size() - ((sizeof(EXTENSION) - 1) + temp2));

  LestTrueType ttf;
  readTtfFile(crTtfPath, ttf);

  char currChar = '\0';
  for(int32_t i = ASCII_CHAR_START; i <= ASCII_CHAR_END; i ++)
  {
    currChar = static_cast<char>(i);
    mGlyfData[currChar].FontHeader = getCharGlyfHeader(currChar, ttf);
  
    if(mGlyfData[currChar].FontHeader.numberofContours > 0)
    {
      generateGlyfData(currChar);
    }
  }
}

//! @brief Fills in bitmap for glyph using scanline fill algorithm
//!
//! Applies Sub-Pixel AA
//!
//! @param[in] cChar     Character to rasterize
//! @param[in] cCharSize Font Size to generate glyph
//!
//! @return None
void Font::scanLineFill(const char cChar, const uint8_t cCharSize) const
{
  std::cout << cChar << " : " << std::endl;
  EdgeTable::scanLineFill(mFont[cCharSize][cChar].GenPtsEdges, mFont[cCharSize][cChar].Dimensions,
                          mFont[cCharSize][cChar].Bitmap, lg::White, 0, cChar);
}

//! @brief Fills polygon with a Seed Fill TODO: Add seed coordinate
//!
//! TODO: This does not belong here
//!
//! @param[in] cChar     Character to rasterize
//! @param[in] cCharSize Font Size of glyph
//!
//! @return None 
void Font::fillColor(const char cChar, const uint8_t cCharSize)
{
  std::queue<int32_t> visited;
  int32_t currPoint = -1;
  int32_t startingPoint = 0; 
  visited.push(startingPoint);
  mFont[cCharSize][cChar].Bitmap[startingPoint] = lg::White.getRgba();
  int32_t point_below = 0;
  int32_t point_above = 0;
  int32_t point_right = 0;
  int32_t point_left = 0;
  uint32_t num_rows = mFont[cCharSize][cChar].Dimensions.y;
  uint32_t num_cols = mFont[cCharSize][cChar].Dimensions.x;
  const uint32_t color_map_size = mFont[cCharSize][cChar].Bitmap.size();
  glm::vec2 curr_point_coords;
  glm::vec2 point_above_coords;
  glm::vec2 point_below_coords;
  glm::vec2 point_right_coords;
  glm::vec2 point_left_coords;

  // Perform dijkstra's algorithm
  while(!visited.empty())
  {
    currPoint = visited.front();
    visited.pop();
    point_below = currPoint + num_cols;
    point_above = currPoint - num_cols;
    point_right = currPoint + 1;
    point_left = currPoint - 1;
    curr_point_coords = glm::vec2(currPoint % num_cols, currPoint / num_cols);
    point_above_coords = glm::vec2(point_above % num_cols, point_above / num_cols);
    point_below_coords = glm::vec2(point_below % num_cols, point_below / num_cols);
    point_right_coords = glm::vec2(point_right % num_cols, point_right / num_cols);
    point_left_coords = glm::vec2(point_left % num_cols, point_left / num_cols);


    if(point_below < color_map_size && 
       !(lg::White == mFont[cCharSize][cChar].Bitmap[point_below]))
    {
      if(PlotUtility<glm::vec2>::arePointsTouching(point_below_coords, curr_point_coords))
      {
        visited.push(point_below);
        mFont[cCharSize][cChar].Bitmap[point_below] = lg::White.getRgba();
      }
    }

    if(point_above >= 0 && !(lg::White == mFont[cCharSize][cChar].Bitmap[point_above]))
    {
      if(PlotUtility<glm::vec2>::arePointsTouching(point_above_coords, curr_point_coords))
      {
        visited.push(point_above);
        mFont[cCharSize][cChar].Bitmap[point_above] = lg::White.getRgba();
      }
    }

    if(point_right < color_map_size && !(lg::White == mFont[cCharSize][cChar].Bitmap[point_right]))
    {
      if (PlotUtility<glm::vec2>::arePointsTouching(point_right_coords, curr_point_coords))
      {
        visited.push(point_right);
        mFont[cCharSize][cChar].Bitmap[point_right] = lg::White.getRgba();
      }
    }

    if(point_left >= 0 && !(lg::White == mFont[cCharSize][cChar].Bitmap[point_left]))
    {
      if(PlotUtility<glm::vec2>::arePointsTouching(point_left_coords, curr_point_coords))
      {
        visited.push(point_left);
        mFont[cCharSize][cChar].Bitmap[point_left] = lg::White.getRgba();
      }
    }
  }
}

//! @brief Generate outline of glyph
//!
//! TODO: Remove as this does not go here
//!
//! @param[in] cChar     Character to rasterize
//! @param[in] cCharSize Font Size to generate glyph
//!
//! @return None
void Font::fillGeneratedPointColor(const char cChar, const uint8_t cCharSize)
{
  const uint32_t num_cols = mFont[cCharSize][cChar].Dimensions.x;
  int i = 0;
  glm::ivec2 p1 = {0, 0};
  glm::ivec2 p2 = {0, 0};
  
  for (const auto &edge : mFont[cCharSize][cChar].GenPtsEdges)
  {
    p1.x = edge.p1.x;
    p1.y = edge.p1.y;
    p2.x = edge.p2.x;
    p2.y = edge.p2.y;
    PlotUtility<glm::ivec2>::plotLine(p1, p2, mFont[cCharSize][cChar].Bitmap, num_cols, lg::White);
  }
}

//! @brief Updates the number of contours provided from ttf with the bezier curve points considered
//!
//! @param[in] cChar Character to perform operations for
//!
//! @return None
void Font::updateNumberOfContours(const char cChar)
{
  int32_t j = 0;
  uint32_t currIdx = 0;
  int32_t contourStartIdx = 0;
  int32_t genPtsStartIdx = 0;
  int8_t contourStartedOff = 0;
  int8_t contourStart = 0;
  int32_t nextIdx = 0;
  int32_t contourLen = 0;

  for(int32_t i = 0; i < mGlyfData[cChar].FontHeader.numberofContours; i++)
  {
    contourStartIdx = j;
    genPtsStartIdx = currIdx;
    contourStart = 1;
    contourStartedOff = 0;
    for(; j <= mGlyfData[cChar].FontHeader.endPtsOfContours[i]; j ++)
    {
      contourLen = mGlyfData[cChar].FontHeader.endPtsOfContours[i] - contourStartIdx + 1;
      nextIdx = (j + 1 - contourStartIdx) % contourLen + contourStartIdx;

      if(ON_CURVE_POINT & mGlyfData[cChar].FontHeader.flags[j])
      {
        currIdx++;
      }
      else
      {
        if (contourStart)
        {
          contourStartedOff = 1;
          if (ON_CURVE_POINT & mGlyfData[cChar].FontHeader.flags[nextIdx])
          {
            currIdx++;
            j++;
            continue;
          }
          currIdx ++;
        }

        if ((ON_CURVE_POINT & mGlyfData[cChar].FontHeader.flags[nextIdx]))
        {
          j++;
        }
        
        currIdx += mNumSubDiv;
      }

      contourStart = 0;
    }

    // Process last contour point
    if(ON_CURVE_POINT & mGlyfData[cChar].FontHeader.flags[j - 1])
    {
      currIdx++;
    }

    //handle off curve
    if(contourStartedOff)
    {
      currIdx += mNumSubDiv;
    }

    mGlyfData[cChar].Contours[i] = currIdx;
  }
}

//! @brief Generates Points as hinted by Ttf File
//!
//! @param[in] cChar Character to generate glyph points
//!
//! @return Number of points generated
int32_t Font::generateGlyphPoints(const char cChar)
{
  glm::vec2 p0 = {0.0, 0.0};
  glm::vec2 p1 = {0.0, 0.0};
  glm::vec2 p2 = {0.0, 0.0};

  int32_t j = 0;
  uint32_t currIdx = 0;
  int32_t xPos = 0.0f;
  int32_t yPos = 0.0f;
  int32_t contourStartIdx = 0;
  int32_t genPtsStartIdx = 0;
  int8_t contourStartedOff = 0;
  int8_t contourStart = 0;
  int32_t nextIdx = 0;
  int32_t contourLen = 0;
  glm::vec2 minCoord = glm::vec2(mGlyfData[cChar].FontHeader.xMin,
                                               mGlyfData[cChar].FontHeader.yMin);
  glm::vec2 maxCoord = glm::vec2(mGlyfData[cChar].FontHeader.xMax,
                                               mGlyfData[cChar].FontHeader.yMax);
  GLfloat yShift = -maxCoord.y;

  for(int32_t i = 0; i < mGlyfData[cChar].FontHeader.numberofContours; i++)
  {
    contourStartIdx = j;
    genPtsStartIdx = currIdx;
    contourStart = 1;
    contourStartedOff = 0;
    for(; j <= mGlyfData[cChar].FontHeader.endPtsOfContours[i]; j ++)
    {
      xPos = (mGlyfData[cChar].FontHeader.xCoordinates[j]) - minCoord.x;
      yPos = abs((mGlyfData[cChar].FontHeader.yCoordinates[j]) + yShift);
      contourLen = mGlyfData[cChar].FontHeader.endPtsOfContours[i] - contourStartIdx + 1;
      nextIdx = (j + 1 - contourStartIdx) % contourLen + contourStartIdx;

      if(ON_CURVE_POINT & mGlyfData[cChar].FontHeader.flags[j])
      {
        mGlyfData[cChar].GeneratedPoints[currIdx] = glm::vec2(xPos, yPos);
        currIdx++;
      }
      else
      {

        if (contourStart)
        {
          contourStartedOff = 1;
          if (ON_CURVE_POINT & mGlyfData[cChar].FontHeader.flags[nextIdx])
          {
            mGlyfData[cChar].GeneratedPoints[currIdx] = glm::vec2(
              (mGlyfData[cChar].FontHeader.xCoordinates[nextIdx]) - minCoord.x,
              abs((mGlyfData[cChar].FontHeader.yCoordinates[nextIdx]) + yShift));
            currIdx++;
            j++;
            continue;
          }

          xPos = xPos + ((
            (mGlyfData[cChar].FontHeader.xCoordinates[nextIdx]) - minCoord.x - xPos) / 2.0f);
          yPos = yPos + ((
            abs((mGlyfData[cChar].FontHeader.yCoordinates[nextIdx]) + yShift) - yPos) / 2.0f);
          // I changed the order here, might have effects
          mGlyfData[cChar].GeneratedPoints[currIdx].x = xPos;
          mGlyfData[cChar].GeneratedPoints[currIdx].y = yPos;

          currIdx ++;
        }

        p0 = mGlyfData[cChar].GeneratedPoints[currIdx - 1];
        p1 = glm::vec2(xPos, yPos);
        p2 = glm::vec2((mGlyfData[cChar].FontHeader.xCoordinates[nextIdx]) - minCoord.x,
                              abs((mGlyfData[cChar].FontHeader.yCoordinates[nextIdx]) + yShift)); 

        if (!(ON_CURVE_POINT & mGlyfData[cChar].FontHeader.flags[nextIdx]))
        {
          // Get midpoint between p1 and p2
          p2 = glm::vec2(p1.x + ((p2.x - p1.x) / 2.0f),
                                p1.y + ((p2.y - p1.y) / 2.0f));
        }
        else
        {
          j++;
        }
        
        currIdx += PlotUtility<glm::vec2>::tessellateQuadBezier(mGlyfData[cChar].GeneratedPoints,
                                                              currIdx, mNumSubDiv, p0, p1, p2);
      }

      contourStart = 0;
    }

    // Process last contour point
    if(ON_CURVE_POINT & mGlyfData[cChar].FontHeader.flags[j - 1])
    {
      mGlyfData[cChar].GeneratedPoints[currIdx] = mGlyfData[cChar].GeneratedPoints[genPtsStartIdx];
      currIdx++;
    }

    //handle off curve
    if(contourStartedOff)
    {
      p0 = mGlyfData[cChar].GeneratedPoints[currIdx - 1];
      p1.x = (mGlyfData[cChar].FontHeader.xCoordinates[contourStartIdx]) - minCoord.x;
      p1.y = abs((mGlyfData[cChar].FontHeader.yCoordinates[contourStartIdx]) + yShift);
      p2 = mGlyfData[cChar].GeneratedPoints[genPtsStartIdx];
      currIdx += PlotUtility<glm::vec2>::tessellateQuadBezier(mGlyfData[cChar].GeneratedPoints,
                                                            currIdx, mNumSubDiv, p0, p1, p2);
    }
  }

  return currIdx;
}

//! @brief Generates edges from Generated Points
//!
//! @param[in] cChar     Character to generate edges for
//! @param[in] cCharSize Size of character to generate edges for
//!
//! @return None
void Font::generateEdges(const char cChar, const uint8_t cCharSize) const
{
  int32_t j = 0;
  int32_t edgeIdx = 0;

  for(int32_t i = 0; i < mGlyfData[cChar].Contours.size(); i ++)
  {
    for(; j < mGlyfData[cChar].Contours[i] - 1; j ++)
    {
      mFont[cCharSize][cChar].GenPtsEdges[edgeIdx].p1 = mGlyfData[cChar].GeneratedPoints[j];
      mFont[cCharSize][cChar].GenPtsEdges[edgeIdx].p2 = mGlyfData[cChar].GeneratedPoints[j + 1];
      edgeIdx ++;
    }    
    j ++;
  }
}

//! @brief Gets bitmap data of given character and font size
//!
//! @param[in] cCharSize Size of character to grab bitmap from
//! @param[in] cChar     Character to grab bitmap from
//!
//! @return Bitmap data
std::vector<uint32_t> Font::getData(const uint8_t cCharSize, const char cChar) const
{
    return mFont.at(cCharSize).at(cChar).Bitmap;
}

//! @brief Gets character dimensions for given character and size
//!
//! @param[in] cCharSize Size of character to get dimensions from
//! @param[in] cChar     Character to get dimensions from
//!
//! @return Dimensions of character in Vector2 format
glm::uvec2 Font::getCharacterDimensions(const uint8_t cCharSize, const char cChar) const
{
  return mFont.at(cCharSize).at(cChar).Dimensions;
}

//! TODO: Remove this is debug code
void Font::writeGenPoints(const char cChar, const uint8_t cCharSize)
{
  // std::ofstream fd("GenPoints.txt");

  // fd << "-----------------------------------------------------" << std::endl;
  // fd << "Points for letter: " << cChar << std::endl;
  // fd << "Dimensions: " << mFont[cCharSize][cChar].Dimensions;
  // fd << mGlyfData[cChar].GeneratedPoints.size() << std::endl;
  // int i = 0;
  // for(const auto& pts : mGlyfData[cChar].GeneratedPoints)
  // {
  //   fd << i << ": " << pts;
  //   i++;
  // }
  // fd << "-----------------------------------------------------" << std::endl;
}

//! @brief Gets Ybearing from character in font size map
//!
//! @param[in] cChar     Character to grab Ybearing from
//! @param[in] cCharSize Character size to grab Ybearing from
//!
//! @return Ybearing
int32_t Font::getYBearing(const char cChar, const uint8_t cCharSize) const
{
  return mFont.at(cCharSize).at(cChar).Ybearing;
}

//! @brief Gets Ydescent from character in font size map
//!
//! @param[in] cChar     Character to grab Ydescent from
//! @param[in] cCharSize Character size to grab Ydescent from
//!
//! @return Ydescent
int32_t Font::getYDescent(const char cChar, const uint8_t cCharSize) const
{
  return mFont.at(cCharSize).at(cChar).Ydescent;
}


//! @brief Reads in TTF file data
//!
//! @param[in] crPath  Path to TTF file
//! @param[out] rTtf   Object that stores data read from TTF file
//!
//! @return None
void Font::readTtfFile(const std::string& crPath, LestTrueType &rTtf)
{
  if (-1 == rTtf.read(crPath))
  {
    std::cout << "Ttf failed to read." << std::endl;
    exit(-1);
  }

  if(!rTtf.hasOS2Table())
  {
    std::cout << "Ttf does not contain OS2 Table." << std::endl;
    exit(-1);
  }

  OS2Table os2 = rTtf.getOS2Table();
  HeadHeader head = rTtf.getHeadHeaderTable();
  mCapHeight = os2.sCapHeight;
  mMaxWidth = head.xMax - head.xMin;
  mMaxHeight = head.yMax - head.yMin;
  mUnitsPerEm = head.unitsPerEm;
  HheaHeader hhea = rTtf.getHheaHeader();
  mAdvancedWidth = hhea.advancedWidthMax;
}

//! @brief Generates Glyf Data for given character
//!
//! @param[in] cChar Character to generate Glyf Data for
//!
//! @return None
void Font::generateGlyfData(const char cChar)
{
  if(mGlyfData[cChar].FontHeader.numberofContours > 0)
  {
    mGlyfData[cChar].Contours.resize(mGlyfData[cChar].FontHeader.numberofContours);

    // Update the number of contours for mFont[cCharSize][cChar] to properly allocate memory for generatedPoints
    updateNumberOfContours(cChar);

    // Generate points from TTF file
    mGlyfData[cChar].GeneratedPoints.resize(mGlyfData[cChar].Contours[mGlyfData[cChar].Contours.size() - 1]);
    generateGlyphPoints(cChar);
  }
}

//! @brief Loads glyph data for given character size
//!
//! @param[in] cCharSize      Size of character to load Glyphs
//! @param[in] prResourceMngr Resource Manager
//!
//! @return None
void Font::loadGlyphs(const uint32_t cCharSize) const
{
  // Don't remake font size if it exists in map, return early
  if(mFont.find(cCharSize) != mFont.end())
  {
    std::cout << "Font size already exists." << std::endl;
    // Doesn't matter dimensions here, because font exists, resource already exists
    return;
  }

  char currChar = '\0';
  float scaleY = 0;
  float scaleX = 0;
  glm::uvec2 offset(0, 0);
  const float EM_PCT = static_cast<float>(cCharSize) / static_cast<float>(BASE_SIZE_PX);
  const float PT_SIZE = EM_PCT * BASE_SIZE_PT;

  std::cout << PT_SIZE << std::endl;
  
  for(int32_t i = ASCII_CHAR_START; i <= ASCII_CHAR_END; i ++)
  {
    currChar = static_cast<char>(i);
    mFont[cCharSize][currChar].Dimensions = glm::uvec2(
    calculatePixelSize(mGlyfData[currChar].FontHeader.xMax - mGlyfData[currChar].FontHeader.xMin, PT_SIZE, mUnitsPerEm),
    calculatePixelSize(mGlyfData[currChar].FontHeader.yMax - mGlyfData[currChar].FontHeader.yMin, PT_SIZE, mUnitsPerEm));
      // Correct the right dimensions
    mFont[cCharSize][currChar].Dimensions.x += 1;
    mFont[cCharSize][currChar].Dimensions.y += 1;
    if(mGlyfData[currChar].Contours.size() > 0)
    {
        // If we get a crash with different fonts this can be why
        mFont[cCharSize][currChar].GenPtsEdges.clear();
        mFont[cCharSize][currChar].GenPtsEdges.resize(
        (mGlyfData[currChar].Contours[mGlyfData[
          currChar].Contours.size() - 1] - 1) - (mGlyfData[currChar].Contours.size() - 1));
        // Connect edges together
        generateEdges(currChar, cCharSize);

        mFont[cCharSize][currChar].Ybearing = cCharSize - mFont[cCharSize][currChar].Dimensions.y;

        if(mFont[cCharSize][currChar].Ybearing < 0)
        {
          mFont[cCharSize][currChar].Ybearing = 0;
        }

        updateEdges(currChar, cCharSize);
        mFont[cCharSize][currChar].Bitmap.resize(
          (mFont[cCharSize][currChar].Dimensions.y) * (mFont[cCharSize][currChar].Dimensions.x), lg::Color(255, 255, 255, 0).getRgba());
        scanLineFill(currChar, cCharSize);

        mFont[cCharSize][currChar].Offset = offset;

        offset.x += mFont[cCharSize][currChar].Dimensions.x;
        offset.y += mFont[cCharSize][currChar].Dimensions.y;

        mFont[cCharSize][currChar].Ydescent = abs(cCharSize * (static_cast<float>(mGlyfData[currChar].FontHeader.yMin) /
                                             static_cast<float>(mMaxHeight)));
    }
  }

  mTextures[cCharSize].create(offset.y, offset.x);

  for(int32_t i = ASCII_CHAR_START + 1; i <= ASCII_CHAR_END; i ++)
  {
    currChar = static_cast<char>(i);
    mTextures[cCharSize].update(mFont[cCharSize][currChar].Bitmap.data(), mFont[cCharSize][currChar].Dimensions,
                                 mFont[cCharSize][currChar].Offset);
  }
}

//! @brief Updates edges scaled down to cCharSize
//!
//! @param[in] cChar     Character to scale down edges
//! @param[in] cCharSize Size to scale down edges
//!
//! @return None
void Font::updateEdges(const char cChar, const uint8_t cCharSize) const
{
  const float EM_PCT = static_cast<float>(cCharSize) / static_cast<float>(BASE_SIZE_PX);
  const float PT_SIZE = EM_PCT * BASE_SIZE_PT;
  const float newMaxX = calculatePixelSize(mGlyfData[cChar].FontHeader.xMax - mGlyfData[cChar].FontHeader.xMin, PT_SIZE, mUnitsPerEm) / static_cast<float>(mGlyfData[cChar].FontHeader.xMax - mGlyfData[cChar].FontHeader.xMin);
  const float newMaxY = calculatePixelSize(mGlyfData[cChar].FontHeader.yMax - mGlyfData[cChar].FontHeader.yMin, PT_SIZE, mUnitsPerEm) / static_cast<float>(mGlyfData[cChar].FontHeader.yMax - mGlyfData[cChar].FontHeader.yMin);

  // Scale down points in edges by the scale
  for (auto& edges : mFont[cCharSize][cChar].GenPtsEdges)
  {
    edges.p1.x = (edges.p1.x) * newMaxX;
    edges.p1.y = (edges.p1.y) * newMaxY;
    edges.p2.x = (edges.p2.x) * newMaxX;
    edges.p2.y = (edges.p2.y) * newMaxY;
  }
}

//! @brief Grabs GlyfHeader for given character
//!
//! @param[in] cChar Character to grab GlyfHeaader for
//! @param[in] crTtf TTF object containing Glyf data
//!
//! @return GlyfHeader for given Character
GlyfHeader Font::getCharGlyfHeader(const char cChar, const LestTrueType& crTtf)
{
  GlyfHeader tempHeader;
  crTtf.getSpecifcCharacterOutline(cChar, tempHeader);
  return tempHeader;
}

//! @brief Determines if Font has been loaded with given Char Size
//!
//! @param[in] cCharSize Character size to check against map
//!
//! @return true if glyphs are loaded
//! @return false if glyphs are not loaded
bool Font::hasGlyphsLoaded(const uint8_t cCharSize) const
{
  return mFont.find(cCharSize) != mFont.end();
}

//! @brief Get Offset from FontTable of character size
//!        This offset will be used to determine texture coordinates
//!
//! @param[in] cChar     Character to grab offset from
//! @param[in] cCharSize Character size to get character offset from specific map
//!
//! @return Offset for Texture buffer
glm::uvec2 Font::getOffset(const char cChar, const uint8_t cCharSize) const
{
  return mFont.at(cCharSize).at(cChar).Offset;
}

//! @brief Get Texture from Texture map of character size
//!
//! @param[in] cCharSize Character size to get resource from specific map
//!
//! @return Texture
const Texture2D& Font::getTexture(const uint8_t cCharSize) const
{
  return mTextures.at(cCharSize);
}

//! @brief Returns the Advanced Width value
//!
//! @return Advanced Width
uint16_t Font::getAdvancedWidth() const
{
  return mAdvancedWidth;
}

//! @brief Gets Capital Height
//!
//! @return Capital Height
int32_t Font::getCapitalHeight() const
{
  return mCapHeight;
}

//! @brief Gets Max Height
//!
//! @return Max Height
int32_t Font::getMaxHeight() const
{
  return mMaxHeight;
}

//! @brief Gets Max Width
//!
//! @return Max Width
int32_t Font::getMaxWidth() const
{
  return mMaxWidth;
}