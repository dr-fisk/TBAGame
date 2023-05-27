#include "mainMenuState.h"
#include <cmath>
#include <algorithm>
#include <queue>

template <typename T>
bool arePointsInRange(const Vector2<T>& crP1, const Vector2<T>& crP2)
{
  Vector2<int32_t> point(crP2.mX - crP1.mX, crP2.mY - crP1.mY);
  point.mX = abs(point.mX);
  point.mY = abs(point.mY);

  return ((1 == point.mY || 0 == point.mY) && (1 == point.mX || 0 == point.mX));
}

template <typename T>
bool arePointsTouching(const Vector2<T>& crP1, const Vector2<T>& crP2)
{
  Vector2<int32_t> point(crP2.mX - crP1.mX, crP2.mY - crP1.mY);
  point.mX = abs(point.mX);
  point.mY = abs(point.mY);

  return ((1 == point.mY && 0 == point.mX) || (1 == point.mX && 0 == point.mY));
}

std::vector<Rect> drawStraightLineToPoint(Rect& rP1, Rect& rP2)
{
  std::vector<Rect> pts;

  if(rP1.getLeft() == rP2.getLeft())
  {
    int addr = 1;

    if(rP1.getTop() > rP2.getTop())
    {
      addr = -1;
    }

    pts.resize(abs(rP2.getTop() - rP1.getTop()) - 1);
    int16_t start_pt = rP1.getTop() + addr;

    for(int i = 0; i < pts.size(); i ++)
    {
      pts[i] = Rect(rP1.getLeft(), start_pt);
      pts[i].setColor(lg::White);
      start_pt += addr;
    }
  }
  else
  {
    int addr = 1;

    if(rP1.getLeft() > rP2.getLeft())
    {
      addr = -1;
    }

    pts.resize(abs(rP2.getLeft() - rP1.getLeft()) - 1);
    int16_t start_pt = rP1.getLeft() + addr;

    for(int i = 0; i < pts.size(); i ++)
    {
      pts[i] = Rect(start_pt, rP1.getTop());
      pts[i].setColor(lg::White);
      start_pt += addr;
    }
  }

  return pts;
}

std::vector<Rect> plotLineLow(Rect p1, Rect p2)
{
  std::vector<Rect> pts;
  int32_t dx = p2.getLeft() - p1.getLeft();
  int32_t dy = p2.getTop() - p1.getTop();

  int32_t yi = 1;

  if(0 > dy)
  {
    yi = -1;
    dy = -dy;
  }

  int32_t D = (2 * dy) - dx;
  int32_t y = p1.getTop();
  pts.resize(p2.getLeft() -  p1.getLeft());

  for(int32_t x = p1.getLeft(); x < p2.getLeft(); x++)
  {
    pts[x - p1.getLeft()] = Rect(x, y);
    pts[x - p1.getLeft()].setColor(lg::White);

    if(0 < D)
    {
      y = y + yi;
      D = D + (2 *  (dy - dx));
    }
    else
    {
      D = D + 2 * dy;
    }
  }

  return pts;
}

std::vector<Rect> plotLineHigh(Rect p1, Rect p2)
{
  std::vector<Rect> pts;
  int32_t dx = p2.getLeft() - p1.getLeft();
  int32_t dy = p2.getTop() - p1.getTop();
  int32_t xi = 1;

  if(0 > dx)
  {
    xi = -1;
    dx = -dx;
  }

  int32_t D = (2 * dx) - dy;
  int32_t x = p1.getLeft();
  pts.resize(p2.getTop() -  p1.getTop());

  for(int32_t y = p1.getTop(); y < p2.getTop(); y++)
  {
    pts[y - p1.getTop()] = Rect(x, y);
    pts[y - p1.getTop()].setColor(lg::White);

    if(0 < D)
    {
      x = x + xi;
      D = D + (2 * (dx - dy));
    }
    else
    {
      D = D + 2 * dx;
    }
  }

  return pts;
}

std::vector<Rect> plotLine(Rect p1, Rect p2)
{
  if(abs(p2.getTop() - p1.getTop()) < abs(p2.getLeft() - p1.getLeft()))
  {
    if(p1.getLeft() > p2.getLeft())
    {
      return plotLineLow(p2, p1);
    }
    else
    {
      return plotLineLow(p1, p2);
    }
  }
  else
  {
    if(p1.getTop() > p2.getTop())
    {
      return plotLineHigh(p2, p1);
    }
    else
    {
      return plotLineHigh(p1, p2);
    }
  }
}

