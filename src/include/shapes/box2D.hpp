#ifndef BOX_2D_HPP
#define BOX_2D_HPP

#include "shapes/shape.hpp"

template <typename T>
class Box2D : public Shape<T>
{
  public:
    Box2D();
    ~Box2D() = default;
    Box2D(const T cLeft, const T cTop, const T cWidth, const T cHeight);
    Box2D& setPos(const T cLeft, const T cTop);
    Box2D& setSize(const T cWidth, const T cHeight);
    void getCenter(T& rX, T& rY) const;
    void movePos(const T cX, const T cY);
    bool contains(const T cX, const T cY);

    T left;
    T top;
    T width;
    T height;
};

template <typename T>
Box2D<T>::Box2D()
{
  left = 0;
  top = 0;
  width = 1;
  height = 1;
}

template <typename T>
Box2D<T>::Box2D(const T cLeft, const T cTop, const T cWidth, const T cHeight)
{
  left = cLeft;
  top = cTop;
  width = cWidth;
  height = cHeight;
}

template <typename T>
Box2D<T>& Box2D<T>::setPos(const T cLeft, const T cTop)
{
  left = cLeft;
  top = cTop;
  return *this;
}

template <typename T>
Box2D<T>& Box2D<T>::setSize(const T cWidth, const T cHeight)
{
  width = cWidth;
  height = cHeight;
  return *this;
}

template <typename T>
void Box2D<T>::getCenter(T& rX, T& rY) const
{
  rX = left - width / 2.0f;
  rY = top - height / 2.0f;
}

template <typename T>
void Box2D<T>::movePos(const T cX, const T cY)
{
  left += cX;
  top += cY;
}

template <typename T>
bool Box2D<T>::contains(const T cX, const T cY)
{
  return (left < cX) && (left + width > cX) && (top < cY) && (top + height > cY);
}


#endif