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