std::vector<Rect> drawDiagonalLineToPoint(Rect rP1, Rect rP2)
{
  std::vector<Rect> pts;
  Vector2<int32_t> p2p1(rP2.getPos() - rP1.getPos());
  GLfloat delta = 0.0f;

  if(0 == p2p1.mX)
  {
    if(rP2.getTop() < rP1.getTop())
    {
      rP1.setPos(rP1.getLeft(), rP2.getTop());
      rP2.setPos(rP2.getLeft(), rP1.getTop());
    }

    pts.resize(rP2.getTop() + 1 - rP1.getTop());
    
    for(int32_t i = rP1.getTop(); i < rP2.getTop() + 1; i++)
    {
      pts[i - rP1.getTop()] = Rect(rP1.getLeft(), i);
      pts[i - rP1.getTop()].setColor(lg::White);
    }

    return pts;
  }
  else
  {
    GLfloat m = (GLfloat)p2p1.mY/(GLfloat)p2p1.mX;
    int32_t adjust = 0 <= m ? 1 : -1;
    int32_t offset = 0;
    GLfloat threshold = 0.5f;

    if(1 >= m)
    {
      GLfloat delta = abs(m);
      int32_t y = rP1.getTop();

      if(rP2.getLeft() < rP1.getLeft())
      {
        rP1.setPos(rP2.getLeft(), rP1.getTop());
        rP2.setPos(rP1.getLeft(), rP2.getTop());
        y = rP2.getTop();
      }

      pts.resize(rP2.getLeft() + 1 - rP1.getLeft());
      for(int32_t i = rP1.getLeft(); i < rP2.getLeft() + 1; i++)
      {
        pts[i - rP1.getLeft()] = Rect(i, y);
        pts[i - rP1.getLeft()].setColor(lg::White);
        offset += delta;
        if(offset >= threshold)
        {
          y += adjust;
          threshold += 1;
        }
      }

      return pts;
    }
    else
    {
      delta = abs((GLfloat)p2p1.mY/(GLfloat)p2p1.mX);
      int32_t x = rP1.getLeft();

      if(rP2.getTop() < rP1.getTop())
      {
        rP1.setPos(rP1.getLeft(), rP2.getTop());
        rP2.setPos(rP2.getLeft(), rP1.getTop());
        x = rP2.getLeft();
      }

      pts.resize(rP2.getTop() + 1 - rP1.getTop());
      for(int32_t i = rP1.getTop(); i < rP2.getTop() + 1; i++)
      {
        pts[i - rP1.getTop()] = Rect(x, i);
        pts[i - rP1.getTop()].setColor(lg::White);
        offset += delta;
        if(offset >= threshold)
        {
          x += adjust;
          threshold += 1;
        }
      }

      return pts;
    }
  }
}
std::vector<Rect> tessellateQuadBezier(Rect& rP0, Rect& rP1, Rect& rP2)
{
  int32_t distance = (rP1.getPos().mX - rP0.getPos().mX) * (rP1.getPos().mX - rP0.getPos().mX) +
                     (rP1.getPos().mY - rP0.getPos().mY) * (rP1.getPos().mY - rP0.getPos().mY);
  distance = sqrt(distance);
  GLfloat step = 1.0f / (GLfloat)distance;
  std::vector<Rect> generatedPts(distance);
  GLfloat t = 0.0f;
  GLfloat t1 = 0.0f;
  GLfloat t2 = 0.0f;

  for(int i = 1; i <= distance; i ++)
  {
    t = (GLfloat) i * step;
    t1 = (1.0f - t);
    t2 = t * t;
    generatedPts[i - 1] = Rect((t1 * t1 * rP0.getLeft() + 2 * t1 * t * rP1.getLeft() + t2 * rP2.getLeft()),
                               (t1 * t1 * rP0.getTop() + 2 * t1 * t * rP1.getTop() + t2 * rP2.getTop()));
    generatedPts[i - 1].setColor(lg::White);
  }

  return generatedPts;
}

