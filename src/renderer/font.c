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
                                          {'y'}, {'z'} };

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
  std::vector<Vector2<int32_t>> generatedPoints;
  int32_t startingPoint = 0;
  GlyfHeader temp;

  for(auto& character : sCHARS)
  {
    ttf.getSpecifcCharacterOutline(character, temp);
    mFont[character].FontHeader = temp;

    if(mFont[character].FontHeader.numberofContours > 0)
    {
        newContourEnds.resize(mFont[character].FontHeader.numberofContours);
    
        // Update the number of contours for mFont[character] to properly allocate memory for generatedPoints
        updateNumberOfContours(character, newContourEnds);

        // Generate points from TTF file
        generatedPoints.resize(newContourEnds[newContourEnds.size() - 1] + 1);
        generateGlyphPoints(character, generatedPoints);

        // Connect edges together
        connectEdges(generatedPoints, newContourEnds);

        // Sort points by X Intersection
        std::sort(generatedPoints.begin(), generatedPoints.end(), Vector2<int32_t>::sortByXIntersection);

        // Remember to add 1 later TODO:
        mFont[character].Dimensions = Vector2<int32_t>
        ((mFont[character].FontHeader.xMax - mFont[character].FontHeader.xMin) / mPixelDimensions,
         (mFont[character].FontHeader.yMax - mFont[character].FontHeader.yMin)/ mPixelDimensions);
        
        // Correct the right dimensions
        mFont[character].Dimensions.mX += 1;
        mFont[character].Dimensions.mY += 1;

        mFont[character].GeneratedPoints = generatedPoints;

        mFont[character].StartingPoint = getStartingPoint(character, generatedPoints);
        mFont[character].ColorMap.resize((mFont[character].Dimensions.mY) * (mFont[character].Dimensions.mX), 0);
        fillGeneratedPointColor(character);
        fillColor(character);

        generatedPoints.clear();
        newContourEnds.clear();
    }
  }
}

void Font::fillColor(const char cCharacter)
{
  std::queue<int32_t> visited;
  int32_t currPoint = -1;
  int32_t startingPoint = mFont[cCharacter].StartingPoint; 
  visited.push(startingPoint);
  mFont[cCharacter].ColorMap[startingPoint] = mFontColor.getRgba();
  int32_t point_below = 0;
  int32_t point_above = 0;
  int32_t point_right = 0;
  int32_t point_left = 0;
  uint32_t num_rows = mFont[cCharacter].Dimensions.mY;
  uint32_t num_cols = mFont[cCharacter].Dimensions.mX;
  const uint32_t color_map_size = mFont[cCharacter].ColorMap.size();
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
       !(mFontColor == mFont[cCharacter].ColorMap[point_below]))
    {
      if(Vector2<int32_t>::arePointsTouching(point_below_coords, curr_point_coords))
      {
        visited.push(point_below);
        mFont[cCharacter].ColorMap[point_below] = mFontColor.getRgba();
      }
    }

    if(point_above >= 0 && !(mFontColor == mFont[cCharacter].ColorMap[point_above]))
    {
      if(Vector2<int32_t>::arePointsTouching(point_above_coords, curr_point_coords))
      {
        visited.push(point_above);
        mFont[cCharacter].ColorMap[point_above] = mFontColor.getRgba();
      }
    }

    if(point_right < color_map_size && !(mFontColor == mFont[cCharacter].ColorMap[point_right]))
    {
      if (Vector2<int32_t>::arePointsTouching(point_right_coords, curr_point_coords))
      {
        visited.push(point_right);
        mFont[cCharacter].ColorMap[point_right] = mFontColor.getRgba();
      }
    }

    if(point_left >= 0 && !(mFontColor == mFont[cCharacter].ColorMap[point_left]))
    {
      if(Vector2<int32_t>::arePointsTouching(point_left_coords, curr_point_coords))
      {
        visited.push(point_left);
        mFont[cCharacter].ColorMap[point_left] = mFontColor.getRgba();
      }
    }
  }
}

void Font::fillGeneratedPointColor(const char cCharacter)
{
  const uint32_t num_cols = mFont[cCharacter].Dimensions.mX;
  
  for(const auto &points : mFont[cCharacter].GeneratedPoints)
  {
    mFont[cCharacter].ColorMap[(points.mY * num_cols) + points.mX] = mFontColor.getRgba();
  }
}

Font::~Font()
{
}

void Font::updateNumberOfContours(const char cCharacter, std::vector<uint16_t> &rContours)
{
  int32_t j = 0;
  int32_t last_end_contour = 0;
  // Loop to see how much memory we will need to allocate
  for(int32_t i = 0; i < mFont[cCharacter].FontHeader.numberofContours; i++)
  {
    rContours[i] += last_end_contour;
    for(; j <= mFont[cCharacter].FontHeader.endPtsOfContours[i]; j ++)
    {
      if(!(ON_CURVE_POINT & mFont[cCharacter].FontHeader.flags[j]))
      {
        rContours[i] += mNumSubDiv;
      }
      else
      {
        rContours[i] ++;
      }
    }
    
    rContours[i] --;
    last_end_contour = rContours[i] + 1;
  }
}

