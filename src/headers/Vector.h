#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>
#include <vector>

#ifdef GLEW_STATIC
  #include <GL/glew.h>
  #include <GLFW/glfw3.h>
#endif

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
    bool operator==(const Vector2 &crRhs) const;
    bool operator!=(const Vector2 &crRhs);
    Vector2& operator*=(const int8_t &crRhs);
    Vector2& operator*=(const int16_t &crRhs);
    Vector2& operator*=(const int32_t &crRhs);
    Vector2& operator*=(const int64_t &crRhs);
    Vector2& operator*=(const uint8_t &crRhs);
    Vector2& operator*=(const uint16_t &crRhs);
    Vector2& operator*=(const uint32_t &crRhs);
    Vector2& operator*=(const uint64_t &crRhs);

    #ifdef GLEW_STATIC
      Vector2& operator*=(const GLfloat &crRhs);
      Vector2& operator*=(const GLdouble &crRhs);
    #endif

    Vector2 operator*(const int8_t &crRhs);
    Vector2 operator*(const int16_t &crRhs);
    Vector2 operator*(const int32_t &crRhs);
    Vector2 operator*(const int64_t &crRhs);
    Vector2 operator*(const uint8_t &crRhs);
    Vector2 operator*(const uint16_t &crRhs);
    Vector2 operator*(const uint32_t &crRhs);
    Vector2 operator*(const uint64_t &crRhs);

    #ifdef GLEW_STATIC
      Vector2 operator*(const GLfloat &crRhs);
      Vector2 operator*(const GLdouble &crRhs);
    #endif

    Vector2& operator/=(const int8_t &crRhs);
    Vector2& operator/=(const int16_t &crRhs);
    Vector2& operator/=(const int32_t &crRhs);
    Vector2& operator/=(const int64_t &crRhs);
    Vector2& operator/=(const uint8_t &crRhs);
    Vector2& operator/=(const uint16_t &crRhs);
    Vector2& operator/=(const uint32_t &crRhs);
    Vector2& operator/=(const uint64_t &crRhs);

    #ifdef GLEW_STATIC
      Vector2& operator/=(const GLfloat &crRhs);
      Vector2& operator/=(const GLdouble &crRhs);
    #endif

    Vector2 operator/(const int8_t &crRhs);
    Vector2 operator/(const int16_t &crRhs);
    Vector2 operator/(const int32_t &crRhs);
    Vector2 operator/(const int64_t &crRhs);
    Vector2 operator/(const uint8_t &crRhs);
    Vector2 operator/(const uint16_t &crRhs);
    Vector2 operator/(const uint32_t &crRhs);
    Vector2 operator/(const uint64_t &crRhs);
    
    #ifdef GLEW_STATIC
      Vector2 operator/(const GLfloat &crRhs);
      Vector2 operator/(const GLdouble &crRhs);
    #endif

    T operator*(const Vector2<T>& crVector);
    friend std::ostream& operator<< <>(std::ostream& rOs, const Vector2<T>& crVector);

    T x;
    T y;
};

