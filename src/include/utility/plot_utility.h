#ifndef PLOT_UTILITY_H
#define PLOT_UTILITY_H

#include <utility>
#include <iostream>
#include <cmath>

#include "Vector.h"
#include "color.h"

template <typename T>
struct Edges
{
  Vector2<T> p1;
  Vector2<T> p2;
};

template <typename T> class PlotUtility
{
  public:
    static bool doPointsShareAxis(const Vector2<T> &crP1, const Vector2<T> &crP2);
    static bool arePointsInRange(const Vector2<T> &crP1, const Vector2<T> &crP2);
    static bool arePointsTouching(const Vector2<T> &crP1, const Vector2<T> &crP2);
    static bool sortByXIntersection(const Vector2<T>& crP1, const Vector2<T>& crP2);
    static bool sortByYIntersection(const Vector2<T>& crP1, const Vector2<T>& crP2);
    static uint32_t tessellateQuadBezier(std::vector<Vector2<T>>& crPoints, const uint32_t cOffset,
                                         uint32_t cSubDiv, Vector2<T>& rP0, Vector2<T>& rP1, Vector2<T>& rP2);
    static std::vector<Vector2<T>> drawStraightLineToPoint(const Vector2<T>& crP1, const Vector2<T>& crP2);
    static void drawStraightLineToPoint(const Vector2<T>& crP1, const Vector2<T>& crP2, std::vector<uint32_t> &rBitmap,
                                        const uint32_t cNumCols, const lg::Color &crColor);
    static void drawPixelInBitmap(const Vector2<T>& crP1, std::vector<uint32_t> &rBitmap, const uint32_t cNumCols,
                                  const lg::Color &crColor);
    static void plotLineLow(const Vector2<T> cP1, const Vector2<T> cP2,
                            std::vector<uint32_t> &rBitmap, const uint32_t cNumCols,
                            const lg::Color &crColor);
    static void plotLineHigh(const Vector2<T> cP1, const Vector2<T> cP2,
                             std::vector<uint32_t> &rBitmap, const uint32_t cNumCols,
                             const lg::Color &crColor);
    static void plotLine(const Vector2<T> cP1, const Vector2<T> cP2, std::vector<uint32_t> &rBitmap,
                         const uint32_t cNumCols, const lg::Color &crColor);
// Remove
    static std::vector<Vector2<T>> plotLineLow(const Vector2<T> cP1, const Vector2<T> cP2);
    static std::vector<Vector2<T>> plotLineHigh(const Vector2<T> cP1, const Vector2<T> cP2);
    static std::vector<Vector2<T>> plotLine(const Vector2<T> cP1, const Vector2<T> cP2);
    static std::vector<Vector2<T>> plotAALine(Vector2<T> p1, Vector2<T> p2);
    static float getDecimalFromFloat(float val);
};

template <typename T>
bool PlotUtility<T>::doPointsShareAxis(const Vector2<T> &crP1, const Vector2<T> &crP2)
{
  return ((crP1.y == crP2.y) || (crP1.x == crP2.x));
}


template <typename T>
bool PlotUtility<T>::arePointsInRange(const Vector2<T> &crP1, const Vector2<T> &crP2)
{
  Vector2<int32_t> point(crP2.x - crP1.x, crP2.y - crP1.y);
  point.x = abs(point.x);
  point.y = abs(point.y);

  return ((1 == point.y || 0 == point.y) && (1 == point.x || 0 == point.x));
}

template <typename T>
bool PlotUtility<T>::arePointsTouching(const Vector2<T> &crP1, const Vector2<T> &crP2)
{
  Vector2<int32_t> point(crP2.x - crP1.x, crP2.y - crP1.y);
  point.x = abs(point.x);
  point.y = abs(point.y);

  return ((1 == point.x || 0 == point.x) && (1 == point.y || 0 == point.y));
}

template <typename T>
bool PlotUtility<T>::sortByXIntersection(const Vector2<T>& crP1, const Vector2<T>& crP2)
{
   if (crP1.y == crP2.y)
   {
      return crP1.x < crP2.x;
   }

   return crP1.y < crP2.y;
}

