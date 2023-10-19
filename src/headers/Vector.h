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
bool Vector2<T>::operator==(const Vector2<T> &crRhs) const
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

#ifdef GLEW_STATIC
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
#endif

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

#ifdef GLEW_STATIC
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
#endif

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

#ifdef GLEW_STATIC
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
#endif

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

#ifdef GLEW_STATIC
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
#endif

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

    T mX;
    T mY;
    T mZ;
};

template <typename T>
Vector3<T>::Vector3(const T cXPos, const T cYPos, const T cZPos) : mX(cXPos), mY(cYPos), mZ(cZPos)
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
  mX = crRhs.mX;
  mY = crRhs.mY;
  mZ = crRhs.mZ;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator+=(const Vector3 &crRhs)
{
  mX += crRhs.mX;
  mY += crRhs.mY;
  mZ += crRhs.mZ;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator-=(const Vector3 &crRhs)
{
  mX -= crRhs.mX;
  mY -= crRhs.mY;
  mZ -= crRhs.mZ;
  return *this;
}

template <typename T>
Vector3<T> Vector3<T>::operator+(const Vector3 &crRhs)
{
  return Vector3<T>(mX + crRhs.mX, mY + crRhs.mY, mZ + crRhs.mZ);
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const Vector3 &crRhs)
{
  return Vector3<T>(mX - crRhs.mX, mY - crRhs.mY, mZ - crRhs.mZ);
}

template <typename T>
bool Vector3<T>::operator!=(const Vector3<T> &crRhs)
{
  return (mX != crRhs.mX) || (mY != crRhs.mY) || (mZ != crRhs.mZ);
}


template <typename T>
bool Vector3<T>::operator==(const Vector3<T> &crRhs)
{
  return (mX == crRhs.mX) && (mY == crRhs.mY) && (mZ == crRhs.mZ);
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const int8_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const int16_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const int32_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const int64_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const uint8_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const uint16_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const uint32_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const uint64_t &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  mZ *= crRhs;
  return *this;
}

#ifdef GLEW_STATIC
template <typename T>
Vector3<T>& Vector3<T>::operator*=(const GLfloat &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  mZ *= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator*=(const GLdouble &crRhs)
{
  mX *= crRhs;
  mY *= crRhs;
  mZ *= crRhs;
  return *this;
}
#endif

template <typename T>
Vector3<T> Vector3<T>::operator*(const int8_t &crRhs)
{
  return Vector3<T>(mX * crRhs, mY * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const int16_t &crRhs)
{
  return Vector3<T>(mX * crRhs, mY * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const int32_t &crRhs)
{
  return Vector3<T>(mX * crRhs, mY * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const int64_t &crRhs)
{
  return Vector3<T>(mX * crRhs, mY * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const uint8_t &crRhs)
{
  return Vector3<T>(mX * crRhs, mY * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const uint16_t &crRhs)
{
  return Vector3<T>(mX * crRhs, mY * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const uint32_t &crRhs)
{
  return Vector3<T>(mX * crRhs, mY * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const uint64_t &crRhs)
{
  return Vector3<T>(mX * crRhs, mY * crRhs, mZ * crRhs);
}

#ifdef GLEW_STATIC
template <typename T>
Vector3<T> Vector3<T>::operator*(const GLfloat &crRhs)
{
  return Vector3<T>(mX * crRhs, mY * crRhs, mZ * crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const GLdouble &crRhs)
{
  return Vector3<T>(mX * crRhs, mY * crRhs, mZ * crRhs);
}
#endif

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const int8_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const int16_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const int32_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const int64_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const uint8_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const uint16_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const uint32_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const uint64_t &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  mZ /= crRhs;
  return *this;
}

#ifdef GLEW_STATIC
template <typename T>
Vector3<T>& Vector3<T>::operator/=(const GLfloat &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  mZ /= crRhs;
  return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator/=(const GLdouble &crRhs)
{
  mX /= crRhs;
  mY /= crRhs;
  mZ /= crRhs;
  return *this;
}
#endif

template <typename T>
Vector3<T> Vector3<T>::operator/(const int8_t &crRhs)
{
  return Vector3<T>(mX / crRhs, mY / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const int16_t &crRhs)
{
  return Vector3<T>(mX / crRhs, mY / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const int32_t &crRhs)
{
  return Vector3<T>(mX / crRhs, mY / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const int64_t &crRhs)
{
  return Vector3<T>(mX / crRhs, mY / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const uint8_t &crRhs)
{
  return Vector3<T>(mX / crRhs, mY / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const uint16_t &crRhs)
{
  return Vector3<T>(mX / crRhs, mY / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const uint32_t &crRhs)
{
  return Vector3<T>(mX / crRhs, mY / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const uint64_t &crRhs)
{
  return Vector3<T>(mX / crRhs, mY / crRhs, mZ / crRhs);
}

#ifdef GLEW_STATIC
template <typename T>
Vector3<T> Vector3<T>::operator/(const GLfloat &crRhs)
{
  return Vector3<T>(mX / crRhs, mY / crRhs, mZ / crRhs);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const GLdouble &crRhs)
{
  return Vector3<T>(mX / crRhs, mY / crRhs, mZ / crRhs);
}
#endif

template <typename T>
T Vector3<T>::operator*(const Vector3<T>& crVector)
{
  return mX * crVector.mX + mY * crVector.mY + mZ * crVector.mZ;
}

template <typename T>
std::ostream& operator<<(std::ostream& rOs, const Vector3<T>& crVector)
{
  rOs << "(" << crVector.mX << ", " << crVector.mY << ", " << crVector.mZ << ")" << std::endl;

  return rOs;
}

#endif