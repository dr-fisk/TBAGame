#include <cmath>
#include <algorithm>
#include <fstream>
#include <queue>

#include "font.h"
#include "edgeTable.h"

Font::Font()
{
}

Font::Font(std::string ttfPath, const uint32_t cNumOfSubDivs, const lg::Color cColor, const uint32_t cPixelDim)
{
  LestTrueType ttf;
  const int32_t ASCII_CHAR_START = 33;
  const int32_t ASCII_CHAR_END = 126;

  mNumSubDiv = cNumOfSubDivs;
  mFontColor = cColor;
  mPixelDimensions = 1;//cPixelDim;

  if (-1 == ttf.read(ttfPath))
  {
    std::cout << "Ttf failed to read." << std::endl;
    exit(-1);
  }

  GlyfHeader temp;

  for(int32_t i = ASCII_CHAR_START; i <= ASCII_CHAR_END; i ++)
  {
    std::cout << (char)i << std::endl;
    ttf.getSpecifcCharacterOutline(static_cast<char>(i), temp);
    // std::cout << "Glyf extracted." << std::endl;
    mFont[static_cast<char>(i)].FontHeader = temp;

    if(mFont[static_cast<char>(i)].FontHeader.numberofContours > 0)
    {
        mFont[static_cast<char>(i)].ContourEnds.resize(mFont[static_cast<char>(i)].FontHeader.numberofContours);
    
        // Update the number of contours for mFont[static_cast<char>(i)] to properly allocate memory for generatedPoints
        updateNumberOfContours(static_cast<char>(i));

        // Generate points from TTF file
        mFont[static_cast<char>(i)].GeneratedPoints.resize(mFont[static_cast<char>(i)].ContourEnds[mFont[static_cast<char>(i)].ContourEnds.size() - 1]);
        // If we get a crash with different fonts this can be why
        mFont[static_cast<char>(i)].GenPtsEdges.resize(
        (mFont[static_cast<char>(i)].ContourEnds[mFont[static_cast<char>(i)].ContourEnds.size() - 1] - 1) - (mFont[static_cast<char>(i)].ContourEnds.size() - 1));
        generateGlyphPoints(static_cast<char>(i));

        // Connect edges together
        generateEdges(static_cast<char>(i));
        // float scaleY = 64.0 / (mFont[static_cast<char>(i)].FontHeader.yMax - mFont[static_cast<char>(i)].FontHeader.yMin);
        // float scaleX = 64.0 / (mFont[static_cast<char>(i)].FontHeader.xMax - mFont[static_cast<char>(i)].FontHeader.xMin);
        // float scaleY = 1;
        mFont[static_cast<char>(i)].Dimensions = Vector2<int32_t>
        ((mFont[static_cast<char>(i)].FontHeader.xMax - mFont[static_cast<char>(i)].FontHeader.xMin) / 8.0,
         (mFont[static_cast<char>(i)].FontHeader.yMax - mFont[static_cast<char>(i)].FontHeader.yMin) / 8.0);
        
        for (auto &edges : mFont[static_cast<char>(i)].GenPtsEdges)
        {
          edges.p1.mX = edges.p1.mX / 8.0;
          edges.p1.mY = edges.p1.mY / 8.0;
          edges.p2.mX = edges.p2.mX / 8.0;
          edges.p2.mY = edges.p2.mY / 8.0;
        }
        // Correct the right dimensions
        mFont[static_cast<char>(i)].Dimensions.mX += 1;
        mFont[static_cast<char>(i)].Dimensions.mY += 1;
        mFont[static_cast<char>(i)].Bitmap.resize(
          (mFont[static_cast<char>(i)].Dimensions.mY) * (mFont[static_cast<char>(i)].Dimensions.mX), 0);
        scanLineFill(static_cast<char>(i));
        // fillGeneratedPointColor((char) i);
    }
    // if ((char)i == 'A')
    // break;
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