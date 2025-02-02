#include "graphics/modifier.hpp"

Modifier& Modifier::setBackGroundColor(const lg::Color& crColor)
{
  mBackgroundColor = crColor;
  return *this;
}

Modifier& Modifier::setVerticalAlign(const VerticalAlign cAlign)
{
  mVerticalAlign = cAlign;
  return *this;
}

Modifier& Modifier::setHorizontalAlign(const HorizontalAlign cAlign)
{
  mHorizontalAlign = cAlign;
  return *this;
}

Modifier& Modifier::setWidth(const float cWidth)
{
  mTransform.setWidth(cWidth);
  return *this;
}

Modifier& Modifier::setHeight(const float cHeight)
{
  mTransform.setHeight(cHeight);
  return *this;
}

Modifier& Modifier::setLeft(const float cLeft)
{
  mTransform.setLeft(cLeft);
  return *this;
}

Modifier& Modifier::setTop(const float cTop)
{
  mTransform.setTop(cTop);
  return *this;
}

Modifier& Modifier::setPos(const glm::vec2& crPos)
{
  mTransform.setPos(crPos);
  return *this;
}

Modifier& Modifier::setScale(const glm::vec2& crScale)
{
  mTransform.setScale(crScale);
  return *this;
}

Modifier& Modifier::setRotation(const float cRotation)
{
  mTransform.setRotation(cRotation);
  return *this;
}

Modifier& Modifier::moveTransform(const glm::vec2& crMove)
{
  mTransform += crMove;
  return *this;
}

const lg::Color& Modifier::getBackGroundColor()
{
  return mBackgroundColor;
}

VerticalAlign Modifier::getVerticalAlign()
{
  return mVerticalAlign;
}

HorizontalAlign Modifier::getHorizontalAlign()
{
  return mHorizontalAlign;
}

float Modifier::getWidth() const
{
  return mTransform.getScale().x;
}

float Modifier::getHeight() const
{
  return mTransform.getScale().y;
}

float Modifier::getLeft() const
{
  return mTransform.getPos().x;
}

float Modifier::getTop() const
{
  return mTransform.getPos().y;
}

float Modifier::getRotation() const
{
  return mTransform.getRotation();
}

glm::vec2 Modifier::getPos() const
{
  return mTransform.getPos();
}

glm::vec2 Modifier::getScale() const
{
  return mTransform.getScale();
}

Transform Modifier::getTransform() const
{
  return mTransform;
}