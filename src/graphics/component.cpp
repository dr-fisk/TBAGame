#include "graphics/component.hpp"

Component& Component::movePos(const glm::vec2& crMove)
{
  mTransform += crMove;
  return *this;
}

Component& Component::setPos(const glm::vec2& crPos)
{
  mTransform.setPos(crPos);
  
  if(mExtraUpdate)
  {
    mExtraUpdate();
  }

  return *this;
}

Component& Component::resize(const glm::vec2& crSize)
{
  mTransform.setScale(crSize);
  if(mExtraUpdate)
  {
    mExtraUpdate();
  }

  return *this;
}

Component& Component::setPadding(const glm::vec2& crPadding)
{
  mPadding = crPadding;
  if(mExtraUpdate)
  {
    mExtraUpdate();
  }
  
  return *this;
}
