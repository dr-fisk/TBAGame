#ifndef SHAPE_H
#define SHAPE_H

#include "glm/vec2.hpp"

template<typename T>
class Shape
{
  public:
    Shape() = default;
    virtual ~Shape() = default;

    T getSize();
    T getPos();
    virtual void setSize(const T& crSize) = 0;
    virtual void setPos(const T& crPos) = 0;
    virtual void movePos(const T& crMoveVector) = 0;
    virtual bool inLocalBounds(const glm::ivec2& crPos) = 0;
    virtual bool inLocalBounds(const glm::vec2& crPos) = 0;
  protected:
    T mSize;
    T mPos;
};

template<typename T>
T Shape<T>::getSize()
{
  return mSize;
}

template<typename T>
T Shape<T>::getPos()
{
  return mPos;
}

#endif