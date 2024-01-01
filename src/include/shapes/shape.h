#ifndef SHAPE_H
#define SHAPE_H

#include "Vector.h"

template<typename T>
class Shape
{
  public:
    Shape() = default;
    virtual ~Shape() = default;

    Vector2<T> getSize();
    Vector2<T> getPos();
    virtual void setSize(const Vector2<T>& crSize) = 0;
    virtual void setPos(const Vector2<T>& crPos) = 0;
    virtual void movePos(const Vector2<T>& crMoveVector) = 0;
    virtual bool inLocalBounds(const Vector2<int32_t>& crPos) = 0;
    virtual bool inLocalBounds(const Vector2<float>& crPos) = 0;
  protected:
    Vector2<T> mSize;
    Vector2<T> mPos;
};

template<typename T>
Vector2<T> Shape<T>::getSize()
{
  return mSize;
}

template<typename T>
Vector2<T> Shape<T>::getPos()
{
  return mPos;
}

#endif