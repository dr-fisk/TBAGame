#include "graphics/menuItem.hpp"

MenuItem::MenuItem()
{
}

std::vector<std::shared_ptr<MenuItem>> MenuItem::getMenuItems() const
{
  return mMenuItemList;
}

void MenuItem::performAction(const ActionEvent& crEvent)
{
  mState = DEFAULT_STATE;
}