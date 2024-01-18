#ifndef BOX_H
#define BOX_H

#include "shapes/shape.h"
#include "glm/vec2.hpp"

template <typename T>
class Box : public Shape<T>
{
  public:
    Box() = default;
    Box(const T& crPos, const T& crSize);
    ~Box() = default;
    void setPos(const T& crPos);
    void setSize(const T& crSize);
    T getTopLeft();
    void movePos(const T& crMoveVector);
    void setBoxTopLeft(const T& crPos, const T& crSize);
    void setBox(const T& crPos, const T& crSize);
    void setTopLeft(const T& crPos);
    bool inLocalBounds(const glm::ivec2& crPos);
    bool inLocalBounds(const glm::vec2& crPos);
  private:
    T mTopLeft;

    void updateTopLeft();
    void updatePos();
};

template <typename T>
void Box<T>::setBoxTopLeft(const T& crPos, const T& crSize)
{
  this->mSize = crSize;
  mTopLeft = crPos;
  updatePos();
}

template <typename T>
void Box<T>::setBox(const T& crPos, const T& crSize)
{
  this->mSize = crSize;
  this->mPos = crPos;
  updateTopLeft();
}

template <typename T>
void Box<T>::setTopLeft(const T& crPos)
{
  mTopLeft = crPos;
}

template <typename T>
Box<T>::Box(const T& crPos, const T& crSize)
{
  updateBoxPos(crPos, crSize);
}

template <typename T>
void Box<T>::setPos(const T& crPos)
{
  this->mPos = crPos;
  updateTopLeft();
}

template <typename T>
void Box<T>::updateTopLeft()
{
  const float DIVISOR = 2.0;

  mTopLeft.x = this->mPos.x - (this->mSize.x / DIVISOR);
  mTopLeft.y = this->mPos.y - (this->mSize.y / DIVISOR);
}

template <typename T>
void Box<T>::updatePos()
{
  const float DIVISOR = 2.0;
  this->mPos.x = mTopLeft.x + (this->mSize.x / DIVISOR);
  this->mPos.y = mTopLeft.y + (this->mSize.y / DIVISOR);
}

template<typename T>
void Box<T>::setSize(const T& crSize)
{
  this->mSize = crSize;
  updateTopLeft();
}

template <typename T>
T Box<T>::getTopLeft()
{
  return mTopLeft;
}

template <typename T>
void Box<T>::movePos(const T& crMoveVector)
{
  this->mPos += crMoveVector;
  updateTopLeft();
}

template <typename T>
bool Box<T>::inLocalBounds(const glm::ivec2& crPos)
{
  return (crPos.x > mTopLeft.x) && (crPos.x < (mTopLeft.x + this->mSize.x)) &&
         (crPos.y > mTopLeft.y) && (crPos.y < (mTopLeft.y + this->mSize.y));
}

template <typename T>
bool Box<T>::inLocalBounds(const glm::vec2& crPos)
{
  return (crPos.x > mTopLeft.x) && (crPos.x < (mTopLeft.x + this->mSize.x)) &&
         (crPos.y > mTopLeft.y) && (crPos.y < (mTopLeft.y + this->mSize.y));
}

#endif