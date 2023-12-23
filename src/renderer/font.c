#include <cmath>
#include <algorithm>
#include <fstream>
#include <queue>

#include "font.h"
#include "utility/edgeTable.h"

Font::Font()
{
}

static const int32_t ASCII_CHAR_START = 33;
static const int32_t ASCII_CHAR_END = 126;

Font::Font(const std::string& crTtfPath, const uint32_t cNumOfSubDivs, const lg::Color cColor)
{
  mNumSubDiv = cNumOfSubDivs;
  mFontColor = cColor;

  LestTrueType ttf;
  readTtfFile(crTtfPath, ttf);

  char currChar = '\0';
  for(int32_t i = ASCII_CHAR_START; i <= ASCII_CHAR_END; i ++)
  {
    currChar = static_cast<char>(i);
    mFont[currChar].FontHeader = getCharGlyfHeader(currChar, ttf);
  
    if(mFont[currChar].FontHeader.numberofContours > 0)
    {
      generateGlyfData(currChar);
    }
  }
}

void Font::scanLineFill(const char cChar)
{
  EdgeTable::scanLineFill(mFont[cChar].GenPtsEdges, mFont[cChar].Dimensions, mFont[cChar].Bitmap, mFontColor, 0, cChar);
}

void Font::fillColor(const char cChar)
{
  std::queue<int32_t> visited;
  int32_t currPoint = -1;
  int32_t startingPoint = 0; 
  visited.push(startingPoint);
  mFont[cChar].Bitmap[startingPoint] = mFontColor.getRgba();
  int32_t point_below = 0;
  int32_t point_above = 0;
  int32_t point_right = 0;
  int32_t point_left = 0;
  uint32_t num_rows = mFont[cChar].Dimensions.y;
  uint32_t num_cols = mFont[cChar].Dimensions.x;
  const uint32_t color_map_size = mFont[cChar].Bitmap.size();
  Vector2<int32_t> curr_point_coords;
  Vector2<int32_t> point_above_coords;
  Vector2<int32_t> point_below_coords;
  Vector2<int32_t> point_right_coords;
  Vector2<int32_t> point_left_coords;

  while(!visited.empty())
  {
    currPoint = visited.front();
    visited.pop();
    point_below = currPoint + num_cols;
    point_above = currPoint - num_cols;
    point_right = currPoint + 1;
    point_left = currPoint - 1;
    curr_point_coords = Vector2<int32_t>(currPoint % num_cols, currPoint / num_cols);
    point_above_coords = Vector2<int32_t>(point_above % num_cols, point_above / num_cols);
    point_below_coords = Vector2<int32_t>(point_below % num_cols, point_below / num_cols);
    point_right_coords = Vector2<int32_t>(point_right % num_cols, point_right / num_cols);
    point_left_coords = Vector2<int32_t>(point_left % num_cols, point_left / num_cols);


    if(point_below < color_map_size && 
       !(mFontColor == mFont[cChar].Bitmap[point_below]))
    {
      if(PlotUtility<int32_t>::arePointsTouching(point_below_coords, curr_point_coords))
      {
        visited.push(point_below);
        mFont[cChar].Bitmap[point_below] = mFontColor.getRgba();
      }
    }

    if(point_above >= 0 && !(mFontColor == mFont[cChar].Bitmap[point_above]))
    {
      if(PlotUtility<int32_t>::arePointsTouching(point_above_coords, curr_point_coords))
      {
        visited.push(point_above);
        mFont[cChar].Bitmap[point_above] = mFontColor.getRgba();
      }
    }

    if(point_right < color_map_size && !(mFontColor == mFont[cChar].Bitmap[point_right]))
    {
      if (PlotUtility<int32_t>::arePointsTouching(point_right_coords, curr_point_coords))
      {
        visited.push(point_right);
        mFont[cChar].Bitmap[point_right] = mFontColor.getRgba();
      }
    }

    if(point_left >= 0 && !(mFontColor == mFont[cChar].Bitmap[point_left]))
    {
      if(PlotUtility<int32_t>::arePointsTouching(point_left_coords, curr_point_coords))
      {
        visited.push(point_left);
        mFont[cChar].Bitmap[point_left] = mFontColor.getRgba();
      }
    }
  }
}

void Font::fillGeneratedPointColor(const char cChar)
{
  const uint32_t num_cols = mFont[cChar].Dimensions.x;
  int i = 0;
  Vector2<int32_t> p1 = {0, 0};
  Vector2<int32_t> p2 = {0, 0};
  
  for (const auto &edge : mFont[cChar].GenPtsEdges)
  {
    p1.x = edge.p1.x;
    p1.y = edge.p1.y;
    p2.x = edge.p2.x;
    p2.y = edge.p2.y;
    PlotUtility<int32_t>::plotLine(p1, p2, mFont[cChar].Bitmap, num_cols, mFontColor);
  }
}

