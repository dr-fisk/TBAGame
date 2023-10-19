#include <cmath>
#include <algorithm>
#include <fstream>
#include <queue>

#include "font.h"

static const std::vector<char> sCHARS = { {'A'}, {'B'}, {'C'}, {'D'}, {'E'}, {'F'}, {'G'}, {'H'}, {'I'}, {'J'},
                                          {'K'}, {'L'}, {'M'}, {'N'}, {'O'}, {'P'}, {'Q'}, {'R'}, {'S'}, {'T'},
                                          {'U'}, {'V'}, {'W'}, {'X'}, {'Y'}, {'Z'}, {'a'}, {'b'}, {'c'}, {'d'},
                                          {'e'}, {'f'}, {'g'}, {'h'}, {'i'}, {'j'}, {'k'}, {'m'}, {'n'}, {'n'},
                                          {'o'}, {'p'}, {'q'}, {'r'}, {'s'}, {'t'}, {'u'}, {'v'}, {'w'}, {'x'},
                                          {'y'}, {'z'}, {'0'}, {'1'}, {'2'}, {'3'}, {'4'}, {'5'}, {'6'}, {'7'},
                                          {'8'}, {'9'} };

Font::Font()
{
}

Font::Font(std::string ttfPath, const uint32_t cNumOfSubDivs, const lg::Color cColor, const uint32_t cPixelDim)
{
  LestTrueType ttf;

  mNumSubDiv = cNumOfSubDivs;
  mFontColor = cColor;
  mPixelDimensions = cPixelDim;

  if (-1 == ttf.read(ttfPath))
  {
    std::cout << "Ttf failed to read." << std::endl;
    exit(-1);
  }

  std::vector<uint16_t> newContourEnds;
  int32_t startingPoint = 0;
  GlyfHeader temp;

  for(auto& character : sCHARS)
  {
    ttf.getSpecifcCharacterOutline(character, temp);
    mFont[character].FontHeader = temp;

    if(mFont[character].FontHeader.numberofContours > 0)
    {
        mFont[character].ContourEnds.resize(mFont[character].FontHeader.numberofContours);
    
        // Update the number of contours for mFont[character] to properly allocate memory for generatedPoints
        updateNumberOfContours(character);

        // Generate points from TTF file
        mFont[character].GeneratedPoints.resize(mFont[character].ContourEnds[mFont[character].ContourEnds.size() - 1]);
        mFont[character].GenPtsEdges.resize(mFont[character].ContourEnds[mFont[character].ContourEnds.size() - 1] - 1);
        mFont[character].NumGenPoints = generateGlyphPoints(character);

        // Connect edges together
        generateEdges(character);

        // Sort points by X Intersection
        // std::sort(mFont[character].GeneratedPoints.begin(), mFont[character].GeneratedPoints.end(),
        //           PlotUtility<int32_t>::sortByXIntersection);

        mFont[character].Dimensions = Vector2<int32_t>
        ((mFont[character].FontHeader.xMax - mFont[character].FontHeader.xMin) / mPixelDimensions,
         (mFont[character].FontHeader.yMax - mFont[character].FontHeader.yMin) / mPixelDimensions);
        
        // Correct the right dimensions
        mFont[character].Dimensions.mX += 1;
        mFont[character].Dimensions.mY += 1;
        mFont[character].StartingPoint = getStartingPoint(character, mFont[character].GeneratedPoints);
        mFont[character].ColorMap.resize((mFont[character].Dimensions.mY) * (mFont[character].Dimensions.mX), 0);
        fillGeneratedPointColor(character);
        // fillColor(character);
    }
  }
}

void Font::scanLineFill(const char cChar)
{
  //We have an inverted grid, where y = 0 is yMax and Dimensions.mY is yMin
  for(int32_t i = 0; i < mFont[cChar].GeneratedPoints.size() - 1; i ++)
  {
    if(PlotUtility<int32_t>::doPointsShareAxis(mFont[cChar].GeneratedPoints[i], mFont[cChar].GeneratedPoints[i + 1])
      && !PlotUtility<int32_t>::arePointsTouching(mFont[cChar].GeneratedPoints[i], mFont[cChar].GeneratedPoints[i + 1]))
    {
    }
  }
}