void Font::generateGlyphPoints(const char cCharacter, std::vector<Vector2<int32_t>>& rPoints)
{
  Vector2<int32_t> p1;
  Vector2<int32_t> p2;

  int j = 0;
  uint32_t curr_index = 0;
  int32_t xPos = 0.0f;
  int32_t yPos = 0.0f;
  Vector2<GLfloat> minCoord = Vector2<GLfloat>(mFont[cCharacter].FontHeader.xMin / mPixelDimensions,
                                               mFont[cCharacter].FontHeader.yMin / mPixelDimensions);

  for(int i = 0; i < mFont[cCharacter].FontHeader.numberofContours; i++)
  {
    for(; j < mFont[cCharacter].FontHeader.endPtsOfContours[i]; j ++)
    {
      xPos = mFont[cCharacter].FontHeader.xCoordinates[j] / mPixelDimensions - minCoord.mX;
      yPos = abs((mFont[cCharacter].FontHeader.yCoordinates[j] - mFont[cCharacter].FontHeader.yMax )/ (GLfloat) mPixelDimensions - minCoord.mY);

      if(ON_CURVE_POINT & mFont[cCharacter].FontHeader.flags[j])
      {
        rPoints[curr_index] = Vector2<int32_t>(xPos, yPos);
        curr_index++;
      }
      else
      {
        p1 = Vector2<int32_t>(xPos, yPos);
        p2 = Vector2<int32_t>(mFont[cCharacter].FontHeader.xCoordinates[j + 1] / mPixelDimensions - minCoord.mX,
                              abs((mFont[cCharacter].FontHeader.yCoordinates[j + 1] - mFont[cCharacter].FontHeader.yMax) / (GLfloat) mPixelDimensions -
                              minCoord.mY)); 

        if (!(ON_CURVE_POINT & mFont[cCharacter].FontHeader.flags[j + 1]))
        {
          // Get midpoint between p1 and p2
          p2 = Vector2<int32_t>(p1.mX + ((p2.mX - p1.mX) / 2.0f),
                    p1.mY + ((p2.mY - p1.mY) / 2.0f));
        }

        curr_index += Vector2<int32_t>::tessellateQuadBezier(rPoints, curr_index, 1, rPoints[curr_index - 1], p1, p2);
      }
    }
  }

  xPos = mFont[cCharacter].FontHeader.xCoordinates[j] / mPixelDimensions - minCoord.mX;
  yPos = abs((mFont[cCharacter].FontHeader.yCoordinates[j] - mFont[cCharacter].FontHeader.yMax) / (GLfloat) mPixelDimensions - minCoord.mY);

  // Process last contour point
  if(ON_CURVE_POINT & mFont[cCharacter].FontHeader.flags[j])
  {
    rPoints[curr_index] = Vector2<int32_t>(xPos, yPos);
    curr_index++;
  }
  //handle off curve
  else if(ON_CURVE_POINT & mFont[cCharacter].FontHeader.flags[0])
  {
    p1 = Vector2<int32_t>(xPos, yPos);
    curr_index += Vector2<int32_t>::tessellateQuadBezier(rPoints, curr_index, 1, rPoints[curr_index - 1], p1, rPoints[0]);
  }

}

void Font::connectEdges(std::vector<Vector2<int32_t>>& rPoints, const std::vector<uint16_t>& crContourEnds)
{
  int32_t j = 0;
  int32_t start_of_contour = 0;
  int32_t comp = 0;
  std::vector<Vector2<int32_t>> newPoints = rPoints;
  std::vector<Vector2<int32_t>> pts;

  for(int32_t i = 0; i < crContourEnds.size(); i ++)
  {
    for(; j <= crContourEnds[i]; j ++)
    {
      comp = j + 1;
      
      if (j == crContourEnds[i])
      {
        comp = start_of_contour;
      }
      
      if(rPoints[j] != rPoints[comp])
      {
        if(((rPoints[j].mX == rPoints[comp].mX || rPoints[j].mY == rPoints[comp].mY)))
        {
            pts = Vector2<int32_t>::drawStraightLineToPoint(rPoints[j], rPoints[comp]);
        }
        else
        {
            pts = Vector2<int32_t>::plotLine(rPoints[j], rPoints[comp]);
        }

        newPoints.insert(newPoints.begin() + j + 1, pts.begin(), pts.end());
        pts.clear();
      }
    }
      
    start_of_contour = crContourEnds[i] + 1;
  }

  rPoints = newPoints;
}

int32_t Font::getStartingPoint(const char cCharacter, const std::vector<Vector2<int32_t>>& crPoints)
{
  int32_t startingPoint = -1;
  for(int i = 0; i < crPoints.size(); i ++)
  {
      if(crPoints[i + 1].mX - crPoints[i].mX > 1 && (crPoints[i].mY == crPoints[i + 1].mY))
      {
        startingPoint = (crPoints[i].mY) * (mFont[cCharacter].Dimensions.mX) + (crPoints[i].mX + 1);
        break;
      }
  }

  return startingPoint;
}

std::vector<uint32_t> Font::operator[](const char cCharacter)
{
    return mFont.at(cCharacter).ColorMap;
}

Vector2<int32_t> Font::getCharacterDimensions(const char cCharacter)
{
  return mFont.at(cCharacter).Dimensions;
}