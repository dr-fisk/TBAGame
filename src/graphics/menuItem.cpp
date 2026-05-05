#include "graphics/menuItem.hpp"

std::vector<std::shared_ptr<MenuItem>> MenuItem::getMenuItems() const
{
  return std::vector<std::shared_ptr<MenuItem>>();
}

void MenuItem::buttonClicked()
{
  mState = ButtonState::DEFAULT_STATE;
}