std::vector<Rect> tessellateQuadBezier(uint32_t cSubDiv, Rect& rP0, Rect& rP1, Rect& rP2)
{
  GLfloat step = 1.0f / (GLfloat)cSubDiv;
  std::vector<Rect> generatedPts(cSubDiv);
  GLfloat t = 0.0f;
  GLfloat t1 = 0.0f;
  GLfloat t2 = 0.0f;

  for(int i = 1; i <= cSubDiv; i ++)
  {
    t = (GLfloat) i * step;
    t1 = (1.0f - t);
    t2 = t * t;
    generatedPts[i - 1] = Rect((t1 * t1 * rP0.getLeft() + 2 * t1 * t * rP1.getLeft() + t2 * rP2.getLeft()),
                               (t1 * t1 * rP0.getTop() + 2 * t1 * t * rP1.getTop() + t2 * rP2.getTop()));
    generatedPts[i - 1].setColor(lg::White);
  }

  return generatedPts;
}

uint32_t tessellateQuadBezier(std::vector<Rect>& crPoints, const uint32_t cOffset,
                              uint32_t cSubDiv, Rect& rP0, Rect& rP1, Rect& rP2)
{
  GLfloat step = 1.0f / ((GLfloat)cSubDiv + 1);
  GLfloat t = 0.0f;
  GLfloat t1 = 0.0f;
  GLfloat t2 = 0.0f;
  uint32_t itemsAdded = 0;

  for(int i = 1; i < cSubDiv + 1; i ++)
  {
    t = (GLfloat) i * step;
    t1 = (1.0f - t);
    t2 = t * t;
    crPoints[itemsAdded + cOffset] = Rect((t1 * t1 * rP0.getLeft() + 2 * t1 * t * rP1.getLeft() + t2 * rP2.getLeft()),
                               (t1 * t1 * rP0.getTop() + 2 * t1 * t * rP1.getTop() + t2 * rP2.getTop()));
    crPoints[itemsAdded + cOffset].setColor(lg::White);
    itemsAdded ++;
  }

  return itemsAdded;
}

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>> &crStates, const std::shared_ptr<BatchBuffer> &crpBatchBuffer) : State(crStates, crpBatchBuffer)
{
  std::vector<Drawable*> vertexes;
  std::vector<RenderData> rendData;
  std::cout << "SETTINGMAIN\n";
  mFont = Font("../src/fonts/Font.png");
  mText = Text("TEST", mFont);
  std::string temp = "Envy Code R.ttf";
  if(-1 == ttf.read(temp))
  {
    std::cout << "An error occurred reading " << temp << std::endl;
    exit(0);
  }
  // vertexes.push_back(&mText);
  GlyfHeader tempheader;
  ttf.getSpecifcCharacterOutline((uint16_t)'C', tempheader);
  temprect.resize(tempheader.flags.size());
  std::vector<Rect> pts;
  double pi = 3.14159265358979323846;

  std::vector<Rect> generated_pts;
  int j = 0;
  std::vector<uint16_t> new_contour_end(tempheader.numberofContours, 0);
  uint16_t last_end_contour = 0;

  // Loop to see how much memory we will need to allocate
  for(int i = 0; i < tempheader.numberofContours; i++)
  {
    new_contour_end[i] += last_end_contour;
    for(; j <= tempheader.endPtsOfContours[i]; j ++)
    {
      if(!(ON_CURVE_POINT & tempheader.flags[j]))
      {
        // need to check last point
        new_contour_end[i] ++;
      }
      else
      {
        new_contour_end[i] ++;
      }
    }
    
    new_contour_end[i] --;
    last_end_contour = new_contour_end[i] + 1;
    std::cout << new_contour_end[i] << std::endl;
  }

  Rect p1;
  Rect p2;

  generated_pts.resize(new_contour_end[new_contour_end.size() - 1] + 1);
  j = 0;
  uint32_t curr_index = 0;

  for(int i = 0; i < tempheader.numberofContours; i++)
  {
    for(; j < tempheader.endPtsOfContours[i]; j ++)
    {
      if(ON_CURVE_POINT & tempheader.flags[j])
      {
        generated_pts[curr_index] = Rect(tempheader.xCoordinates[j]/8 - tempheader.xMin / 8, abs(tempheader.yCoordinates[j] - tempheader.yMax)/8 - tempheader.yMin / 8);
        generated_pts[curr_index].setColor(lg::White);
        curr_index++;
      }
      else
      {
        p1 = Rect(tempheader.xCoordinates[j]/8 - tempheader.xMin / 8, abs(tempheader.yCoordinates[j] - tempheader.yMax)/8 - tempheader.yMin / 8);
        p1.setColor(lg::White);
        p2 = Rect(tempheader.xCoordinates[j + 1]/8 - tempheader.xMin / 8, abs(tempheader.yCoordinates[j + 1] - tempheader.yMax)/8 - tempheader.yMin / 8);

        if (!(ON_CURVE_POINT & tempheader.flags[j + 1]))
        {

          p2 = Rect(p1.getLeft() + ((p2.getLeft() - p1.getLeft()) / 2),
                    p1.getTop() + ((p2.getTop() - p1.getTop()) / 2));
          p2.setColor(lg::White);
        }

        curr_index += tessellateQuadBezier(generated_pts, curr_index, 1, generated_pts[curr_index - 1], p1, p2);
      }
    }
  }

  // Process last contour point
  if(ON_CURVE_POINT & tempheader.flags[j])
  {
    generated_pts[curr_index] = Rect(tempheader.xCoordinates[j]/8 - tempheader.xMin / 8, abs(tempheader.yCoordinates[j] - tempheader.yMax)/8 - tempheader.yMin / 8);
    generated_pts[curr_index].setColor(lg::White);
    curr_index++;
  }
  //handle off curve
  else if(ON_CURVE_POINT & tempheader.flags[0])
  {
    Rect p1 = Rect(tempheader.xCoordinates[j]/8 - tempheader.xMin / 8, abs(tempheader.yCoordinates[j] - tempheader.yMax)/8 - tempheader.yMin / 8);
    curr_index += tessellateQuadBezier(generated_pts, curr_index, 1, generated_pts[curr_index - 1], p1, generated_pts[0]);
  }

  final = generated_pts;

  j = 0;
  int start_of_contour = 0;
  int comp = 0;
  for(int i = 0; i < new_contour_end.size(); i ++)
  {
    for(; j <= new_contour_end[i]; j ++)
    {
      comp = j + 1;
      
      if (j == new_contour_end[i])
      {
        comp = start_of_contour;
      }
      
      if((generated_pts[j].getLeft() == generated_pts[comp].getLeft() || generated_pts[j].getTop() == generated_pts[comp].getTop()))
      {
        std::cout << generated_pts[j].getPos() << generated_pts[comp].getPos();
        pts = drawStraightLineToPoint(generated_pts[j], generated_pts[comp]);
      }
      else
      {
        pts = plotLine(generated_pts[j], generated_pts[comp]);
      }

      final.insert(final.begin() + j + 1, pts.begin(), pts.end());
      pts.clear();
    }
      
    start_of_contour = new_contour_end[i] + 1;
  }

  std::vector<Rect> bitmap((((tempheader.yMax / 8) - (tempheader.yMin / 8)) + 1) * (((tempheader.xMax / 8) - (tempheader.xMin / 8)) + 1) + 1);

  std::sort(final.begin(), final.end(), Rect::sortByXIntersection);

  int32_t startingPoint = -1;
  for (int i = 0; i < final.size(); i ++)
  {
      if (final[i + 1].getLeft() - final[i].getLeft() > 1 && (final[i].getTop() == final[i + 1].getTop()))
      {
        startingPoint = (final[i].getLeft() + 1) *((tempheader.yMax / 8) - (tempheader.yMin / 8)) + final[i].getTop();
        break;
      }
  }

  for(const auto& points : final)
  {
    // std::cout << bitmap.size() << std::endl;
    bitmap[((points.getLeft() * ((tempheader.yMax / 8) - tempheader.yMin / 8)) + points.getTop())] = points;
  }

  final = bitmap;
  for(int32_t i = 0; i < (tempheader.xMax / 8) - (tempheader.xMin / 8) + 1; i++)
  {
    for(int32_t k = 0; k < (tempheader.yMax / 8) - (tempheader.yMin / 8) + 1; k ++)
    {
      if(!(bitmap[i * ((tempheader.yMax / 8) - (tempheader.yMin / 8)) + k].getRGBA() == lg::White))
      {
        bitmap[i * ((tempheader.yMax / 8) - (tempheader.yMin / 8)) + k]= Rect(Vector2<int32_t>(i, k));
        // std::cout << bitmap[i * ((tempheader.yMax / 8) - (tempheader.yMin / 8)) + k].getPos();
      }
    }
  }

  std::queue<int32_t> visited;
  int currPoint = -1;
  visited.push(startingPoint);
  bitmap[startingPoint].setColor(lg::White);
  while(!visited.empty())
  {
    currPoint = visited.front();
    visited.pop();

    if (currPoint + tempheader.yMax / 8 - tempheader.yMin / 8 < bitmap.size() && !(bitmap[currPoint + tempheader.yMax / 8 - tempheader.yMin / 8].getRGBA() == lg::White))
    {
      if (arePointsTouching(bitmap[currPoint + tempheader.yMax / 8 - tempheader.yMin / 8].getPos(),  bitmap[currPoint].getPos()))
      {
        visited.push(currPoint + tempheader.yMax / 8 - tempheader.yMin / 8);
        bitmap[currPoint + tempheader.yMax / 8 - tempheader.yMin / 8].setColor(lg::White);
      }
    }

    if (currPoint - tempheader.yMax / 8 - tempheader.yMin / 8 >= 0 && !(bitmap[currPoint - tempheader.yMax / 8 - tempheader.yMin / 8].getRGBA() == lg::White))
    {
      if (arePointsTouching(bitmap[currPoint - tempheader.yMax / 8 - tempheader.yMin / 8].getPos(),  bitmap[currPoint].getPos()))
      {
        visited.push(currPoint - tempheader.yMax / 8 - tempheader.yMin / 8);
        bitmap[currPoint - tempheader.yMax / 8 - tempheader.yMin / 8].setColor(lg::White);
      }
    }

    if (currPoint + 1 < bitmap.size() && !(bitmap[currPoint + 1].getRGBA() == lg::White))
    {
      if (arePointsTouching(bitmap[currPoint + 1].getPos(),  bitmap[currPoint].getPos()))
      {
        visited.push(currPoint + 1);
        bitmap[currPoint + 1].setColor(lg::White);
      }
    }

    if (currPoint - 1 >= 0 && !(bitmap[currPoint - 1].getRGBA() == lg::White))
    {
      if (arePointsTouching(bitmap[currPoint - 1].getPos(),  bitmap[currPoint].getPos()))
      {
        visited.push(currPoint - 1);
        bitmap[currPoint - 1].setColor(lg::White);
      }
    }
  }

  final = bitmap;

  // int intersectionCount = 0;
  // for(int i = 0; i < generated_pts.size() - 1; i++)
  // {
  //   if(generated_pts[i].getTop() > tempheader.yMin / 8 && generated_pts[i].getTop() < tempheader.yMax / 8)
  //   {
  //     std::cout << generated_pts[i].getPos() << "VS ";
  //     std::cout << generated_pts[i + 1].getPos();
      
  //     if (generated_pts[i + 1].getLeft() - generated_pts[i].getLeft() > 1 && (generated_pts[i].getTop() == generated_pts[i + 1].getTop()))
  //     {
  //       std::cout <<"Generating line" << std::endl;
  //       pts = drawStraightLineToPoint(generated_pts[i], generated_pts[i + 1]);
  //       final.insert(final.begin() + i + 1, pts.begin(), pts.end());
  //       pts.clear();
  //       intersectionCount = 0;
  //       i++;
  //     }
  //   }
  // }

  // for(const auto& points: final)
  // {
  //   std::cout << points.getPos();
  // }

  for (int i = 0; i < final.size(); i ++ )
  {
    vertexes.push_back(&final[i]);
  }

  BatchBuffer::concatRenderData(vertexes, rendData);
  mpBatchBuffer->updateBoundedBufferData(rendData, GL_STREAM_DRAW);
}

void MainMenu::render(const std::shared_ptr<RenderTarget> &crpTarget)
{
  crpTarget->draw(*mpBatchBuffer);
}

void MainMenu::update()
{
}

MainMenu::~MainMenu() 
{
}

bool MainMenu::shouldStateExit()
{
  return false;
}