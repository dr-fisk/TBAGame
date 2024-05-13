#include "graphics/component.hpp"
#include "graphics/popupMenu.hpp"

Component::Component()
{
  mVisible = true;
  mUpdateUI = true;
  mEnabled = true;
}

Component& Component::movePos(const glm::vec2& crMove)
{
  mTransform += crMove;
  mUpdateUI = true;
  return *this;
}

Component& Component::setPos(const glm::vec2& crPos)
{
  mTransform.setPos(crPos);
  mUpdateUI = true;

  return *this;
}

Component& Component::resize(const glm::vec2& crSize)
{
  mTransform.setScale(crSize);
  mUpdateUI = true;

  return *this;
}

Component& Component::setPadding(const glm::vec2& crPadding)
{
  mPadding = crPadding;
  mUpdateUI = true;
  
  return *this;
}

void Component::setVisible(const bool cVisible)
{
  mVisible = cVisible;
}

bool Component::isVisible() const
{
  return mVisible;
}

void Component::setEnabled(const bool cEnable)
{
  mEnabled = cEnable;
}

bool Component::isEnabled() const
{
  return mEnabled;
}

std::shared_ptr<PopupMenu> Component::getPopupMenu() const
{
  return nullptr;
}