void Font::fillColor(const char cChar)
{
  std::queue<int32_t> visited;
  int32_t currPoint = -1;
  int32_t startingPoint = mFont[cChar].StartingPoint; 
  visited.push(startingPoint);
  mFont[cChar].ColorMap[startingPoint] = mFontColor.getRgba();
  int32_t point_below = 0;
  int32_t point_above = 0;
  int32_t point_right = 0;
  int32_t point_left = 0;
  uint32_t num_rows = mFont[cChar].Dimensions.mY;
  uint32_t num_cols = mFont[cChar].Dimensions.mX;
  const uint32_t color_map_size = mFont[cChar].ColorMap.size();
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
       !(mFontColor == mFont[cChar].ColorMap[point_below]))
    {
      if(PlotUtility<int32_t>::arePointsTouching(point_below_coords, curr_point_coords))
      {
        visited.push(point_below);
        mFont[cChar].ColorMap[point_below] = mFontColor.getRgba();
      }
    }

    if(point_above >= 0 && !(mFontColor == mFont[cChar].ColorMap[point_above]))
    {
      if(PlotUtility<int32_t>::arePointsTouching(point_above_coords, curr_point_coords))
      {
        visited.push(point_above);
        mFont[cChar].ColorMap[point_above] = mFontColor.getRgba();
      }
    }

    if(point_right < color_map_size && !(mFontColor == mFont[cChar].ColorMap[point_right]))
    {
      if (PlotUtility<int32_t>::arePointsTouching(point_right_coords, curr_point_coords))
      {
        visited.push(point_right);
        mFont[cChar].ColorMap[point_right] = mFontColor.getRgba();
      }
    }

    if(point_left >= 0 && !(mFontColor == mFont[cChar].ColorMap[point_left]))
    {
      if(PlotUtility<int32_t>::arePointsTouching(point_left_coords, curr_point_coords))
      {
        visited.push(point_left);
        mFont[cChar].ColorMap[point_left] = mFontColor.getRgba();
      }
    }
  }
}

void Font::fillGeneratedPointColor(const char cChar)
{
  const uint32_t num_cols = mFont[cChar].Dimensions.mX;
  
  for (const auto &edge : mFont[cChar].GenPtsEdges)
  {
    PlotUtility<int32_t>::plotLine(edge.p1, edge.p2, mFont[cChar].ColorMap, num_cols, mFontColor);        
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
  Vector2<int32_t> p0;
  Vector2<int32_t> p1;
  Vector2<int32_t> p2;

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
        mFont[cChar].GeneratedPoints[currIdx] = Vector2<int32_t>(xPos, yPos);
        currIdx++;
      }
      else
      {

        if (contourStart)
        {
          contourStartedOff = 1;
          if (ON_CURVE_POINT & mFont[cChar].FontHeader.flags[nextIdx])
          {
            mFont[cChar].GeneratedPoints[currIdx] = Vector2<int32_t>(
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
        p1 = Vector2<int32_t>(xPos, yPos);
        p2 = Vector2<int32_t>((mFont[cChar].FontHeader.xCoordinates[nextIdx] / mPixelDimensions) - minCoord.mX,
                              abs((mFont[cChar].FontHeader.yCoordinates[nextIdx] / mPixelDimensions) + yShift)); 

        if (!(ON_CURVE_POINT & mFont[cChar].FontHeader.flags[nextIdx]))
        {
          // Get midpoint between p1 and p2
          p2 = Vector2<int32_t>(p1.mX + ((p2.mX - p1.mX) / 2.0f),
                                p1.mY + ((p2.mY - p1.mY) / 2.0f));
        }
        else
        {
          j++;
        }
        
        currIdx += PlotUtility<int32_t>::tessellateQuadBezier(mFont[cChar].GeneratedPoints,
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
      currIdx += PlotUtility<int32_t>::tessellateQuadBezier(mFont[cChar].GeneratedPoints,
                                                            currIdx, mNumSubDiv, p0, p1, p2);
    }
  }

  return currIdx;
}

void Font::generateEdges(const char cChar)
{
  int32_t j = 0;
  int32_t start_of_contour = 0;
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
    start_of_contour = j;
  }
}

int32_t Font::getStartingPoint(const char cChar, const std::vector<Vector2<int32_t>>& crPoints)
{
  int32_t startingPoint = -1;
  for(int i = 0; i < crPoints.size(); i ++)
  {
      if(crPoints[i + 1].mX - crPoints[i].mX > 1 && (crPoints[i].mY == crPoints[i + 1].mY))
      {
        startingPoint = (crPoints[i].mY) * (mFont[cChar].Dimensions.mX) + (crPoints[i].mX + 1);
        break;
      }
  }

  return startingPoint;
}

std::vector<uint32_t> Font::operator[](const char cChar)
{
    return mFont.at(cChar).ColorMap;
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
  fd << mFont[cChar].NumGenPoints << std::endl;
  int i = 0;
  for(const auto& pts : mFont[cChar].GeneratedPoints)
  {
    fd << i << ": " << pts;
    i++;
  }
  fd << "-----------------------------------------------------" << std::endl;
}