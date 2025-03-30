#include "graphics/menu.hpp"

Menu::Menu()
{
  // initial bounds should be set to pos + size/2 as button pos is tracked from it's center
  mDefaultMenuLocation = true;
  mDropDownState = MENU_LIST_HIDE;
  mTopLevel = false;
  mpPopupMenu = std::make_shared<PopupMenu>();
  mpPopupMenu->setVisible(false);
  mButtonEventSub.setCallback(BIND_EVENT_FN(Menu::onButtonEvent));
  mPopupMenuEventSub.setCallback(BIND_EVENT_FN(Menu::onPopupMenuEvent));
  mpPopupMenu->addPopupMenuListener(mPopupMenuEventSub);
  mDispatcher.attach(mButtonEventSub);
  mUpdateUI = true;
}

void Menu::buttonClicked()
{
  mState = ButtonState::HOVER_STATE;
  std::cout << "Clicked " << getString() << std::endl;
  if(!mTopLevel)
  {
    return;
  }

  switch(mDropDownState)
  {
    case MENU_LIST_SHOW:
      mDropDownState = MENU_LIST_HIDE;
      // notifyMenuDeselected();
      break;
    case MENU_LIST_HIDE:
      mDropDownState = MENU_LIST_SHOW;
      // notifyMenuSelected();
      break;
    default:
      break;
  }
}

void Menu::addMenuItem(const std::shared_ptr<MenuItem> cpMenuItem)
{
  mpPopupMenu->addItem(cpMenuItem);
}

void Menu::draw()
{
  if(mUpdateUI)
  {
    updateUI();
  }

  AbstractButton::draw();
  mpPopupMenu->draw();
}

Menu& Menu::setMenuLocation(const glm::vec2& crPos)
{
  mpPopupMenu->setMenuLocation(crPos);
  return *this;
}

//! @brief Adds a Menu Listener to listen for Menu events
//!
//! @param[in] pListener Listener to add to list
//!
//! @return None
// Menu& Menu::addMenuListener(MenuListener* pListener)
// {
//   mMenuListeners.push_back(pListener);
//   return *this;
// }

//! @brief Removes Menu Listner from the list
//!
//! @param[in] cpListener Listner to remove from the list
//!
//! @return None
// void Menu::removeMenuListener(const MenuListener* cpListener)
// {
//   for(auto itr = mMenuListeners.begin(); itr != mMenuListeners.end(); itr++)
//   {
//     if(*itr == cpListener)
//     {
//       mMenuListeners.erase(itr);
//       break;
//     }
//   }
// }

//! @brief Notifies listeners when Menu is selected
//!
//! @return None
// void Menu::notifyMenuSelected()
// {
//   for(const auto& menuListener : mMenuListeners)
//   {
//     menuListener->menuSelected(MenuEvent(this));
//   }
// }

//! @brief Notifies listeners when Menu is deselectedp
//!
//! @return None
// void Menu::notifyMenuDeselected()
// {
//   for(const auto& menuListener : mMenuListeners)
//   {
//     menuListener->menuDeselected(MenuEvent(this));
//   }
// }

//! @brief Notifies listeners when Menu is cancelled
//!
//! @return None
// void Menu::notifyMenuCancelled()
// {
//   for(const auto& menuListener : mMenuListeners)
//   {
//     menuListener->menuCancelled(MenuEvent(this));
//   }
// }

void Menu::setIsTopLevel(const bool cTop)
{
  mTopLevel = cTop;
}

bool Menu::isTopLevel() const
{
  return mTopLevel;
}

std::shared_ptr<PopupMenu> Menu::getPopupMenu() const
{
  return mpPopupMenu;
}

bool Menu::isPopupMenuVisible() const
{
  return mpPopupMenu->isVisible();
}

//! @brief Popup Menu Cancelled callback handler
//!
//! @param[in] crEvent Event to handle 
//!
//! @return None
// void Menu::popupMenuCancelled(const PopupMenuEvent<PopupMenu>& crEvent)
// {
//   mDropDownState = MENU_LIST_HIDE;
// }

//! @brief Popup Menu Will Become Invisible callback handler
//!
//! @param[in] crEvent Event to handle 
//!
//! @return None
// void Menu::popupMenuWillBecomeInvisible(const PopupMenuEvent<PopupMenu>& crEvent)
// {
//   mDropDownState = MENU_LIST_HIDE;
// }

//! @brief Popup Menu Will Become Visible callback handler
//!
//! @param[in] crEvent Event to handle 
//!
//! @return None
// void Menu::popupMenuWillBecomeVisible(const PopupMenuEvent<PopupMenu>& crEvent)
// {
//   mDropDownState = MENU_LIST_SHOW;
// }

std::vector<std::shared_ptr<MenuItem>> Menu::getMenuItems() const
{
  return mpPopupMenu->getMenuItems();
}

void Menu::updateUI()
{
  mpPopupMenu->setPreferredSize(mModifier.getScale().x, mModifier.getScale().y);
  if(!isTopLevel())
  {
    mpPopupMenu->setPos({mModifier.getPos().x + (mModifier.getScale().x / 2.0f),
                      mModifier.getPos().y - (mModifier.getScale().y / 2.0f)});
  }
  else
  {
    mpPopupMenu->setPos({mModifier.getPos().x - (mModifier.getScale().x / 2.0f),
                      mModifier.getPos().y + (mModifier.getScale().y / 2.0f)});
  }

  AbstractButton::updateUI();

  mUpdateUI = false;
}

void Menu::onButtonEvent(AbstractButton::ButtonEvent& rButtonEvent)
{
  switch(rButtonEvent.mAction)
  {
    case GuiEvent::GUI_HOVER:
    case GuiEvent::GUI_PRESS:
    case GuiEvent::GUI_CLICK:
      if(!mTopLevel)
      {
        mDropDownState = MENU_LIST_SHOW;
        mpPopupMenu->setVisible(true);
      }
      break;
  }
}

void Menu::onPopupMenuEvent(PopupMenu::PopupMenuEvent& rPopupMenuEvent)
{
  if(MenuEvent::MENU_CANCELLED == rPopupMenuEvent.mAction)
  {
    mpPopupMenu->setVisible(false);
  }
}

void Menu::dispatchEvent(I_Event<lre::LestRenderEngineEvents>& rEvent)
{
  mpPopupMenu->dispatchEvent(rEvent);

  if(mVisible)
  {
    processEvent(rEvent);
  }
}