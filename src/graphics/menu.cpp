#include "graphics/menu.hpp"

//! @brief Default Constructor
//!
//! @return None
Menu::Menu()
{
  // initial bounds should be set to pos + size/2 as button pos is tracked from it's center
  mDefaultMenuLocation = true;
  mDropDownState = MENU_LIST_HIDE;
  mTopLevel = false;
  mpPopupMenu = std::make_shared<PopupMenu>();
  mpPopupMenu->setInvoker(this);
  mpPopupMenu->setVisible(false);
}

//! @brief Performs Menu Specific action upon being clicked
//!
//! @param[in] crEvent Action Event
//!
//! @return None
void Menu::buttonClicked()
{
  mState = HOVER_STATE;
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

//! @brief Adds a Menu Item to the Popup Menu
//!
//! @param[in] cpMenuItem Menu Item to be added
//!
//! @return None 
void Menu::addMenuItem(const std::shared_ptr<MenuItem> cpMenuItem)
{
  mpPopupMenu->addItem(cpMenuItem);
}

//! @brief Draws the Menu
//!
//! @return None
void Menu::draw()
{
  if(mUpdateUI)
  {
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

//! @brief Handles the incoming Event
//!
//! @param[in] crEvent Event to be handled
//!
//! @return None
void Menu::handleEvent(const Event& crEvent)
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
      // Handle events if Menu is not pressed
      if(!isPressed())
      {
        mpPopupMenu->handleEvent(crEvent);

        // Change state to MENU_LIST_HIDE since Popup Menu is hidden
        if(!mpPopupMenu->isVisible())
        {
          mDropDownState = MENU_LIST_HIDE;
        }
      }

      break;
    default:
      break;
  }
}

//! @brief Sets the Popup Menu location TopLeft pos
//!
//! @param[in] crPos Position to set Popup Menu
//!
//! @return Menu reference to chain calls
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
Menu& Menu::addMenuListener(MenuListener* pListener)
{
  mMenuListeners.push_back(pListener);
  return *this;
}

//! @brief Removes Menu Listner from the list
//!
//! @param[in] cpListener Listner to remove from the list
//!
//! @return None
void Menu::removeMenuListener(const MenuListener* cpListener)
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

//! @brief Notifies listeners when Menu is selected
//!
//! @return None
void Menu::notifyMenuSelected()
{
  for(const auto& menuListener : mMenuListeners)
  {
    menuListener->menuSelected(MenuEvent(this));
  }
}

//! @brief Notifies listeners when Menu is deselected
//!
//! @return None
void Menu::notifyMenuDeselected()
{
  for(const auto& menuListener : mMenuListeners)
  {
    menuListener->menuDeselected(MenuEvent(this));
  }
}

//! @brief Notifies listeners when Menu is cancelled
//!
//! @return None
void Menu::notifyMenuCancelled()
{
  for(const auto& menuListener : mMenuListeners)
  {
    menuListener->menuCancelled(MenuEvent(this));
  }
}

//! @brief Sets whether this is a top level menu
//! TODO: find a better way to do this
//!
//! @return None
void Menu::setIsTopLevel(const bool cTop)
{
  mTopLevel = cTop;
}

//! @brief Returns if this Menu is Top Level
//!
//! @return true if is Top Level, false otherwise
bool Menu::isTopLevel() const
{
  return mTopLevel;
}

//! @brief Returns the Popup Menu assign to this Menu
//!
//! @return Popup Menu pointer 
std::shared_ptr<PopupMenu> Menu::getPopupMenu() const
{
  return mpPopupMenu;
}

//! @brief Gets whether the Popup Menu is visible
//!
//! @return true if Popup Menu is visible, false otherwise 
bool Menu::isPopupMenuVisible() const
{
  return mpPopupMenu->isVisible();
}

//! @brief Popup Menu Cancelled callback handler
//!
//! @param[in] crEvent Event to handle 
//!
//! @return None
void Menu::popupMenuCancelled(const PopupMenuEvent<PopupMenu>& crEvent)
{
  mDropDownState = MENU_LIST_HIDE;
}

//! @brief Popup Menu Will Become Invisible callback handler
//!
//! @param[in] crEvent Event to handle 
//!
//! @return None
void Menu::popupMenuWillBecomeInvisible(const PopupMenuEvent<PopupMenu>& crEvent)
{
  mDropDownState = MENU_LIST_HIDE;
}

//! @brief Popup Menu Will Become Visible callback handler
//!
//! @param[in] crEvent Event to handle 
//!
//! @return None
void Menu::popupMenuWillBecomeVisible(const PopupMenuEvent<PopupMenu>& crEvent)
{
  mDropDownState = MENU_LIST_SHOW;
}

//! @brief Gets the Menu Item list
//!
//! @return Menu Items
std::vector<std::shared_ptr<MenuItem>> Menu::getMenuItems() const
{
  return mpPopupMenu->getMenuItems();
}