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

int32_t calcMetric(const int32_t cDimensions, const float cPointSize, const uint32_t cUnitsPerEm)
{
  float lsb = calculatePixelSize(cDimensions, cPointSize, cUnitsPerEm);

  return static_cast<int32_t>(std::round(lsb));
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
    mGlyfData.try_emplace(currChar);
    mGlyfData.at(currChar).FontHeader = getCharGlyfHeader(currChar, ttf);
    mGlyfData.at(currChar).HorMetrics = ttf.getSpecificCharacterHorMetrics(currChar);

    if(mGlyfData.at(currChar).FontHeader.numberofContours > 0)
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
  EdgeTable::scanLineFill(mFont.at(cCharSize).at(cChar).GenPtsEdges, mFont.at(cCharSize).at(cChar).Dimensions,
                          mFont.at(cCharSize).at(cChar).Bitmap, lg::White, 0, cChar);
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
  mFont.at(cCharSize).at(cChar).Bitmap[startingPoint] = lg::White.getRgba();
  int32_t point_below = 0;
  int32_t point_above = 0;
  int32_t point_right = 0;
  int32_t point_left = 0;
  uint32_t num_rows = mFont.at(cCharSize).at(cChar).Dimensions.y;
  uint32_t num_cols = mFont.at(cCharSize).at(cChar).Dimensions.x;
  const uint32_t color_map_size = mFont.at(cCharSize).at(cChar).Bitmap.size();
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
       !(lg::White == mFont.at(cCharSize).at(cChar).Bitmap[point_below]))
    {
      if(PlotUtility<glm::vec2>::arePointsTouching(point_below_coords, curr_point_coords))
      {
        visited.push(point_below);
        mFont.at(cCharSize).at(cChar).Bitmap[point_below] = lg::White.getRgba();
      }
    }

    if(point_above >= 0 && !(lg::White == mFont.at(cCharSize).at(cChar).Bitmap[point_above]))
    {
      if(PlotUtility<glm::vec2>::arePointsTouching(point_above_coords, curr_point_coords))
      {
        visited.push(point_above);
        mFont.at(cCharSize).at(cChar).Bitmap[point_above] = lg::White.getRgba();
      }
    }

    if(point_right < color_map_size && !(lg::White == mFont.at(cCharSize).at(cChar).Bitmap[point_right]))
    {
      if (PlotUtility<glm::vec2>::arePointsTouching(point_right_coords, curr_point_coords))
      {
        visited.push(point_right);
        mFont.at(cCharSize).at(cChar).Bitmap[point_right] = lg::White.getRgba();
      }
    }

    if(point_left >= 0 && !(lg::White == mFont.at(cCharSize).at(cChar).Bitmap[point_left]))
    {
      if(PlotUtility<glm::vec2>::arePointsTouching(point_left_coords, curr_point_coords))
      {
        visited.push(point_left);
        mFont.at(cCharSize).at(cChar).Bitmap[point_left] = lg::White.getRgba();
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
  const uint32_t num_cols = mFont.at(cCharSize).at(cChar).Dimensions.x;
  int i = 0;
  glm::ivec2 p1 = {0, 0};
  glm::ivec2 p2 = {0, 0};
  
  for (const auto &edge : mFont.at(cCharSize).at(cChar).GenPtsEdges)
  {
    p1.x = edge.p1.x;
    p1.y = edge.p1.y;
    p2.x = edge.p2.x;
    p2.y = edge.p2.y;
    PlotUtility<glm::ivec2>::plotLine(p1, p2, mFont.at(cCharSize).at(cChar).Bitmap, num_cols, lg::White);
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

  for(int32_t i = 0; i < mGlyfData.at(cChar).FontHeader.numberofContours; i++)
  {
    contourStartIdx = j;
    genPtsStartIdx = currIdx;
    contourStart = 1;
    contourStartedOff = 0;
    for(; j <= mGlyfData.at(cChar).FontHeader.SimpleGlyfData->endPtsOfContours[i]; j ++)
    {
      contourLen = mGlyfData.at(cChar).FontHeader.SimpleGlyfData->endPtsOfContours[i] - contourStartIdx + 1;
      nextIdx = (j + 1 - contourStartIdx) % contourLen + contourStartIdx;

      if(ON_CURVE_POINT & mGlyfData.at(cChar).FontHeader.SimpleGlyfData->flags[j])
      {
        currIdx++;
      }
      else
      {
        if (contourStart)
        {
          contourStartedOff = 1;
          if (ON_CURVE_POINT & mGlyfData.at(cChar).FontHeader.SimpleGlyfData->flags[nextIdx])
          {
            currIdx++;
            j++;
            continue;
          }
          currIdx ++;
        }

        if ((ON_CURVE_POINT & mGlyfData.at(cChar).FontHeader.SimpleGlyfData->flags[nextIdx]))
        {
          j++;
        }
        
        currIdx += mNumSubDiv;
      }

      contourStart = 0;
    }

    // Process last contour point
    if(ON_CURVE_POINT & mGlyfData.at(cChar).FontHeader.SimpleGlyfData->flags[j - 1])
    {
      currIdx++;
    }

    //handle off curve
    if(contourStartedOff)
    {
      currIdx += mNumSubDiv;
    }

    mGlyfData.at(cChar).Contours[i] = currIdx;
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
  GlyfRawData* glyfData = &mGlyfData.at(cChar);
  glm::vec2 minCoord = glm::vec2(glyfData->FontHeader.xMin,
                                               glyfData->FontHeader.yMin);
  glm::vec2 maxCoord = glm::vec2(glyfData->FontHeader.xMax,
                                               glyfData->FontHeader.yMax);
  GLfloat yShift = -maxCoord.y;

  for(int32_t i = 0; i < glyfData->FontHeader.numberofContours; i++)
  {
    contourStartIdx = j;
    genPtsStartIdx = currIdx;
    contourStart = 1;
    contourStartedOff = 0;
    for(; j <= glyfData->FontHeader.SimpleGlyfData->endPtsOfContours[i]; j ++)
    {
      xPos = (glyfData->FontHeader.SimpleGlyfData->xCoordinates[j]) - minCoord.x;
      yPos = abs((glyfData->FontHeader.SimpleGlyfData->yCoordinates[j]) + yShift);
      contourLen = glyfData->FontHeader.SimpleGlyfData->endPtsOfContours[i] - contourStartIdx + 1;
      nextIdx = (j + 1 - contourStartIdx) % contourLen + contourStartIdx;

      if(ON_CURVE_POINT & glyfData->FontHeader.SimpleGlyfData->flags[j])
      {
        glyfData->GeneratedPoints[currIdx] = glm::vec2(xPos, yPos);
        currIdx++;
      }
      else
      {

        if (contourStart)
        {
          contourStartedOff = 1;
          if (ON_CURVE_POINT & glyfData->FontHeader.SimpleGlyfData->flags[nextIdx])
          {
            glyfData->GeneratedPoints[currIdx] = glm::vec2(
              (glyfData->FontHeader.SimpleGlyfData->xCoordinates[nextIdx]) - minCoord.x,
              abs((glyfData->FontHeader.SimpleGlyfData->yCoordinates[nextIdx]) + yShift));
            currIdx++;
            j++;
            continue;
          }

          xPos = xPos + ((
            (glyfData->FontHeader.SimpleGlyfData->xCoordinates[nextIdx]) - minCoord.x - xPos) / 2.0f);
          yPos = yPos + ((
            abs((glyfData->FontHeader.SimpleGlyfData->yCoordinates[nextIdx]) + yShift) - yPos) / 2.0f);
          // I changed the order here, might have effects
          glyfData->GeneratedPoints[currIdx].x = xPos;
          glyfData->GeneratedPoints[currIdx].y = yPos;

          currIdx ++;
        }

        p0 = glyfData->GeneratedPoints[currIdx - 1];
        p1 = glm::vec2(xPos, yPos);
        p2 = glm::vec2((glyfData->FontHeader.SimpleGlyfData->xCoordinates[nextIdx]) - minCoord.x,
                              abs((glyfData->FontHeader.SimpleGlyfData->yCoordinates[nextIdx]) + yShift)); 

        if (!(ON_CURVE_POINT & glyfData->FontHeader.SimpleGlyfData->flags[nextIdx]))
        {
          // Get midpoint between p1 and p2
          p2 = glm::vec2(p1.x + ((p2.x - p1.x) / 2.0f),
                                p1.y + ((p2.y - p1.y) / 2.0f));
        }
        else
        {
          j++;
        }
        
        currIdx += PlotUtility<glm::vec2>::tessellateQuadBezier(glyfData->GeneratedPoints,
                                                              currIdx, mNumSubDiv, p0, p1, p2);
      }

      contourStart = 0;
    }

    // Process last contour point
    if(ON_CURVE_POINT & glyfData->FontHeader.SimpleGlyfData->flags[j - 1])
    {
      glyfData->GeneratedPoints[currIdx] = glyfData->GeneratedPoints[genPtsStartIdx];
      currIdx++;
    }

    //handle off curve
    if(contourStartedOff)
    {
      p0 = glyfData->GeneratedPoints[currIdx - 1];
      p1.x = (glyfData->FontHeader.SimpleGlyfData->xCoordinates[contourStartIdx]) - minCoord.x;
      p1.y = abs((glyfData->FontHeader.SimpleGlyfData->yCoordinates[contourStartIdx]) + yShift);
      p2 = glyfData->GeneratedPoints[genPtsStartIdx];
      currIdx += PlotUtility<glm::vec2>::tessellateQuadBezier(glyfData->GeneratedPoints,
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

  for(int32_t i = 0; i < mGlyfData.at(cChar).Contours.size(); i ++)
  {
    for(; j < mGlyfData.at(cChar).Contours[i] - 1; j ++)
    {
      mFont.at(cCharSize).at(cChar).GenPtsEdges[edgeIdx].p1 = mGlyfData.at(cChar).GeneratedPoints[j];
      mFont.at(cCharSize).at(cChar).GenPtsEdges[edgeIdx].p2 = mGlyfData.at(cChar).GeneratedPoints[j + 1];
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
  // fd << "Dimensions: " << mFont.at(cCharSize).at(cChar).D)mensions;
  // fd << mGlyfData.at(cChar).GeneratedPoints.size() << std::endl;
  // int i = 0;
  // for(const auto& pts : mGlyfData.at(cChar).GeneratedPoints)
  // {
  //   fd << i << ": " << pts;
  //   i++;
  // }
  // fd << "-----------------------------------------------------" << std::endl;
}

//! @brief Gets YHint from character in font size map
//!
//! @param[in] cChar     Character to grab YHint from
//! @param[in] cCharSize Character size to grab YHint from
//!
//! @return YHint
int32_t Font::getYHint(const char cChar, const uint8_t cCharSize) const
{
  return mFont.at(cCharSize).at(cChar).YHint;
}

//! @brief Gets LeftSideBearing from character in font size map
//!
//! @param[in] cChar     Character to grab LeftSideBearing from
//! @param[in] cCharSize Character size to grab LeftSideBearing from
//!
//! @return LeftSideBearing
int16_t Font::getLeftSideBearing(const char cChar, const uint8_t cCharSize) const
{
  return mFont.at(cCharSize).at(cChar).LeftSideBearing;
}

//! @brief Gets Advance Width from character in font size map
//!
//! @param[in] cChar     Character to grab Advance Width from
//! @param[in] cCharSize Character size to grab Advance Width from
//!
//! @return Advance Width
int16_t Font::getAdvancedWidth(const char cChar, const uint8_t cCharSize) const
{
  return mFont.at(cCharSize).at(cChar).AdvanceWidth;
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
  mLowerCaseHeight = os2.sxHeight;
  mMaxWidth = head.xMax - head.xMin;
  mMaxHeight = head.yMax - head.yMin;
  mUnitsPerEm = head.unitsPerEm;
  HheaHeader hhea = rTtf.getHheaHeader();
  mAdvancedWidth = hhea.advancedWidthMax;

  std::cout << "Cap Height: " << mCapHeight << "\n LC Height: " << mLowerCaseHeight << std::endl;
}

//! @brief Generates Glyf Data for given character
//!
//! @param[in] cChar Character to generate Glyf Data for
//!
//! @return None
void Font::generateGlyfData(const char cChar)
{
  if(mGlyfData.at(cChar).FontHeader.numberofContours >= 0)
  {
    mGlyfData.at(cChar).Contours.resize(mGlyfData.at(cChar).FontHeader.numberofContours);

    // Update the number of contours for mFont.at(cCharSize).at(cChar) t) properly allocate memory for generatedPoints
    updateNumberOfContours(cChar);

    // Generate points from TTF file
    mGlyfData.at(cChar).GeneratedPoints.resize(mGlyfData.at(cChar).Contours[mGlyfData.at(cChar).Contours.size() - 1]);
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

  mFont.try_emplace(cCharSize);

  char currChar = '\0';
  float scaleY = 0;
  float scaleX = 0;
  glm::uvec2 offset(0, 0);
  const float EM_PCT = static_cast<float>(cCharSize) / static_cast<float>(BASE_SIZE_PX);
  const float PT_SIZE = EM_PCT * BASE_SIZE_PT;

  FontTable* fontTable = &mFont.at(cCharSize);
  FontPage* fontPage = nullptr;
  GlyfRawData* glyfData = nullptr;

  std::cout << PT_SIZE << std::endl;

  for(int32_t i = ASCII_CHAR_START; i <= ASCII_CHAR_END; i ++)
  {
    //******************************************************************************************************************
    // Data Setup
    //******************************************************************************************************************
    currChar = static_cast<char>(i);
    fontTable->try_emplace(currChar, FontPage());
    fontPage = &fontTable->at(currChar);
    glyfData = &mGlyfData.at(currChar);

    //******************************************************************************************************************
    // Processing Logic
    //******************************************************************************************************************
    fontPage->Dimensions = glm::uvec2(
    calculatePixelSize(glyfData->FontHeader.xMax - glyfData->FontHeader.xMin, PT_SIZE, mUnitsPerEm),
    calculatePixelSize(glyfData->FontHeader.yMax - glyfData->FontHeader.yMin, PT_SIZE, mUnitsPerEm));
    // Correct the right dimensions
    fontPage->Dimensions.x += 1;
    fontPage->Dimensions.y += 1;
    fontPage->AdvanceWidth = std::round(calculatePixelSize(glyfData->HorMetrics.advanceWidth, PT_SIZE, mUnitsPerEm));
    fontPage->LeftSideBearing = static_cast<int16_t>(calcMetric(glyfData->HorMetrics.leftSideBearing, PT_SIZE, mUnitsPerEm));

    if(glyfData->FontHeader.numberofContours >= 0)
    {
        // If we get a crash with different fonts this can be why
        fontPage->GenPtsEdges.clear();
        fontPage->GenPtsEdges.resize((glyfData->Contours[glyfData->Contours.size() - 1] - 1)
                                     - (glyfData->Contours.size() - 1));
        // Connect edges together
        generateEdges(currChar, cCharSize);

        updateEdges(currChar, cCharSize);
        fontPage->Bitmap.resize(
          (fontPage->Dimensions.y) * (fontPage->Dimensions.x), lg::Color(255, 255, 255, 0).getRgba());
        scanLineFill(currChar, cCharSize);

        fontPage->Offset = offset;

        offset.x += fontPage->Dimensions.x;
        offset.y += fontPage->Dimensions.y;

        fontPage->YHint = calcMetric(mCapHeight - glyfData->FontHeader.yMax, PT_SIZE, mUnitsPerEm);
    }
  }

  mTextures[cCharSize].create(offset.y, offset.x);

  for(int32_t i = ASCII_CHAR_START + 1; i <= ASCII_CHAR_END; i ++)
  {
    currChar = static_cast<char>(i);
    fontPage = &fontTable->at(currChar);
    mTextures[cCharSize].update(fontPage->Bitmap.data(), fontPage->Dimensions, fontPage->Offset);
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
  GlyfRawData* glyfData = &mGlyfData.at(cChar);
  const float newMaxX = calculatePixelSize(glyfData->FontHeader.xMax - glyfData->FontHeader.xMin, PT_SIZE, mUnitsPerEm) / static_cast<float>(glyfData->FontHeader.xMax - glyfData->FontHeader.xMin);
  const float newMaxY = calculatePixelSize(glyfData->FontHeader.yMax - glyfData->FontHeader.yMin, PT_SIZE, mUnitsPerEm) / static_cast<float>(glyfData->FontHeader.yMax - glyfData->FontHeader.yMin);

  // Scale down points in edges by the scale
  for (auto& edges : mFont.at(cCharSize).at(cChar).GenPtsEdges)
  {
    edges.p1.x = edges.p1.x * newMaxX;
    edges.p1.y = edges.p1.y * newMaxY;
    edges.p2.x = edges.p2.x * newMaxX;
    edges.p2.y = edges.p2.y * newMaxY;
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