template <typename T>
bool PlotUtility<T>::sortByYIntersection(const Vector2<T>& crP1, const Vector2<T>& crP2)
{
   if (crP1.x == crP2.x)
   {
      return crP1.y < crP2.y;
   }

   return crP1.x < crP2.x;
}

template <typename T>
uint32_t PlotUtility<T>::tessellateQuadBezier(std::vector<Vector2<T>>& crPoints, const uint32_t cOffset,
                              uint32_t cSubDiv, Vector2<T>& rP0, Vector2<T>& rP1, Vector2<T>& rP2)
{
  #ifdef GLEW_STATIC
    GLfloat step = 1.0f / static_cast<GLfloat>(cSubDiv);
    GLfloat t = 0.0f;
    GLfloat t1 = 0.0f;
    GLfloat t2 = 0.0f;
  #else
    float step = 1.0f / static_cast<float>(cSubDiv);
    float t = 0.0f;
    float t1 = 0.0f;
    float t2 = 0.0f;
  #endif
  uint32_t itemsAdded = 0;

  for(int i = 1; i <= cSubDiv; i ++)
  {
    #ifdef GLEW_STATIC
    t = static_cast<GLfloat>(i) * step;
    #else
    t = static_cast<float>(i) * step;
    #endif
    t1 = (1.0f - t);
    t2 = t * t;
    crPoints[itemsAdded + cOffset] = Vector2<T>((t1 * t1 * rP0.x + 2 * t1 * t * rP1.x + t2 * rP2.x),
                                                (t1 * t1 * rP0.y + 2 * t1 * t * rP1.y + t2 * rP2.y));
    itemsAdded ++;
  }

  return itemsAdded;
}

template <typename T>
void PlotUtility<T>::drawPixelInBitmap(const Vector2<T>& crP1, std::vector<uint32_t> &rBitmap, const uint32_t cNumCols,
                                       const lg::Color &crColor)
{
  rBitmap[(crP1.y * cNumCols) + crP1.x] = crColor.getRgba();
}

template <typename T>
void PlotUtility<T>::drawStraightLineToPoint(const Vector2<T>& crP1, const Vector2<T>& crP2, 
                                             std::vector<uint32_t> &rBitmap, const uint32_t cNumCols,
                                             const lg::Color &crColor)
{
  if(crP1.x == crP2.x)
  {
    int8_t addr = 1;

    if(crP1.y > crP2.y)
    {
      addr = -1;
    }

    int32_t numPts = crP2.y - crP1.y - 1;
    int16_t start_pt = crP1.y + addr;

    for(int i = 0; i < numPts; i ++)
    {
      rBitmap[(start_pt * cNumCols) + crP1.x] = crColor.getRgba();
      start_pt += addr;
    }
  }
  else
  {
    int8_t addr = 1;

    if(crP1.x > crP2.x)
    {
      addr = -1;
    }

    int32_t numPts = crP2.x - crP1.x - 1;
    int16_t start_pt = crP1.x + addr;

    for(int i = 0; i < numPts; i ++)
    {
      rBitmap[(crP1.y * cNumCols) + start_pt] = crColor.getRgba();
      start_pt += addr;
    }
  }
}

