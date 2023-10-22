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
  return ((crP1.mY == crP2.mY) || (crP1.mX == crP2.mX));
}


template <typename T>
bool PlotUtility<T>::arePointsInRange(const Vector2<T> &crP1, const Vector2<T> &crP2)
{
  Vector2<int32_t> point(crP2.mX - crP1.mX, crP2.mY - crP1.mY);
  point.mX = abs(point.mX);
  point.mY = abs(point.mY);

  return ((1 == point.mY || 0 == point.mY) && (1 == point.mX || 0 == point.mX));
}

template <typename T>
bool PlotUtility<T>::arePointsTouching(const Vector2<T> &crP1, const Vector2<T> &crP2)
{
  Vector2<int32_t> point(crP2.mX - crP1.mX, crP2.mY - crP1.mY);
  point.mX = abs(point.mX);
  point.mY = abs(point.mY);

  return ((1 == point.mX || 0 == point.mX) && (1 == point.mY || 0 == point.mY));
}

template <typename T>
bool PlotUtility<T>::sortByXIntersection(const Vector2<T>& crP1, const Vector2<T>& crP2)
{
   if (crP1.mY == crP2.mY)
   {
      return crP1.mX < crP2.mX;
   }

   return crP1.mY < crP2.mY;
}

template <typename T>
bool PlotUtility<T>::sortByYIntersection(const Vector2<T>& crP1, const Vector2<T>& crP2)
{
   if (crP1.mX == crP2.mX)
   {
      return crP1.mY < crP2.mY;
   }

   return crP1.mX < crP2.mX;
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
    crPoints[itemsAdded + cOffset] = Vector2<T>((t1 * t1 * rP0.mX + 2 * t1 * t * rP1.mX + t2 * rP2.mX),
                                                (t1 * t1 * rP0.mY + 2 * t1 * t * rP1.mY + t2 * rP2.mY));
    itemsAdded ++;
  }

  return itemsAdded;
}

template <typename T>
void PlotUtility<T>::drawPixelInBitmap(const Vector2<T>& crP1, std::vector<uint32_t> &rBitmap, const uint32_t cNumCols,
                                       const lg::Color &crColor)
{
  rBitmap[(crP1.mY * cNumCols) + crP1.mX] = crColor.getRgba();
}

template <typename T>
void PlotUtility<T>::drawStraightLineToPoint(const Vector2<T>& crP1, const Vector2<T>& crP2, 
                                             std::vector<uint32_t> &rBitmap, const uint32_t cNumCols,
                                             const lg::Color &crColor)
{
  if(crP1.mX == crP2.mX)
  {
    int8_t addr = 1;

    if(crP1.mY > crP2.mY)
    {
      addr = -1;
    }

    int32_t numPts = crP2.mY - crP1.mY - 1;
    int16_t start_pt = crP1.mY + addr;

    for(int i = 0; i < numPts; i ++)
    {
      rBitmap[(start_pt * cNumCols) + crP1.mX] = crColor.getRgba();
      start_pt += addr;
    }
  }
  else
  {
    int8_t addr = 1;

    if(crP1.mX > crP2.mX)
    {
      addr = -1;
    }

    int32_t numPts = crP2.mX - crP1.mX - 1;
    int16_t start_pt = crP1.mX + addr;

    for(int i = 0; i < numPts; i ++)
    {
      rBitmap[(crP1.mY * cNumCols) + start_pt] = crColor.getRgba();
      start_pt += addr;
    }
  }
}