template <typename T>
Vector2<T>::Vector2(const T cXPos, const T cYPos) : x(cXPos), y(cYPos)
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
  x = crRhs.x;
  y = crRhs.y;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2 &crRhs)
{
  x += crRhs.x;
  y += crRhs.y;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2 &crRhs)
{
  x -= crRhs.x;
  y -= crRhs.y;
  return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2 &crRhs)
{
  return Vector2<T>(x + crRhs.x, y + crRhs.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2 &crRhs)
{
  return Vector2<T>(x - crRhs.x, y - crRhs.y);
}

template <typename T>
bool Vector2<T>::operator!=(const Vector2<T> &crRhs)
{
  return (x != crRhs.x) || (y != crRhs.y);
}


template <typename T>
bool Vector2<T>::operator==(const Vector2<T> &crRhs) const
{
  return (x == crRhs.x) && (y == crRhs.y);
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const int8_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const int16_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const int32_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const int64_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const uint8_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const uint16_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const uint32_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const uint64_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  return *this;
}

#ifdef GLEW_STATIC
template <typename T>
Vector2<T>& Vector2<T>::operator*=(const GLfloat &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const GLdouble &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  return *this;
}
#endif

template <typename T>
Vector2<T> Vector2<T>::operator*(const int8_t &crRhs)
{
  return Vector2<T>(x * crRhs, y * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const int16_t &crRhs)
{
  return Vector2<T>(x * crRhs, y * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const int32_t &crRhs)
{
  return Vector2<T>(x * crRhs, y * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const int64_t &crRhs)
{
  return Vector2<T>(x * crRhs, y * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const uint8_t &crRhs)
{
  return Vector2<T>(x * crRhs, y * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const uint16_t &crRhs)
{
  return Vector2<T>(x * crRhs, y * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const uint32_t &crRhs)
{
  return Vector2<T>(x * crRhs, y * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const uint64_t &crRhs)
{
  return Vector2<T>(x * crRhs, y * crRhs);
}

#ifdef GLEW_STATIC
template <typename T>
Vector2<T> Vector2<T>::operator*(const GLfloat &crRhs)
{
  return Vector2<T>(x * crRhs, y * crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const GLdouble &crRhs)
{
  return Vector2<T>(x * crRhs, y * crRhs);
}
#endif

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const int8_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const int16_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const int32_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const int64_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const uint8_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const uint16_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const uint32_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const uint64_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  return *this;
}

#ifdef GLEW_STATIC
template <typename T>
Vector2<T>& Vector2<T>::operator/=(const GLfloat &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const GLdouble &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  return *this;
}
#endif

template <typename T>
Vector2<T> Vector2<T>::operator/(const int8_t &crRhs)
{
  return Vector2<T>(x / crRhs, y / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const int16_t &crRhs)
{
  return Vector2<T>(x / crRhs, y / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const int32_t &crRhs)
{
  return Vector2<T>(x / crRhs, y / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const int64_t &crRhs)
{
  return Vector2<T>(x / crRhs, y / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const uint8_t &crRhs)
{
  return Vector2<T>(x / crRhs, y / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const uint16_t &crRhs)
{
  return Vector2<T>(x / crRhs, y / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const uint32_t &crRhs)
{
  return Vector2<T>(x / crRhs, y / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const uint64_t &crRhs)
{
  return Vector2<T>(x / crRhs, y / crRhs);
}

#ifdef GLEW_STATIC
template <typename T>
Vector2<T> Vector2<T>::operator/(const GLfloat &crRhs)
{
  return Vector2<T>(x / crRhs, y / crRhs);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const GLdouble &crRhs)
{
  return Vector2<T>(x / crRhs, y / crRhs);
}
#endif

template <typename T>
T Vector2<T>::operator*(const Vector2<T>& crVector)
{
  return x * crVector.x + y * crVector.y;
}

template <typename T>
std::ostream& operator<<(std::ostream& rOs, const Vector2<T>& crVector)
{
  rOs << "(" << crVector.x << ", " << crVector.y << ")" << std::endl;

  return rOs;
}

template <typename T> 
class Vector2;

template <typename T>
std::ostream& operator<<(std::ostream& rOs, const Vector2<T>& crVector);

template <typename T> class Vector3
{
  public:
    Vector3(const T cXPos, const T cYPos, T cZPos);
    Vector3(const Vector3 &crRhs);
    Vector3();
    ~Vector3();
    Vector3& operator=(const Vector3 &crRhs);
    Vector3& operator+=(const Vector3 &crRhs);
    Vector3 operator+(const Vector3 &crRhs);
    Vector3& operator-=(const Vector3 &crRhs);
    Vector3 operator-(const Vector3 &crRhs);
    bool operator==(const Vector3 &crRhs);
    bool operator!=(const Vector3 &crRhs);
    Vector3& operator*=(const int8_t &crRhs);
    Vector3& operator*=(const int16_t &crRhs);
    Vector3& operator*=(const int32_t &crRhs);
    Vector3& operator*=(const int64_t &crRhs);
    Vector3& operator*=(const uint8_t &crRhs);
    Vector3& operator*=(const uint16_t &crRhs);
    Vector3& operator*=(const uint32_t &crRhs);
    Vector3& operator*=(const uint64_t &crRhs);

    #ifdef GLEW_STATIC
      Vector3& operator*=(const GLfloat &crRhs);
      Vector3& operator*=(const GLdouble &crRhs);
    #endif

    Vector3 operator*(const int8_t &crRhs);
    Vector3 operator*(const int16_t &crRhs);
    Vector3 operator*(const int32_t &crRhs);
    Vector3 operator*(const int64_t &crRhs);
    Vector3 operator*(const uint8_t &crRhs);
    Vector3 operator*(const uint16_t &crRhs);
    Vector3 operator*(const uint32_t &crRhs);
    Vector3 operator*(const uint64_t &crRhs);

    #ifdef GLEW_STATIC
      Vector3 operator*(const GLfloat &crRhs);
      Vector3 operator*(const GLdouble &crRhs);
    #endif

    Vector3& operator/=(const int8_t &crRhs);
    Vector3& operator/=(const int16_t &crRhs);
    Vector3& operator/=(const int32_t &crRhs);
    Vector3& operator/=(const int64_t &crRhs);
    Vector3& operator/=(const uint8_t &crRhs);
    Vector3& operator/=(const uint16_t &crRhs);
    Vector3& operator/=(const uint32_t &crRhs);
    Vector3& operator/=(const uint64_t &crRhs);

    #ifdef GLEW_STATIC
      Vector3& operator/=(const GLfloat &crRhs);
      Vector3& operator/=(const GLdouble &crRhs);
    #endif

    Vector3 operator/(const int8_t &crRhs);
    Vector3 operator/(const int16_t &crRhs);
    Vector3 operator/(const int32_t &crRhs);
    Vector3 operator/(const int64_t &crRhs);
    Vector3 operator/(const uint8_t &crRhs);
    Vector3 operator/(const uint16_t &crRhs);
    Vector3 operator/(const uint32_t &crRhs);
    Vector3 operator/(const uint64_t &crRhs);
    
    #ifdef GLEW_STATIC
      Vector3 operator/(const GLfloat &crRhs);
      Vector3 operator/(const GLdouble &crRhs);
    #endif

    T operator*(const Vector3<T>& crVector);
    friend std::ostream& operator<< <>(std::ostream& rOs, const Vector3<T>& crVector);

    T x;
    T y;
    T mZ;
};

template <typename T>
Vector3<T>::Vector3(const T cXPos, const T cYPos, const T cZPos) : x(cXPos), y(cYPos), mZ(cZPos)
{
}

template <typename T>
Vector3<T>::Vector3(const Vector3<T> &crRhs)
{
  *this = crRhs;
}

template <typename T>
Vector3<T>::Vector3()
{

}

template <typename T>
Vector3<T>::~Vector3()
{

}

template <typename T>
Vector3<T>& Vector3<T>::operator=(const Vector3<T> &crRhs)
{
  x = crRhs.x;
  y = crRhs.y;
  mZ = crRhs.mZ;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator+=(const Vector3 &crRhs)
{
  x += crRhs.x;
  y += crRhs.y;
  mZ += crRhs.mZ;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator-=(const Vector3 &crRhs)
{
  x -= crRhs.x;
  y -= crRhs.y;
  mZ -= crRhs.mZ;
  return *this;
}

template <typename T>
Vector3<T> Vector3<T>::operator+(const Vector3 &crRhs)
{
  return Vector3<T>(x + crRhs.x, y + crRhs.y, mZ + crRhs.mZ);
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const Vector3 &crRhs)
{
  return Vector3<T>(x - crRhs.x, y - crRhs.y, mZ - crRhs.mZ);
}

template <typename T>
bool Vector3<T>::operator!=(const Vector3<T> &crRhs)
{
  return (x != crRhs.x) || (y != crRhs.y) || (mZ != crRhs.mZ);
}


template <typename T>
bool Vector3<T>::operator==(const Vector3<T> &crRhs)
{
  return (x == crRhs.x) && (y == crRhs.y) && (mZ == crRhs.mZ);
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const int8_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const int16_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const int32_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const int64_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const uint8_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const uint16_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const uint32_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const uint64_t &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  mZ *= crRhs;
  return *this;
}

#ifdef GLEW_STATIC
template <typename T>
Vector3<T>& Vector3<T>::operator*=(const GLfloat &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const GLdouble &crRhs)
{
  x *= crRhs;
  y *= crRhs;
  mZ *= crRhs;
  return *this;
}
#endif

template <typename T>
Vector3<T> Vector3<T>::operator*(const int8_t &crRhs)
{
  return Vector3<T>(x * crRhs, y * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const int16_t &crRhs)
{
  return Vector3<T>(x * crRhs, y * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const int32_t &crRhs)
{
  return Vector3<T>(x * crRhs, y * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const int64_t &crRhs)
{
  return Vector3<T>(x * crRhs, y * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const uint8_t &crRhs)
{
  return Vector3<T>(x * crRhs, y * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const uint16_t &crRhs)
{
  return Vector3<T>(x * crRhs, y * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const uint32_t &crRhs)
{
  return Vector3<T>(x * crRhs, y * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const uint64_t &crRhs)
{
  return Vector3<T>(x * crRhs, y * crRhs, mZ * crRhs);
}

#ifdef GLEW_STATIC
template <typename T>
Vector3<T> Vector3<T>::operator*(const GLfloat &crRhs)
{
  return Vector3<T>(x * crRhs, y * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const GLdouble &crRhs)
{
  return Vector3<T>(x * crRhs, y * crRhs, mZ * crRhs);
}
#endif

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const int8_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const int16_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const int32_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const int64_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const uint8_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const uint16_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const uint32_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const uint64_t &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  mZ /= crRhs;
  return *this;
}

#ifdef GLEW_STATIC
template <typename T>
Vector3<T>& Vector3<T>::operator/=(const GLfloat &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const GLdouble &crRhs)
{
  x /= crRhs;
  y /= crRhs;
  mZ /= crRhs;
  return *this;
}
#endif

template <typename T>
Vector3<T> Vector3<T>::operator/(const int8_t &crRhs)
{
  return Vector3<T>(x / crRhs, y / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const int16_t &crRhs)
{
  return Vector3<T>(x / crRhs, y / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const int32_t &crRhs)
{
  return Vector3<T>(x / crRhs, y / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const int64_t &crRhs)
{
  return Vector3<T>(x / crRhs, y / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const uint8_t &crRhs)
{
  return Vector3<T>(x / crRhs, y / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const uint16_t &crRhs)
{
  return Vector3<T>(x / crRhs, y / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const uint32_t &crRhs)
{
  return Vector3<T>(x / crRhs, y / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const uint64_t &crRhs)
{
  return Vector3<T>(x / crRhs, y / crRhs, mZ / crRhs);
}

#ifdef GLEW_STATIC
template <typename T>
Vector3<T> Vector3<T>::operator/(const GLfloat &crRhs)
{
  return Vector3<T>(x / crRhs, y / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const GLdouble &crRhs)
{
  return Vector3<T>(x / crRhs, y / crRhs, mZ / crRhs);
}
#endif

template <typename T>
T Vector3<T>::operator*(const Vector3<T>& crVector)
{
  return x * crVector.x + y * crVector.y + mZ * crVector.mZ;
}

template <typename T>
std::ostream& operator<<(std::ostream& rOs, const Vector3<T>& crVector)
{
  rOs << "(" << crVector.x << ", " << crVector.y << ", " << crVector.mZ << ")" << std::endl;

  return rOs;
}

#endif