#ifndef RECT_HPP
#define RECT_HPP

#include <optional>

template <typename T>
class Rect
{
  public:
    Rect();
    ~Rect() = default;
    Rect(const T cLeft, const T cTop, const T cWidth, const T cHeight);
    Rect(const Rect<T>& crRect);
    Rect& setPos(const T cLeft, const T cTop);
    Rect& setSize(const T cWidth, const T cHeight);
    void getCenter(T& rX, T& rY) const;
    void movePos(const T cX, const T cY);
    bool contains(const T cX, const T cY) const;
    bool contains(const Rect<T>& crBox) const;
    std::optional<Rect<T>> getBoundingBox(const Rect<T>& crBox) const;
    bool operator==(const Rect<T>& crBox) const;
    Rect& operator=(const Rect<T>& crBox);

    T left;
    T top;
    T width;
    T height;
};

template <typename T>
Rect<T>::Rect()
{
  left = 0;
  top = 0;
  width = 1;
  height = 1;
}

template <typename T>
Rect<T>::Rect(const T cLeft, const T cTop, const T cWidth, const T cHeight)
{
  left = cLeft;
  top = cTop;
  width = cWidth;
  height = cHeight;
}

template <typename T>
Rect<T>& Rect<T>::setPos(const T cLeft, const T cTop)
{
  left = cLeft;
  top = cTop;
  return *this;
}

template <typename T>
Rect<T>& Rect<T>::setSize(const T cWidth, const T cHeight)
{
  width = cWidth;
  height = cHeight;
  return *this;
}

template <typename T>
void Rect<T>::getCenter(T& rX, T& rY) const
{
  rX = left - width / 2.0f;
  rY = top - height / 2.0f;
}

template <typename T>
void Rect<T>::movePos(const T cX, const T cY)
{
  left += cX;
  top += cY;
}

template <typename T>
bool Rect<T>::contains(const T cX, const T cY) const
{
  return (left < cX) && (left + width > cX) && (top < cY) && (top + height > cY);
}

template <typename T>
bool Rect<T>::contains(const Rect<T>& crBox) const
{
  return (left < crBox.left + crBox.width) && (left + width > crBox.left)
    && (top < crBox.top + crBox.height) && (top + height > crBox.top);
}

template <typename T>
std::optional<Rect<T>> Rect<T>::getBoundingBox(const Rect<T>& crBox) const
{
  if(!contains(crBox))
  {
    return {};
  }

  Rect<T> box;

  if(left < crBox.left)
  {
    box.width = (crBox.left + crBox.width) - (left + width);
    box.x = crBox.left;
  }
  else
  {
    box.width = (left + width) - (crBox.left + crBox.width);
    box.x = left;
  }

  if(top < crBox.top)
  {
    box.height = (crBox.top + crBox.height) - (top + height);
    box.top = crBox.top;
  }
  else
  {
    box.height = (top + height) - (crBox.top + crBox.height);
    box.top = left;
  }

  return box;
}

template <typename T>
bool Rect<T>::operator==(const Rect<T>& crBox) const
{
  return (left == crBox.left) && (top == crBox.top) && (width == crBox.width) && (height == crBox.height);
}

template <typename T>
Rect<T>& Rect<T>::operator=(const Rect<T>& crBox)
{
  if(this == &crBox)
  {
    return *this;
  }

  left = crBox.left;
  top = crBox.top;
  width = crBox.width;
  height = crBox.height;
  return *this;
}

template <typename T>
Rect<T>::Rect(const Rect<T>& crRect)
{
  *this = crRect;
}

#endif