template <typename T>
void PlotUtility<T>::plotLineLow(const Vector2<T> cP1, const Vector2<T> cP2, std::vector<uint32_t> &rBitmap,
                                 const uint32_t cNumCols, const lg::Color &crColor)
{
  int32_t dx = cP2.mX - cP1.mX;
  int32_t dy = cP2.mY - cP1.mY;

  int32_t yi = 1;

  if(0 > dy)
  {
    yi = -1;
    dy = -dy;
  }

  int32_t D = (2 * dy) - dx;
  int32_t y = cP1.mY;

  for(int32_t x = cP1.mX; x <= cP2.mX; x++)
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
  int32_t dx = cP2.mX - cP1.mX;
  int32_t dy = cP2.mY - cP1.mY;
  int32_t xi = 1;

  if(0 > dx)
  {
    xi = -1;
    dx = -dx;
  }

  int32_t D = (2 * dx) - dy;
  int32_t x = cP1.mX;

  for(int32_t y = cP1.mY; y <= cP2.mY; y++)
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
  if(abs(cP2.mY - cP1.mY) < abs(cP2.mX - cP1.mX))
  {
    if(cP1.mX > cP2.mX)
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
    if(cP1.mY > cP2.mY)
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

  if(crP1.mX == crP2.mX)
  {
    int8_t addr = 1;

    if(crP1.mY > crP2.mY)
    {
      addr = -1;
    }

    pts.resize(abs(crP2.mY - crP1.mY) - 1);
    int16_t start_pt = crP1.mY + addr;

    for(int i = 0; i < pts.size(); i ++)
    {
      pts[i] = Vector2<T>(crP1.mX, start_pt);
      start_pt += addr;
    }
  }
  else
  {
    int8_t addr = 1;

    if(crP1.mX > crP2.mX)
    {
      addr = -1;
    }

    pts.resize(abs(crP2.mX - crP1.mX) - 1);
    int16_t start_pt = crP1.mX + addr;

    for(int i = 0; i < pts.size(); i ++)
    {
      pts[i] = Vector2<T>(start_pt, crP1.mY);
      start_pt += addr;
    }
  }

  return pts;
}

template <typename T>
std::vector<Vector2<T>> PlotUtility<T>::plotLineLow(const Vector2<T> cP1, const Vector2<T> cP2)
{
  std::vector<Vector2<T>> pts;
  int32_t dx = cP2.mX - cP1.mX;
  int32_t dy = cP2.mY - cP1.mY;

  int32_t yi = 1;

  if(0 > dy)
  {
    yi = -1;
    dy = -dy;
  }

  int32_t D = (2 * dy) - dx;
  int32_t y = cP1.mY;
  pts.resize(cP2.mX - cP1.mX);

  for(int32_t x = cP1.mX; x < cP2.mX; x++)
  {
    pts[x - cP1.mX] = Vector2<T>(x, y);

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
  int32_t dx = cP2.mX - cP1.mX;
  int32_t dy = cP2.mY - cP1.mY;
  int32_t xi = 1;

  if(0 > dx)
  {
    xi = -1;
    dx = -dx;
  }

  int32_t D = (2 * dx) - dy;
  int32_t x = cP1.mX;
  pts.resize(cP2.mY - cP1.mY);

  for(int32_t y = cP1.mY; y < cP2.mY; y++)
  {
    pts[y - cP1.mY] = Vector2<T>(x, y);

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
  if(abs(cP2.mY - cP1.mY) < abs(cP2.mX - cP1.mX))
  {
    if(cP1.mX > cP2.mX)
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
    if(cP1.mY > cP2.mY)
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
  int32_t steep = abs(p2.mY - p1.mY) > abs(p2.mX - p1.mX);
  std::vector<Vector2<T>> pts;

  // swap the co-ordinates if slope > 1 or we
  // draw backwards
  if (steep)
  {
    std::swap(p1.mX , p1.mY);
    std::swap(p2.mX , p2.mY);
  }
  if (p1.mX > p2.mX)
  {
    std::swap(p1.mX ,p2.mX);
    std::swap(p1.mY ,p2.mY);
  }

  //compute the slope
  float dx = p2.mX - p1.mX;
  float dy = p2.mY - p1.mY;
  float gradient = dy / dx;

  if (dx == 0.0)
  {
    gradient = 1;
  }

  int32_t xpxl1 = p1.mX;
  int32_t xpxl2 = p2.mX;
  float intersectY = p1.mY;

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

      if (pts[i + 1].mX < 0)
      {
        pts[i + 1].mX = 0;
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

      if (pts[i + 1].mY < 0)
      {
        pts[i + 1].mY = 0;
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