Font::~Font()
{
}

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

  for(int32_t i = 0; i < mFont[cChar].FontHeader.numberofContours; i++)
  {
    contourStartIdx = j;
    genPtsStartIdx = currIdx;
    contourStart = 1;
    contourStartedOff = 0;
    for(; j <= mFont[cChar].FontHeader.endPtsOfContours[i]; j ++)
    {
      contourLen = mFont[cChar].FontHeader.endPtsOfContours[i] - contourStartIdx + 1;
      nextIdx = (j + 1 - contourStartIdx) % contourLen + contourStartIdx;

      if(ON_CURVE_POINT & mFont[cChar].FontHeader.flags[j])
      {
        currIdx++;
      }
      else
      {
        if (contourStart)
        {
          contourStartedOff = 1;
          if (ON_CURVE_POINT & mFont[cChar].FontHeader.flags[nextIdx])
          {
            currIdx++;
            j++;
            continue;
          }
          currIdx ++;
        }

        if ((ON_CURVE_POINT & mFont[cChar].FontHeader.flags[nextIdx]))
        {
          j++;
        }
        
        currIdx += mNumSubDiv;
      }

      contourStart = 0;
    }

    // Process last contour point
    if(ON_CURVE_POINT & mFont[cChar].FontHeader.flags[j - 1])
    {
      currIdx++;
    }

    //handle off curve
    if(contourStartedOff)
    {
      currIdx += mNumSubDiv;
    }

    mFont[cChar].ContourEnds[i] = currIdx;
  }
}

int32_t Font::generateGlyphPoints(const char cChar)
{
  Vector2<float> p0 = {0.0, 0.0};
  Vector2<float> p1 = {0.0, 0.0};
  Vector2<float> p2 = {0.0, 0.0};

  int32_t j = 0;
  uint32_t currIdx = 0;
  float xPos = 0.0f;
  float yPos = 0.0f;
  int32_t contourStartIdx = 0;
  int32_t genPtsStartIdx = 0;
  int8_t contourStartedOff = 0;
  int8_t contourStart = 0;
  int32_t nextIdx = 0;
  int32_t contourLen = 0;
  Vector2<GLfloat> minCoord = Vector2<GLfloat>(mFont[cChar].FontHeader.xMin,
                                               mFont[cChar].FontHeader.yMin);
  Vector2<GLfloat> maxCoord = Vector2<GLfloat>(mFont[cChar].FontHeader.xMax,
                                               mFont[cChar].FontHeader.yMax);
  GLfloat yShift = -maxCoord.y;

  for(int32_t i = 0; i < mFont[cChar].FontHeader.numberofContours; i++)
  {
    contourStartIdx = j;
    genPtsStartIdx = currIdx;
    contourStart = 1;
    contourStartedOff = 0;
    for(; j <= mFont[cChar].FontHeader.endPtsOfContours[i]; j ++)
    {
      xPos = (mFont[cChar].FontHeader.xCoordinates[j]) - minCoord.x;
      yPos = abs((mFont[cChar].FontHeader.yCoordinates[j]) + yShift);
      contourLen = mFont[cChar].FontHeader.endPtsOfContours[i] - contourStartIdx + 1;
      nextIdx = (j + 1 - contourStartIdx) % contourLen + contourStartIdx;

      if(ON_CURVE_POINT & mFont[cChar].FontHeader.flags[j])
      {
        mFont[cChar].GeneratedPoints[currIdx] = Vector2<float>(xPos, yPos);
        currIdx++;
      }
      else
      {

        if (contourStart)
        {
          contourStartedOff = 1;
          if (ON_CURVE_POINT & mFont[cChar].FontHeader.flags[nextIdx])
          {
            mFont[cChar].GeneratedPoints[currIdx] = Vector2<float>(
              (mFont[cChar].FontHeader.xCoordinates[nextIdx]) - minCoord.x,
              abs((mFont[cChar].FontHeader.yCoordinates[nextIdx]) + yShift));
            currIdx++;
            j++;
            continue;
          }

          xPos = xPos + ((
            (mFont[cChar].FontHeader.xCoordinates[nextIdx]) - minCoord.x - xPos) / 2.0f);
          yPos = yPos + ((
            abs((mFont[cChar].FontHeader.yCoordinates[nextIdx]) + yShift) - yPos) / 2.0f);
          // I changed the order here, might have effects
          mFont[cChar].GeneratedPoints[currIdx].x = xPos;
          mFont[cChar].GeneratedPoints[currIdx].y = yPos;

          currIdx ++;
        }

        p0 = mFont[cChar].GeneratedPoints[currIdx - 1];
        p1 = Vector2<float>(xPos, yPos);
        p2 = Vector2<float>((mFont[cChar].FontHeader.xCoordinates[nextIdx]) - minCoord.x,
                              abs((mFont[cChar].FontHeader.yCoordinates[nextIdx]) + yShift)); 

        if (!(ON_CURVE_POINT & mFont[cChar].FontHeader.flags[nextIdx]))
        {
          // Get midpoint between p1 and p2
          p2 = Vector2<float>(p1.x + ((p2.x - p1.x) / 2.0f),
                                p1.y + ((p2.y - p1.y) / 2.0f));
        }
        else
        {
          j++;
        }
        
        currIdx += PlotUtility<float>::tessellateQuadBezier(mFont[cChar].GeneratedPoints,
                                                              currIdx, mNumSubDiv, p0, p1, p2);
      }

      contourStart = 0;
    }

    // Process last contour point
    if(ON_CURVE_POINT & mFont[cChar].FontHeader.flags[j - 1])
    {
      mFont[cChar].GeneratedPoints[currIdx] = mFont[cChar].GeneratedPoints[genPtsStartIdx];
      currIdx++;
    }

    //handle off curve
    if(contourStartedOff)
    {
      p0 = mFont[cChar].GeneratedPoints[currIdx - 1];
      p1.x = (mFont[cChar].FontHeader.xCoordinates[contourStartIdx]) - minCoord.x;
      p1.y = abs((mFont[cChar].FontHeader.yCoordinates[contourStartIdx]) + yShift);
      p2 = mFont[cChar].GeneratedPoints[genPtsStartIdx];
      currIdx += PlotUtility<float>::tessellateQuadBezier(mFont[cChar].GeneratedPoints,
                                                            currIdx, mNumSubDiv, p0, p1, p2);
    }
  }

  return currIdx;
}

