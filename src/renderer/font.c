#include <cmath>
#include <algorithm>
#include <fstream>
#include <queue>

#include "font.h"
#include "edgeTable.h"

Font::Font()
{
}

static const int32_t ASCII_CHAR_START = 33;
static const int32_t ASCII_CHAR_END = 126;

Font::Font(const std::string& crTtfPath, const uint32_t cNumOfSubDivs, const lg::Color cColor, const uint32_t cPixelDim)
{
  mNumSubDiv = cNumOfSubDivs;
  mFontColor = cColor;
  mPixelDimensions = 1;//cPixelDim;

  readTtfFile(crTtfPath);
  generateFont(cPixelDim);
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
  uint32_t num_rows = mFont[cChar].Dimensions.mY;
  uint32_t num_cols = mFont[cChar].Dimensions.mX;
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
  const uint32_t num_cols = mFont[cChar].Dimensions.mX;
  int i = 0;
  Vector2<int32_t> p1 = {0, 0};
  Vector2<int32_t> p2 = {0, 0};
  
  for (const auto &edge : mFont[cChar].GenPtsEdges)
  {
    p1.mX = edge.p1.mX;
    p1.mY = edge.p1.mY;
    p2.mX = edge.p2.mX;
    p2.mY = edge.p2.mY;
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
  Vector2<GLfloat> minCoord = Vector2<GLfloat>(mFont[cChar].FontHeader.xMin / mPixelDimensions,
                                               mFont[cChar].FontHeader.yMin / mPixelDimensions);
  Vector2<GLfloat> maxCoord = Vector2<GLfloat>(mFont[cChar].FontHeader.xMax / mPixelDimensions,
                                               mFont[cChar].FontHeader.yMax / mPixelDimensions);
  GLfloat yShift = -maxCoord.mY;

  for(int32_t i = 0; i < mFont[cChar].FontHeader.numberofContours; i++)
  {
    contourStartIdx = j;
    genPtsStartIdx = currIdx;
    contourStart = 1;
    contourStartedOff = 0;
    for(; j <= mFont[cChar].FontHeader.endPtsOfContours[i]; j ++)
    {
      xPos = (mFont[cChar].FontHeader.xCoordinates[j] / mPixelDimensions) - minCoord.mX;
      yPos = abs((mFont[cChar].FontHeader.yCoordinates[j] / mPixelDimensions) + yShift);
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
              (mFont[cChar].FontHeader.xCoordinates[nextIdx] / mPixelDimensions) - minCoord.mX,
              abs((mFont[cChar].FontHeader.yCoordinates[nextIdx] / mPixelDimensions) + yShift));
            currIdx++;
            j++;
            continue;
          }

          xPos = xPos + ((
            (mFont[cChar].FontHeader.xCoordinates[nextIdx] / mPixelDimensions) - minCoord.mX - xPos) / 2.0f);
          yPos = yPos + ((
            abs((mFont[cChar].FontHeader.yCoordinates[nextIdx] / mPixelDimensions) + yShift) - yPos) / 2.0f);
          // I changed the order here, might have effects
          mFont[cChar].GeneratedPoints[currIdx].mX = xPos;
          mFont[cChar].GeneratedPoints[currIdx].mY = yPos;

          currIdx ++;
        }

        p0 = mFont[cChar].GeneratedPoints[currIdx - 1];
        p1 = Vector2<float>(xPos, yPos);
        p2 = Vector2<float>((mFont[cChar].FontHeader.xCoordinates[nextIdx] / mPixelDimensions) - minCoord.mX,
                              abs((mFont[cChar].FontHeader.yCoordinates[nextIdx] / mPixelDimensions) + yShift)); 

        if (!(ON_CURVE_POINT & mFont[cChar].FontHeader.flags[nextIdx]))
        {
          // Get midpoint between p1 and p2
          p2 = Vector2<float>(p1.mX + ((p2.mX - p1.mX) / 2.0f),
                                p1.mY + ((p2.mY - p1.mY) / 2.0f));
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
      p1.mX = (mFont[cChar].FontHeader.xCoordinates[contourStartIdx] / mPixelDimensions) - minCoord.mX;
      p1.mY = abs((mFont[cChar].FontHeader.yCoordinates[contourStartIdx] / mPixelDimensions) + yShift);
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
  for(const auto& pts : mFont[cChar].GenPtsEdges)
  {
    fd << i << ": " << pts.p1 << pts.p2;
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
    }

    mNumSubDiv = rhs.mNumSubDiv;
    mFontColor = rhs.mFontColor;
    mPixelDimensions = rhs.mPixelDimensions;
    mCapHeight = rhs.mCapHeight;

    return *this;
}

int32_t Font::getYBearing(const char cChar)
{
  return mFont.at(cChar).Ybearing;
}

void Font::readTtfFile(const std::string& crPath)
{
  LestTrueType ttf;
  if (-1 == ttf.read(crPath) || !ttf.hasOS2Table())
  {
    std::cout << "Ttf failed to read." << std::endl;
    exit(-1);
  }

  OS2Table os2 = ttf.getOS2Table();

  mCapHeight = os2.sCapHeight;

  GlyfHeader tempHeader;

  for(int32_t i = ASCII_CHAR_START; i <= ASCII_CHAR_END; i ++)
  {
    ttf.getSpecifcCharacterOutline(static_cast<char>(i), tempHeader);
    mFont[static_cast<char>(i)].FontHeader = tempHeader;
  }
}

void Font::generateFont(const uint32_t cPixelDim)
{
  float scaleY = 0;
  float scaleX = 0;
  char currChar = 'A';

  for(int32_t i = ASCII_CHAR_START; i <= ASCII_CHAR_END; i ++)
  {
    currChar = static_cast<char>(i);
    if(mFont[currChar].FontHeader.numberofContours > 0)
    {
        mFont[currChar].ContourEnds.resize(mFont[currChar].FontHeader.numberofContours);
    
        // Update the number of contours for mFont[currChar] to properly allocate memory for generatedPoints
        updateNumberOfContours(currChar);

        // Generate points from TTF file
        mFont[currChar].GeneratedPoints.resize(mFont[currChar].ContourEnds[mFont[currChar].ContourEnds.size() - 1]);
        // If we get a crash with different fonts this can be why
        mFont[currChar].GenPtsEdges.resize(
        (mFont[currChar].ContourEnds[mFont[
          currChar].ContourEnds.size() - 1] - 1) - (mFont[currChar].ContourEnds.size() - 1));
        generateGlyphPoints(currChar);

        // Connect edges together
        generateEdges(currChar);

        // Get a ratio between the max height for current letter / max height for a capital letter
        // This will be used to scale down Y value correctly
        scaleY = (static_cast<float>(mFont[currChar].FontHeader.yMax - mFont[currChar].FontHeader.yMin)) /
                 static_cast<float>(mCapHeight);

        // Get ratio of x / y, this will attempt to keep the X x Y dimenion ratios
        scaleX = 
        (static_cast<float>(mFont[currChar].FontHeader.xMax - mFont[currChar].FontHeader.xMin)) /
        (static_cast<float>(mFont[currChar].FontHeader.yMax - mFont[currChar].FontHeader.yMin));
        
        scaleX = std::min(scaleX, 1.0f);
        scaleY = std::min(scaleY, 1.0f);

        mFont[currChar].Dimensions = Vector2<int32_t>(cPixelDim * scaleX, cPixelDim * scaleY);
        mFont[currChar].Ybearing = cPixelDim - mFont[currChar].Dimensions.mY;
        
        updateEdges(currChar, cPixelDim);
        
        // Correct the right dimensions
        mFont[currChar].Dimensions.mX += 1;
        mFont[currChar].Dimensions.mY += 1;
        mFont[currChar].Bitmap.resize(
          (mFont[currChar].Dimensions.mY) * (mFont[currChar].Dimensions.mX), 0);
        scanLineFill(currChar);
    }
  }
}

void Font::updateEdges(const char cChar, const uint32_t cPixelDim)
{
  float scaleY = 0;
  float scaleX = 0;

  // Scale down points in edges by the scale
  for (auto& edges : mFont[cChar].GenPtsEdges)
  {
    scaleY = edges.p1.mY / static_cast<float>(mCapHeight);
    scaleX = edges.p1.mX / static_cast<float>(mFont[cChar].FontHeader.yMax - mFont[cChar].FontHeader.yMin);
    scaleX = std::min(scaleX, 1.0f);
    scaleY = std::min(scaleY, 1.0f);

    edges.p1.mX = static_cast<float>(cPixelDim) * scaleX;
    edges.p1.mY = static_cast<float>(cPixelDim) * scaleY;

    scaleY = edges.p2.mY / static_cast<float>(mCapHeight);
    scaleX = edges.p2.mX / static_cast<float>(mFont[cChar].FontHeader.yMax - mFont[cChar].FontHeader.yMin);
    scaleX = std::min(scaleX, 1.0f);
    scaleY = std::min(scaleY, 1.0f);

    edges.p2.mX = static_cast<float>(cPixelDim) * scaleX;
    edges.p2.mY = static_cast<float>(cPixelDim) * scaleY;
  }
}