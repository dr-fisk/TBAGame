#include <cmath>
#include <algorithm>

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
    exit(0);
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

        mFont[character].MaxCoords = Vector2<int32_t>((mFont[character].FontHeader.xMax - mFont[character].FontHeader.xMin) / mPixelDimensions,
                                                      (mFont[character].FontHeader.yMax - mFont[character].FontHeader.yMin)/ mPixelDimensions);
        
        // Grab the last point to know the Num Rows and Num Cols to create a bitmap this doesn't grab the max fix
        mFont[character].FontBitmap = Bitmap(mFont[character].MaxCoords.mY + 1,
                                             mFont[character].MaxCoords.mX + 1);

        startingPoint = getStartingPoint(character, generatedPoints);

        // TODO: Change color to be dynamic
        mFont[character].FontBitmap.constructBitmap(generatedPoints, lg::White);
        mFont[character].FontBitmap.fillColor(startingPoint, lg::White);

        generatedPoints.clear();
        newContourEnds.clear();
    }
  }
}

Font::~Font()
{
}

void Font::updateNumberOfContours(const char cLetter, std::vector<uint16_t> &rContours)
{
  int32_t j = 0;
  int32_t last_end_contour = 0;
  // Loop to see how much memory we will need to allocate
  for(int32_t i = 0; i < mFont[cLetter].FontHeader.numberofContours; i++)
  {
    rContours[i] += last_end_contour;
    for(; j <= mFont[cLetter].FontHeader.endPtsOfContours[i]; j ++)
    {
      if(!(ON_CURVE_POINT & mFont[cLetter].FontHeader.flags[j]))
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

void Font::generateGlyphPoints(const char cLetter, std::vector<Vector2<int32_t>>& rPoints)
{
  Vector2<int32_t> p1;
  Vector2<int32_t> p2;

  int j = 0;
  uint32_t curr_index = 0;
  int32_t xPos = 0.0f;
  int32_t yPos = 0.0f;
  Vector2<GLfloat> minCoord = Vector2<GLfloat>(mFont[cLetter].FontHeader.xMin / mPixelDimensions,
                                               mFont[cLetter].FontHeader.yMin / mPixelDimensions);

  for(int i = 0; i < mFont[cLetter].FontHeader.numberofContours; i++)
  {
    for(; j < mFont[cLetter].FontHeader.endPtsOfContours[i]; j ++)
    {
      xPos = mFont[cLetter].FontHeader.xCoordinates[j] / mPixelDimensions - minCoord.mX;
      yPos = abs((mFont[cLetter].FontHeader.yCoordinates[j] - mFont[cLetter].FontHeader.yMax ) / (GLfloat) mPixelDimensions - minCoord.mY);

      if(ON_CURVE_POINT & mFont[cLetter].FontHeader.flags[j])
      {
        rPoints[curr_index] = Vector2<int32_t>(xPos, yPos);
        curr_index++;
      }
      else
      {
        p1 = Vector2<int32_t>(xPos, yPos);
        p2 = Vector2<int32_t>(mFont[cLetter].FontHeader.xCoordinates[j + 1] / mPixelDimensions - minCoord.mX,
                              abs((mFont[cLetter].FontHeader.yCoordinates[j + 1] - mFont[cLetter].FontHeader.yMax) / (GLfloat) mPixelDimensions -
                              minCoord.mY)); 

        if (!(ON_CURVE_POINT & mFont[cLetter].FontHeader.flags[j + 1]))
        {
          // Get midpoint between p1 and p2
          p2 = Vector2<int32_t>(p1.mX + ((p2.mX - p1.mX) / 2.0f),
                    p1.mY + ((p2.mY - p1.mY) / 2.0f));
        }

        curr_index += Vector2<int32_t>::tessellateQuadBezier(rPoints, curr_index, 1, rPoints[curr_index - 1], p1, p2);
      }
    }
  }

  xPos = mFont[cLetter].FontHeader.xCoordinates[j] / mPixelDimensions - minCoord.mX;
  yPos = abs((mFont[cLetter].FontHeader.yCoordinates[j] - mFont[cLetter].FontHeader.yMax) / (GLfloat) mPixelDimensions - minCoord.mY);

  // Process last contour point
  if(ON_CURVE_POINT & mFont[cLetter].FontHeader.flags[j])
  {
    rPoints[curr_index] = Vector2<int32_t>(xPos, yPos);
    curr_index++;
  }
  //handle off curve
  else if(ON_CURVE_POINT & mFont[cLetter].FontHeader.flags[0])
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

int32_t Font::getStartingPoint(const char cLetter, const std::vector<Vector2<int32_t>>& crPoints)
{
  int32_t startingPoint = -1;
  for(int i = 0; i < crPoints.size(); i ++)
  {
      if(crPoints[i + 1].mX - crPoints[i].mX > 1 && (crPoints[i].mY == crPoints[i + 1].mY))
      {
        startingPoint = (crPoints[i].mX + 1) * (mFont[cLetter].MaxCoords.mY + 1) + crPoints[i].mY;
        break;
      }
  }

  return startingPoint;
}

std::vector<std::shared_ptr<Rect>> Font::operator[](const char cLetter)
{
  if(mFont.find(cLetter) != mFont.end())
  {
    return mFont[cLetter].FontBitmap.getBitmap();
  }

  std::cout << "Invalid letter provied." << std::endl;
  return std::vector<std::shared_ptr<Rect>>();
}