void Font::generateEdges(const char cChar)
{
  int32_t j = 0;
  int32_t edgeIdx = 0;

  for(int32_t i = 0; i < mFont[cChar].ContourEnds.size(); i ++)
  {
    for(; j < mFont[cChar].ContourEnds[i] - 1; j ++)
    {
      mFont[cChar].GenPtsEdges[edgeIdx].p1 = mFont[cChar].GeneratedPoints[j];
      mFont[cChar].GenPtsEdges[edgeIdx].p2 = mFont[cChar].GeneratedPoints[j + 1];
      edgeIdx ++;
    }    
    j ++;
  }
}

std::vector<uint32_t> Font::operator[](const char cChar)
{
    return mFont.at(cChar).Bitmap;
}

Vector2<int32_t> Font::getCharacterDimensions(const char cChar)
{
  return mFont.at(cChar).Dimensions;
}

void Font::writeGenPoints(const char cChar)
{
  std::ofstream fd("GenPoints.txt");

  fd << "-----------------------------------------------------" << std::endl;
  fd << "Points for letter: " << cChar << std::endl;
  fd << "Dimensions: " << mFont[cChar].Dimensions;
  fd << mFont[cChar].GeneratedPoints.size() << std::endl;
  int i = 0;
  for(const auto& pts : mFont[cChar].GeneratedPoints)
  {
    fd << i << ": " << pts;
    i++;
  }
  fd << "-----------------------------------------------------" << std::endl;
}

Font& Font::operator=(const Font &rhs)
{
    if (this == &rhs)
    {
      return *this;
    }

    for (const auto& glyf : rhs.mFont)
    {
      mFont[glyf.first].Ybearing = glyf.second.Ybearing;
      mFont[glyf.first].FontHeader = glyf.second.FontHeader;
      mFont[glyf.first].GeneratedPoints = glyf.second.GeneratedPoints;
      mFont[glyf.first].Bitmap = glyf.second.Bitmap;
      mFont[glyf.first].Dimensions = glyf.second.Dimensions;
      mFont[glyf.first].GenPtsEdges = glyf.second.GenPtsEdges;
      mFont[glyf.first].ContourEnds = glyf.second.ContourEnds;
      mFont[glyf.first].Ydescent = glyf.second.Ydescent;
    }

    mNumSubDiv = rhs.mNumSubDiv;
    mFontColor = rhs.mFontColor;
    mPixelDimensions = rhs.mPixelDimensions;
    mCapHeight = rhs.mCapHeight;
    mMaxWidth = rhs.mMaxWidth;

    return *this;
}

int32_t Font::getYBearing(const char cChar)
{
  return mFont.at(cChar).Ybearing;
}

int32_t Font::getYDescent(const char cChar)
{
  return mFont.at(cChar).Ydescent;
}

