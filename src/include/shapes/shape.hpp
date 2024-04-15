#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "glm/vec2.hpp"

template<typename T>
class Shape
{
  public:
    Shape() = default;
    virtual ~Shape() = default;

    T getSize() const;
    T getPos() const;
    virtual void setSize(const T& crSize) = 0;
    virtual void setPos(const T& crPos) = 0;
    virtual void movePos(const T& crMoveVector) = 0;
    virtual bool inLocalBounds(const glm::ivec2& crPos) const = 0;
    virtual bool inLocalBounds(const glm::vec2& crPos) const = 0;
  protected:
    T mSize;
    T mPos;
};

template<typename T>
T Shape<T>::getSize() const
{
  return mSize;
}

template<typename T>
T Shape<T>::getPos() const
{
  return mPos;
}

#endif