#define GLM_FORCE_CTOR_INIT
#include "utility/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

glm::vec2 Transform::getPos() const
{
  return mPosition;
}

glm::vec2 Transform::getScale() const
{
  return mScale;
}

float Transform::getRotation() const
{
  return mRotation;
}

Transform& Transform::setRotation(const float cRotation)
{
  mRotation = cRotation;
  return *this;
}

Transform& Transform::setPos(const glm::vec2& crPos)
{
  mPosition = crPos;
  return *this;
}

Transform& Transform::setScale(const glm::vec2& crScale)
{
  mScale = crScale;
  return *this;
}

Transform& Transform::setLeft(const float cLeft)
{
  mPosition.x = cLeft;
  return *this;
}

Transform& Transform::setTop(const float cTop)
{
  
  mPosition.y = cTop;
  return *this;
}

Transform& Transform::setWidth(const float cWidth)
{
  mScale.x = cWidth;
  return *this;
}

Transform& Transform::setHeight(const float cHeight)
{
  mScale.y = cHeight;
  return *this;
}

glm::mat4 Transform::translate(const glm::vec2& crOffset) const
{
  return glm::translate(glm::mat4(1.0f), glm::vec3(mPosition - crOffset, 0.0f));
}

void Transform::operator+=(const glm::vec2& rVec2)
{
  mPosition += rVec2;
}