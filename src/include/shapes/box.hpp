#ifndef BOX_HPP
#define BOX_HPP

#include "shapes/shape.hpp"
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

    static Box<T> createBoxTopLeft(const T& crPos, const T& crSize);
  private:
    void updatePos(const T& crPos);
    T calcTopLeft();
};

template <typename T>
Box<T> Box<T>::createBoxTopLeft(const T& crPos, const T& crSize)
{
  Box<T> box;
  box.setBoxTopLeft(crPos, crSize);
  return box;
}

template <typename T>
void Box<T>::setBoxTopLeft(const T& crPos, const T& crSize)
{
  this->mSize = abs(crSize);
  updatePos(crPos);
}

template <typename T>
void Box<T>::setBox(const T& crPos, const T& crSize)
{
  this->mSize = abs(crSize);
  this->mPos = crPos;
}

template <typename T>
void Box<T>::setTopLeft(const T& crPos)
{
  updatePos(crPos);
}

template <typename T>
Box<T>::Box(const T& crPos, const T& crSize)
{
  this->mSize = abs(crSize);
  this->mPos = crPos;
}

template <typename T>
void Box<T>::setPos(const T& crPos)
{
  this->mPos = crPos;
}

template <typename T>
void Box<T>::updatePos(const T& crPos)
{
  const float DIVISOR = 2.0;

  this->mPos.x = crPos.x + (this->mSize.x / DIVISOR);
  this->mPos.y = crPos.y + (this->mSize.y / DIVISOR);
}

template<typename T>
void Box<T>::setSize(const T& crSize)
{
  this->mSize = abs(crSize);
}

template <typename T>
T Box<T>::getTopLeft()
{
  return calcTopLeft();
}

template <typename T>
void Box<T>::movePos(const T& crMoveVector)
{
  this->mPos += crMoveVector;
}

template <typename T>
bool Box<T>::inLocalBounds(const glm::ivec2& crPos)
{
  T topLeft = calcTopLeft();

  return (crPos.x > topLeft.x) && (crPos.x < (topLeft.x + this->mSize.x)) &&
         (crPos.y > topLeft.y) && (crPos.y < (topLeft.y + this->mSize.y));
}

template <typename T>
bool Box<T>::inLocalBounds(const glm::vec2& crPos)
{
  T topLeft = calcTopLeft();

  return (crPos.x > topLeft.x) && (crPos.x < (topLeft.x + this->mSize.x)) &&
         (crPos.y > topLeft.y) && (crPos.y < (topLeft.y + this->mSize.y));
}

template <typename T>
T Box<T>::calcTopLeft()
{
  const float DIVISOR = 2.0;

  return T(this->mPos.x - (this->mSize.x / DIVISOR), this->mPos.y - (this->mSize.y / DIVISOR));
}

#endif