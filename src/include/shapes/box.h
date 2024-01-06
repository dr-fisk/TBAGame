#ifndef BOX_H
#define BOX_H

#include "shapes/shape.h"

template <typename T>
class Box : public Shape<T>
{
  public:
    Box() = default;
    Box(const Vector2<T>& crPos, const Vector2<T>& crSize);
    ~Box() = default;
    void setPos(const Vector2<T>& crPos);
    void setSize(const Vector2<T>& crSize);
    Vector2<T> getTopLeft();
    void movePos(const Vector2<T>& crMoveVector);
    void setBoxTopLeft(const Vector2<T>& crPos, const Vector2<T>& crSize);
    void setBox(const Vector2<T>& crPos, const Vector2<T>& crSize);
    void setTopLeft(const Vector2<T>& crPos);
    bool inLocalBounds(const Vector2<int32_t>& crPos);
    bool inLocalBounds(const Vector2<float>& crPos);
  private:
    Vector2<T> mTopLeft;

    void updateTopLeft();
    void updatePos();
};

template <typename T>
void Box<T>::setBoxTopLeft(const Vector2<T>& crPos, const Vector2<T>& crSize)
{
  this->mSize = crSize;
  mTopLeft = crPos;
  updatePos();
}

template <typename T>
void Box<T>::setBox(const Vector2<T>& crPos, const Vector2<T>& crSize)
{
  this->mSize = crSize;
  this->mPos = crPos;
  updateTopLeft();
}

template <typename T>
void Box<T>::setTopLeft(const Vector2<T>& crPos)
{
  mTopLeft = crPos;
}

template <typename T>
Box<T>::Box(const Vector2<T>& crPos, const Vector2<T>& crSize)
{
  updateBoxPos(crPos, crSize);
}

template <typename T>
void Box<T>::setPos(const Vector2<T>& crPos)
{
  this->mPos = crPos;
  updateTopLeft();
}

template <typename T>
void Box<T>::updateTopLeft()
{
  const T DIVISOR = 2;

  mTopLeft.x = this->mPos.x - (this->mSize.x / DIVISOR);
  mTopLeft.y = this->mPos.y - (this->mSize.y / DIVISOR);
}

template <typename T>
void Box<T>::updatePos()
{
  const T DIVISOR = 2;
  this->mPos.x = (mTopLeft.x + this->mSize.x) / DIVISOR;
  this->mPos.y = (mTopLeft.y + this->mSize.y) / DIVISOR;
}

template<typename T>
void Box<T>::setSize(const Vector2<T>& crSize)
{
  this->mSize = crSize;
  updateTopLeft();
}

template <typename T>
Vector2<T> Box<T>::getTopLeft()
{
  return mTopLeft;
}

template <typename T>
void Box<T>::movePos(const Vector2<T>& crMoveVector)
{
  this->mPos += crMoveVector;
  updateTopLeft();
}

template <typename T>
bool Box<T>::inLocalBounds(const Vector2<int32_t>& crPos)
{
  return (crPos.x > mTopLeft.x) && (crPos.x < (mTopLeft.x + this->mSize.x)) &&
         (crPos.y > mTopLeft.y) && (crPos.y < (mTopLeft.y + this->mSize.y));
}

template <typename T>
bool Box<T>::inLocalBounds(const Vector2<float>& crPos)
{
  return (crPos.x > mTopLeft.x) && (crPos.x < (mTopLeft.x + this->mSize.x)) &&
         (crPos.y > mTopLeft.y) && (crPos.y < (mTopLeft.y + this->mSize.y));
}

#endif