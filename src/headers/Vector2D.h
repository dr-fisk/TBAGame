#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <ostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

template <typename T> 
class Vector2;

template <typename T>
std::ostream& operator<<(std::ostream& rOs, const Vector2<T>& crVector);

template <typename T> class Vector2
{
  public:
    Vector2(const T cXPos, const T cYPos);
    Vector2(const Vector2 &crRhs);
    Vector2();
    ~Vector2();
    Vector2& operator=(const Vector2 &crRhs);
    Vector2& operator+=(const Vector2 &crRhs);
    Vector2 operator+(const Vector2 &crRhs);
    Vector2& operator-=(const Vector2 &crRhs);
    Vector2 operator-(const Vector2 &crRhs);
    bool operator==(const Vector2 &crRhs);
    bool operator!=(const Vector2 &crRhs);
    Vector2& operator*=(const int8_t &crRhs);
    Vector2& operator*=(const int16_t &crRhs);
    Vector2& operator*=(const int32_t &crRhs);
    Vector2& operator*=(const int64_t &crRhs);
    Vector2& operator*=(const uint8_t &crRhs);
    Vector2& operator*=(const uint16_t &crRhs);
    Vector2& operator*=(const uint32_t &crRhs);
    Vector2& operator*=(const uint64_t &crRhs);
    Vector2& operator*=(const GLfloat &crRhs);
    Vector2& operator*=(const GLdouble &crRhs);
    Vector2 operator*(const int8_t &crRhs);
    Vector2 operator*(const int16_t &crRhs);
    Vector2 operator*(const int32_t &crRhs);
    Vector2 operator*(const int64_t &crRhs);
    Vector2 operator*(const uint8_t &crRhs);
    Vector2 operator*(const uint16_t &crRhs);
    Vector2 operator*(const uint32_t &crRhs);
    Vector2 operator*(const uint64_t &crRhs);
    Vector2 operator*(const GLfloat &crRhs);
    Vector2 operator*(const GLdouble &crRhs);
    Vector2& operator/=(const int8_t &crRhs);
    Vector2& operator/=(const int16_t &crRhs);
    Vector2& operator/=(const int32_t &crRhs);
    Vector2& operator/=(const int64_t &crRhs);
    Vector2& operator/=(const uint8_t &crRhs);
    Vector2& operator/=(const uint16_t &crRhs);
    Vector2& operator/=(const uint32_t &crRhs);
    Vector2& operator/=(const uint64_t &crRhs);
    Vector2& operator/=(const GLfloat &crRhs);
    Vector2& operator/=(const GLdouble &crRhs);
    Vector2 operator/(const int8_t &crRhs);
    Vector2 operator/(const int16_t &crRhs);
    Vector2 operator/(const int32_t &crRhs);
    Vector2 operator/(const int64_t &crRhs);
    Vector2 operator/(const uint8_t &crRhs);
    Vector2 operator/(const uint16_t &crRhs);
    Vector2 operator/(const uint32_t &crRhs);
    Vector2 operator/(const uint64_t &crRhs);
    Vector2 operator/(const GLfloat &crRhs);
    Vector2 operator/(const GLdouble &crRhs);
    T operator*(const Vector2<T>& crVector);
    friend std::ostream& operator<< <>(std::ostream& rOs, const Vector2<T>& crVector);
    static uint32_t tessellateQuadBezier(std::vector<Vector2>& crPoints, const uint32_t cOffset,
                                         uint32_t cSubDiv, Vector2& rP0, Vector2& rP1, Vector2& rP2);
    static bool arePointsInRange(const Vector2& crP1, const Vector2& crP2);
    static bool arePointsTouching(const Vector2& crP1, const Vector2& crP2);
    static std::vector<Vector2> drawStraightLineToPoint(const Vector2& crP1, const Vector2& crP2);
    static std::vector<Vector2> plotLineLow(const Vector2 cP1, const Vector2 cP2);
    static std::vector<Vector2> plotLineHigh(const Vector2 cP1, const Vector2 cP2);
    static std::vector<Vector2> plotLine(const Vector2 cP1, const Vector2 cP2);
    static bool sortByXIntersection(const Vector2& crP1, const Vector2& crP2);

    T mX;
    T mY;
};

template <typename T>
Vector2<T>::Vector2(const T cXPos, const T cYPos) : mX(cXPos), mY(cYPos)
{
}

template <typename T>
Vector2<T>::Vector2(const Vector2<T> &crRhs)
{
  *this = crRhs;
}

template <typename T>
Vector2<T>::Vector2()
{

}

template <typename T>
Vector2<T>::~Vector2()
{

}

template <typename T>
Vector2<T>& Vector2<T>::operator=(const Vector2<T> &crRhs)
{
  mX = crRhs.mX;
  mY = crRhs.mY;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2 &crRhs)
{
  mX += crRhs.mX;
  mY += crRhs.mY;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2 &crRhs)
{
  mX -= crRhs.mX;
  mY -= crRhs.mY;
  return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2 &crRhs)
{
  return Vector2<T>(mX + crRhs.mX, mY + crRhs.mY);
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2 &crRhs)
{
  return Vector2<T>(mX - crRhs.mX, mY - crRhs.mY);
}

template <typename T>
bool Vector2<T>::operator!=(const Vector2<T> &crRhs)
{
  return (mX != crRhs.mX) || (mY != crRhs.mY);
}


