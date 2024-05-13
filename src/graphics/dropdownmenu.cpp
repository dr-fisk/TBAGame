#include "graphics/dropDownMenu.hpp"

DropdownMenu::DropdownMenu()
{
  // initial bounds should be set to pos + size/2 as button pos is tracked from it's center
  mDefaultMenuLocation = true;
  mDropDownState = MENU_LIST_HIDE;
  mTopLevel = false;
  mpPopupMenu = std::make_shared<PopupMenu>();
  mpPopupMenu->setInvoker(this);
  mpPopupMenu->setVisible(false);
  mpPopupMenu->addPopupMenuListerner(this);
}

void DropdownMenu::performAction(const ActionEvent& crEvent)
{
  if(this == crEvent.mpSource)
  {
    std::cout << "Clicked " << getString() << std::endl;
    if(!mTopLevel)
    {
      return;
    }

    switch(mDropDownState)
    {
      case MENU_LIST_SHOW:
        mDropDownState = MENU_LIST_HIDE;
        notifyMenuDeselected();
        break;
      case MENU_LIST_HIDE:
        mDropDownState = MENU_LIST_SHOW;
        notifyMenuSelected();
        break;
      default:
        break;
    }
  }
}

void DropdownMenu::addMenuItem(const std::shared_ptr<MenuItem> cpMenuItem)
{
  // If MenuItem does not have popup menu then it is a regular menu item
  mpPopupMenu->addItem(cpMenuItem);
  // cpMenuItem->addActionListener(this);
  mMenuItemList.push_back(cpMenuItem);
}

// void DropdownMenu::addMenuItem(const std::shared_ptr<DropdownMenu> cpMenu)
// {
//   mpPopupMenu->addItem(cpMenu);
//   cpMenu->addMenuListener(this);
//   addMenuListener(cpMenu.get());
//   mMenuItemList.push_back(cpMenu);
// }

void DropdownMenu::draw()
{
  if(mUpdateUI)
  {
    // updateListBounds();
    mpPopupMenu->setPreferredSize(mTransform.getScale().x, mTransform.getScale().y);
    if(!isTopLevel())
    {
      mpPopupMenu->setPos({mTransform.getPos().x + (mTransform.getScale().x / 2.0f),
                        mTransform.getPos().y - (mTransform.getScale().y / 2.0f)});
    }
    else
    {
      mpPopupMenu->setPos({mTransform.getPos().x - (mTransform.getScale().x / 2.0f),
                        mTransform.getPos().y + (mTransform.getScale().y / 2.0f)});
    }
    mUpdateUI = false;
  }

  mLabel.draw();
  mpPopupMenu->draw();
}

void DropdownMenu::handleEvent(const Event& crEvent)
{
  if(!mEnabled)
  {
    return;
  }

  AbstractButton::handleEvent(crEvent);

  switch(mDropDownState)
  {
    case MENU_LIST_HIDE:
      if(!mTopLevel && isHover())
      {
        mDropDownState = MENU_LIST_SHOW;
        mpPopupMenu->setVisible(true);
      }
      break;
    case MENU_LIST_SHOW:
      if(!isPressed() || wasClicked())
      {
        mpPopupMenu->handleEvent(crEvent);
      }
      break;
    default:
      break;
  }
}

DropdownMenu& DropdownMenu::setMenuLocation(const glm::vec2& crPos)
{
  mpPopupMenu->setMenuLocation(crPos);
  return *this;
}

DropdownMenu& DropdownMenu::addMenuListener(MenuListener* pListener)
{
  mMenuListeners.push_back(pListener);
  return *this;
}

void DropdownMenu::removeMenuListener(const MenuListener* cpListener)
{
  for(auto itr = mMenuListeners.begin(); itr != mMenuListeners.end(); itr++)
  {
    if(*itr == cpListener)
    {
      mMenuListeners.erase(itr);
      break;
    }
  }
}

void DropdownMenu::notifyMenuSelected()
{
  for(const auto& menuListener : mMenuListeners)
  {
    menuListener->menuSelected(MenuEvent(this));
  }
}

void DropdownMenu::notifyMenuDeselected()
{
  for(const auto& menuListener : mMenuListeners)
  {
    menuListener->menuDeselected(MenuEvent(this));
  }
}

void DropdownMenu::notifyMenuCancelled()
{
  for(const auto& menuListener : mMenuListeners)
  {
    menuListener->menuCancelled(MenuEvent(this));
  }
}

void DropdownMenu::menuDeselected(const MenuEvent& crEvent)
{
}

void DropdownMenu::menuSelected(const MenuEvent& crEvent)
{
}

void DropdownMenu::menuCancelled(const MenuEvent& crEvent)
{
  mDropDownState = MENU_LIST_HIDE;
}

void DropdownMenu::setIsTopLevel(const bool cTop)
{
  mTopLevel = cTop;
}

bool DropdownMenu::isTopLevel() const
{
  return mTopLevel;
}

std::shared_ptr<PopupMenu> DropdownMenu::getPopupMenu() const
{
  return mpPopupMenu;
}

void DropdownMenu::popupMenuCancelled(const PopupMenuEvent& crEvent)
{
  mDropDownState = MENU_LIST_HIDE;
}

void DropdownMenu::popupMenuWillBecomeInvisible(const PopupMenuEvent& crEvent)
{
  mDropDownState = MENU_LIST_HIDE;
}

void DropdownMenu::popupMenuWillBecomeVisible(const PopupMenuEvent& crEvent)
{
  mDropDownState = MENU_LIST_SHOW;
}

bool DropdownMenu::isPopupMenuVisible() const
{
  return mpPopupMenu->isVisible();
}