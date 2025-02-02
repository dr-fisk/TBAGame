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
  mModifier.moveTransform(crMove);
  mUpdateUI = true;
  return *this;
}

Component& Component::setPos(const glm::vec2& crPos)
{
  mModifier.setPos(crPos);
  mUpdateUI = true;

  return *this;
}

Component& Component::resize(const glm::vec2& crSize)
{
  mModifier.setScale(crSize);
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

Component& Component::setModifier(const Modifier& crModifier)
{
  mModifier = crModifier;
  mUpdateUI = true;
  return *this;
}

bool Component::isEnabled() const
{
  return mEnabled;
}

std::shared_ptr<PopupMenu> Component::getPopupMenu() const
{
  return nullptr;
}