template <typename T>
bool Vector2<T>::operator==(const Vector2<T> &crRhs)
{
  return (mX == crRhs.mX) && (mY == crRhs.mY);
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const int8_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const int16_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const int32_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const int64_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const uint8_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const uint16_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const uint32_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const uint64_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const GLfloat &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const GLdouble &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const int8_t &crRhs)
{
  return Vector2<T>(mX * crRhs, mY * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const int16_t &crRhs)
{
  return Vector2<T>(mX * crRhs, mY * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const int32_t &crRhs)
{
  return Vector2<T>(mX * crRhs, mY * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const int64_t &crRhs)
{
  return Vector2<T>(mX * crRhs, mY * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const uint8_t &crRhs)
{
  return Vector2<T>(mX * crRhs, mY * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const uint16_t &crRhs)
{
  return Vector2<T>(mX * crRhs, mY * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const uint32_t &crRhs)
{
  return Vector2<T>(mX * crRhs, mY * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const uint64_t &crRhs)
{
  return Vector2<T>(mX * crRhs, mY * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const GLfloat &crRhs)
{
  return Vector2<T>(mX * crRhs, mY * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const GLdouble &crRhs)
{
  return Vector2<T>(mX * crRhs, mY * crRhs);
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const int8_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const int16_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const int32_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const int64_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const uint8_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const uint16_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const uint32_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const uint64_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const GLfloat &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const GLdouble &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const int8_t &crRhs)
{
  return Vector2<T>(mX / crRhs, mY / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const int16_t &crRhs)
{
  return Vector2<T>(mX / crRhs, mY / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const int32_t &crRhs)
{
  return Vector2<T>(mX / crRhs, mY / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const int64_t &crRhs)
{
  return Vector2<T>(mX / crRhs, mY / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const uint8_t &crRhs)
{
  return Vector2<T>(mX / crRhs, mY / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const uint16_t &crRhs)
{
  return Vector2<T>(mX / crRhs, mY / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const uint32_t &crRhs)
{
  return Vector2<T>(mX / crRhs, mY / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const uint64_t &crRhs)
{
  return Vector2<T>(mX / crRhs, mY / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const GLfloat &crRhs)
{
  return Vector2<T>(mX / crRhs, mY / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const GLdouble &crRhs)
{
  return Vector2<T>(mX / crRhs, mY / crRhs);
}

template <typename T>
T Vector2<T>::operator*(const Vector2<T>& crVector)
{
  return mX * crVector.mX + mY * crVector.mY;
}

template <typename T>
std::ostream& operator<<(std::ostream& rOs, const Vector2<T>& crVector)
{
  rOs << "(" << crVector.mX << ", " << crVector.mY << ")" << std::endl;

  return rOs;
}

template <typename T>
uint32_t Vector2<T>::tessellateQuadBezier(std::vector<Vector2<T>>& crPoints, const uint32_t cOffset,
                              uint32_t cSubDiv, Vector2<T>& rP0, Vector2<T>& rP1, Vector2<T>& rP2)
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
    crPoints[itemsAdded + cOffset] = Vector2<T>((t1 * t1 * rP0.mX + 2 * t1 * t * rP1.mX + t2 * rP2.mX),
                                                (t1 * t1 * rP0.mY + 2 * t1 * t * rP1.mY + t2 * rP2.mY));
    itemsAdded ++;
  }

  return itemsAdded;
}

template <typename T>
bool Vector2<T>::arePointsInRange(const Vector2<T>& crP1, const Vector2<T>& crP2)
{
  Vector2<int32_t> point(crP2.mX - crP1.mX, crP2.mY - crP1.mY);
  point.mX = abs(point.mX);
  point.mY = abs(point.mY);

  return ((1 == point.mY || 0 == point.mY) && (1 == point.mX || 0 == point.mX));
}

template <typename T>
bool Vector2<T>::arePointsTouching(const Vector2<T>& crP1, const Vector2<T>& crP2)
{
  Vector2<int32_t> point(crP2.mX - crP1.mX, crP2.mY - crP1.mY);
  point.mX = abs(point.mX);
  point.mY = abs(point.mY);

  return ((1 == point.mY && 0 == point.mX) || (1 == point.mX && 0 == point.mY));
}

template <typename T>
std::vector<Vector2<T>> Vector2<T>::drawStraightLineToPoint(const Vector2<T>& crP1, const Vector2<T>& crP2)
{
  std::vector<Vector2<T>> pts;

  if(crP1.mX == crP2.mX)
  {
    int addr = 1;

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
    int addr = 1;

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
std::vector<Vector2<T>> Vector2<T>::plotLineLow(const Vector2<T> cP1, const Vector2<T> cP2)
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
  pts.resize(cP2.mX -  cP1.mX);

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
std::vector<Vector2<T>> Vector2<T>::plotLineHigh(const Vector2<T> cP1, const Vector2<T> cP2)
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
  pts.resize(cP2.mY -  cP1.mY);

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
std::vector<Vector2<T>> Vector2<T>::plotLine(const Vector2<T> cP1, const Vector2<T> cP2)
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
bool Vector2<T>::sortByXIntersection(const Vector2<T>& crP1, const Vector2<T>& crP2)
{
   if (crP1.mY == crP2.mY)
   {
      return crP1.mX < crP2.mX;
   }

   return crP1.mY < crP2.mY;
}

#endif