template <typename T>
void PlotUtility<T>::plotLineLow(const Vector2<T> cP1, const Vector2<T> cP2, std::vector<uint32_t> &rBitmap,
                                 const uint32_t cNumCols, const lg::Color &crColor)
{
  int32_t dx = cP2.x - cP1.x;
  int32_t dy = cP2.y - cP1.y;

  int32_t yi = 1;

  if(0 > dy)
  {
    yi = -1;
    dy = -dy;
  }

  int32_t D = (2 * dy) - dx;
  int32_t y = cP1.y;

  for(int32_t x = cP1.x; x <= cP2.x; x++)
  {
    rBitmap[(y * cNumCols) + x] = crColor.getRgba();

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
}

template <typename T>
void PlotUtility<T>::plotLineHigh(const Vector2<T> cP1, const Vector2<T> cP2, std::vector<uint32_t> &rBitmap,
                                  const uint32_t cNumCols, const lg::Color &crColor)
{
  int32_t dx = cP2.x - cP1.x;
  int32_t dy = cP2.y - cP1.y;
  int32_t xi = 1;

  if(0 > dx)
  {
    xi = -1;
    dx = -dx;
  }

  int32_t D = (2 * dx) - dy;
  int32_t x = cP1.x;

  for(int32_t y = cP1.y; y <= cP2.y; y++)
  {
    rBitmap[(y * cNumCols) + x] = crColor.getRgba();

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
}

template <typename T>
void PlotUtility<T>::plotLine(const Vector2<T> cP1, const Vector2<T> cP2, std::vector<uint32_t> &rBitmap,
                              const uint32_t cNumCols, const lg::Color &crColor)
{
  if(abs(cP2.y - cP1.y) < abs(cP2.x - cP1.x))
  {
    if(cP1.x > cP2.x)
    {
      return plotLineLow(cP2, cP1, rBitmap, cNumCols, crColor);
    }
    else
    {
      return plotLineLow(cP1, cP2, rBitmap, cNumCols, crColor);
    }
  }
  else
  {
    if(cP1.y > cP2.y)
    {
      return plotLineHigh(cP2, cP1, rBitmap, cNumCols, crColor);
    }
    else
    {
      return plotLineHigh(cP1, cP2, rBitmap, cNumCols, crColor);
    }
  }
}

template <typename T>
std::vector<Vector2<T>> PlotUtility<T>::drawStraightLineToPoint(const Vector2<T>& crP1, const Vector2<T>& crP2)
{
  std::vector<Vector2<T>> pts;

  if(crP1.x == crP2.x)
  {
    int8_t addr = 1;

    if(crP1.y > crP2.y)
    {
      addr = -1;
    }

    pts.resize(abs(crP2.y - crP1.y) - 1);
    int16_t start_pt = crP1.y + addr;

    for(int i = 0; i < pts.size(); i ++)
    {
      pts[i] = Vector2<T>(crP1.x, start_pt);
      start_pt += addr;
    }
  }
  else
  {
    int8_t addr = 1;

    if(crP1.x > crP2.x)
    {
      addr = -1;
    }

    pts.resize(abs(crP2.x - crP1.x) - 1);
    int16_t start_pt = crP1.x + addr;

    for(int i = 0; i < pts.size(); i ++)
    {
      pts[i] = Vector2<T>(start_pt, crP1.y);
      start_pt += addr;
    }
  }

  return pts;
}

template <typename T>
std::vector<Vector2<T>> PlotUtility<T>::plotLineLow(const Vector2<T> cP1, const Vector2<T> cP2)
{
  std::vector<Vector2<T>> pts;
  int32_t dx = cP2.x - cP1.x;
  int32_t dy = cP2.y - cP1.y;

  int32_t yi = 1;

  if(0 > dy)
  {
    yi = -1;
    dy = -dy;
  }

  int32_t D = (2 * dy) - dx;
  int32_t y = cP1.y;
  pts.resize(cP2.x - cP1.x);

  for(int32_t x = cP1.x; x < cP2.x; x++)
  {
    pts[x - cP1.x] = Vector2<T>(x, y);

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

template <typename T>
std::vector<Vector2<T>> PlotUtility<T>::plotLineHigh(const Vector2<T> cP1, const Vector2<T> cP2)
{
  std::vector<Vector2<T>> pts;
  int32_t dx = cP2.x - cP1.x;
  int32_t dy = cP2.y - cP1.y;
  int32_t xi = 1;

  if(0 > dx)
  {
    xi = -1;
    dx = -dx;
  }

  int32_t D = (2 * dx) - dy;
  int32_t x = cP1.x;
  pts.resize(cP2.y - cP1.y);

  for(int32_t y = cP1.y; y < cP2.y; y++)
  {
    pts[y - cP1.y] = Vector2<T>(x, y);

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

template <typename T>
std::vector<Vector2<T>> PlotUtility<T>::plotLine(const Vector2<T> cP1, const Vector2<T> cP2)
{
  if(abs(cP2.y - cP1.y) < abs(cP2.x - cP1.x))
  {
    if(cP1.x > cP2.x)
    {
      return plotLineLow(cP2, cP1);
    }
    else
    {
      return plotLineLow(cP1, cP2);
    }
  }
  else
  {
    if(cP1.y > cP2.y)
    {
      return plotLineHigh(cP2, cP1);
    }
    else
    {
      return plotLineHigh(cP1, cP2);
    }
  }
}

template <typename T>
std::vector<Vector2<T>> PlotUtility<T>::plotAALine(Vector2<T> p1, Vector2<T> p2)
{ 
  int32_t steep = abs(p2.y - p1.y) > abs(p2.x - p1.x);
  std::vector<Vector2<T>> pts;

  // swap the co-ordinates if slope > 1 or we
  // draw backwards
  if (steep)
  {
    std::swap(p1.x , p1.y);
    std::swap(p2.x , p2.y);
  }
  if (p1.x > p2.x)
  {
    std::swap(p1.x ,p2.x);
    std::swap(p1.y ,p2.y);
  }

  //compute the slope
  float dx = p2.x - p1.x;
  float dy = p2.y - p1.y;
  float gradient = dy / dx;

  if (dx == 0.0)
  {
    gradient = 1;
  }

  int32_t xpxl1 = p1.x;
  int32_t xpxl2 = p2.x;
  float intersectY = p1.y;

  // std::cout << "px 1: " << xpxl2 << " px 2: " << xpxl1 << std::endl;
  pts.resize((xpxl2 - xpxl1 + 1) * 2);

  if (steep)
  {
    int32_t x;
    int32_t i = 0;

    for (x = xpxl1; x <= xpxl2; x++)
    {
      // Do vector shenanigans here
        // pixel coverage is determined by fractional
        // part of y co-ordinate
        pts[i] = Vector2<T>(static_cast<int32_t>(intersectY), x);
                // std::cout << pts[i] << std::endl;

        pts[i + 1] = Vector2<T>(static_cast<int32_t>(intersectY) - 1, x);
        // std::cout << pts[i] << std::endl;

      if (pts[i + 1].x < 0)
      {
        pts[i + 1].x = 0;
      }

        // drawPixel(static_cast<int32_t>(intersectY), x, 1 - intersectY);
        // drawPixel(static_cast<int32_t>(intersectY) - 1, x, getDecimalFromFloat(intersectY));
        intersectY += gradient;

        i += 2;
    }
  }
  else
  {
    int32_t x;
    int32_t i = 0;

    for (x = xpxl1; x <= xpxl2; x++)
    {
      // Do vector shenanigans here
      // pixel coverage is determined by fractional
      // part of y co-ordinate
      pts[i] = Vector2<T>(x, static_cast<int32_t>(intersectY));
              // std::cout << pts[i] << std::endl;
      pts[i + 1] = Vector2<T>(x, static_cast<int32_t>(intersectY) - 1);
              // std::cout << pts[i] << std::endl;

      if (pts[i + 1].y < 0)
      {
        pts[i + 1].y = 0;
      }

//    drawPixel(x, (static_cast<int32_t>(intersectY), 1 - intersectY);
//    drawPixel(x, (static_cast<int32_t>(intersectY) - 1, getDecimalFromFloat(intersectY));
      intersectY += gradient;
      i += 2;
    }
  }

  return pts;
}

// TODO: Shouldn't go here move to another file
template <typename T>
float PlotUtility<T>::getDecimalFromFloat(float val)
{
  if (val > 0)
  {
    return val - (static_cast<int32_t>(val));
  }
  else
  {
    return val - (static_cast<int32_t>(val) + 1);
  }
}

#endif