void Font::readTtfFile(const std::string& crPath, LestTrueType& rTtf)
{
  if (-1 == rTtf.read(crPath) || !rTtf.hasOS2Table())
  {
    std::cout << "Ttf failed to read." << std::endl;
    exit(-1);
  }

  OS2Table os2 = rTtf.getOS2Table();
  HeadHeader head = rTtf.getHeadHeaderTable();

  mCapHeight = os2.sCapHeight;
  mMaxWidth = head.xMax - head.xMin;

  GlyfHeader tempHeader;
}

void Font::generateGlyfData(const char cChar)
{
  if(mFont[cChar].FontHeader.numberofContours > 0)
  {
    mFont[cChar].ContourEnds.resize(mFont[cChar].FontHeader.numberofContours);

    // Update the number of contours for mFont[cChar] to properly allocate memory for generatedPoints
    updateNumberOfContours(cChar);

    // Generate points from TTF file
    mFont[cChar].GeneratedPoints.resize(mFont[cChar].ContourEnds[mFont[cChar].ContourEnds.size() - 1]);
    generateGlyphPoints(cChar);
  }
}

void Font::updateFontTextures(const uint32_t cCharSize)
{
  char currChar = '\0';
  float scaleY = 0;
  float scaleX = 0;
  for(int32_t i = ASCII_CHAR_START; i <= ASCII_CHAR_END; i ++)
  {
    currChar = static_cast<char>(i);
    if(mFont[currChar].ContourEnds.size() > 0)
    {
        // If we get a crash with different fonts this can be why
        mFont[currChar].GenPtsEdges.clear();
        mFont[currChar].GenPtsEdges.resize(
        (mFont[currChar].ContourEnds[mFont[
          currChar].ContourEnds.size() - 1] - 1) - (mFont[currChar].ContourEnds.size() - 1));
        // Connect edges together
        generateEdges(currChar);

        // Get a ratio between the max height for current letter / max height for a capital letter
        // This will be used to scale down Y value correctly
        scaleY = (static_cast<float>(mFont[currChar].FontHeader.yMax - mFont[currChar].FontHeader.yMin)) /
                 static_cast<float>(mCapHeight);

        // Get ratio of x / y, this will attempt to keep the X x Y dimenion ratios
        scaleX = 
        (static_cast<float>(mFont[currChar].FontHeader.xMax - mFont[currChar].FontHeader.xMin)) /
        static_cast<float>(mMaxWidth);

        mFont[currChar].Dimensions = Vector2<int32_t>(cCharSize * scaleX, cCharSize * scaleY);

        mFont[currChar].Ybearing = cCharSize - mFont[currChar].Dimensions.y;
        
        updateEdges(currChar, cCharSize);
        
        // Correct the right dimensions
        mFont[currChar].Dimensions.x += 1;
        mFont[currChar].Dimensions.y += 1;
        mFont[currChar].Bitmap.resize(
          (mFont[currChar].Dimensions.y) * (mFont[currChar].Dimensions.x), 0);
        scanLineFill(currChar);

        mFont[currChar].Ydescent = abs(cCharSize * (static_cast<float>(mFont[currChar].FontHeader.yMin) /
                                       static_cast<float>(mCapHeight)));
    }
  }
}

void Font::updateEdges(const char cChar, const uint32_t cCharSize)
{
  float scaleY = 0;
  float scaleX = 0;
  float yMax = mFont[cChar].FontHeader.yMax - mFont[cChar].FontHeader.yMin;
  float xMax = mFont[cChar].FontHeader.xMax - mFont[cChar].FontHeader.xMin;

  // Scale down points in edges by the scale
  for (auto& edges : mFont[cChar].GenPtsEdges)
  {
    scaleY = edges.p1.y / yMax;
    scaleX = edges.p1.x / xMax;
    edges.p1.x = static_cast<float>(mFont[cChar].Dimensions.x) * scaleX;
    edges.p1.y = static_cast<float>(mFont[cChar].Dimensions.y) * scaleY;
    scaleY = edges.p2.y / yMax;
    scaleX = edges.p2.x / xMax;
    edges.p2.x = static_cast<float>(mFont[cChar].Dimensions.x) * scaleX;
    edges.p2.y = static_cast<float>(mFont[cChar].Dimensions.y) * scaleY;
  }
}

GlyfHeader Font::getCharGlyfHeader(const char cChar, LestTrueType& rTtf)
{
  GlyfHeader tempHeader;
  rTtf.getSpecifcCharacterOutline(cChar, tempHeader);
  return tempHeader;
}

int32_t Font::getTexture(const char cChar)
{
  return mFont[cChar].GlyfTexture.getTextureId();
}