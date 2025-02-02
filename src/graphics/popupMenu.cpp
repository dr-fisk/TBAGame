#include "graphics/popupMenu.hpp"

//! @brief Default Constructor
//!
//! @return PopupMenu Object
PopupMenu::PopupMenu()
{
  mBounds.left = 0;
  mBounds.top = 0;
  mBounds.width = 0;
  mBounds.height = 0;
  mPreferredSize = {0, 0};
  cmpInvoker = nullptr;
  mActiveSubMenu = nullptr;
}

//! @brief Adds a menu item to the Popup Menu
//!        Note: Popup Menu keeps a shared pointer so it is not necessary to keep the menu item in scope
//!
//! @param[in] cpMenuItem Menu Item to add to the Popup Menu
//!
//! @return None
void PopupMenu::addItem(const std::shared_ptr<MenuItem> cpMenuItem)
{
  // default to left most position, later add center and right
  mComponents.push_back(cpMenuItem);

  cpMenuItem->setPos({mBounds.left + (cpMenuItem->getSize().x / 2.0f), 
                      mBounds.top + mBounds.height + (cpMenuItem->getSize().y / 2.0f)});

  std::shared_ptr<PopupMenu> popupMenu = cpMenuItem->getPopupMenu();

  if(popupMenu)
  {
    popupMenu->addPopupMenuListerner(this);
  }

  mBounds.height += cpMenuItem->getSize().y;
}

//! @brief Updates the position of the menu items in the PopupMenu
//!
//! @return None
void PopupMenu::updatePopupMenuItemPositions()
{ 
  mBounds.height = 0;
  mBounds.width = mModifier.getScale().x;
  mBounds.left = mModifier.getPos().x;
  mBounds.top = mModifier.getPos().y;
  std::shared_ptr<PopupMenu> popupMenu;

  for(auto& item : mComponents)
  {
    if(mPreferredSize != glm::vec2{0, 0})
    {
      item->resize(mPreferredSize);
      mBounds.width = mPreferredSize.x;
    }

    item->setPos({mBounds.left + (item->getSize().x / 2.0f),
                  mBounds.top + mBounds.height + (item->getSize().y / 2.0f)});

    popupMenu = item->getPopupMenu();

    if(popupMenu)
    {
      popupMenu->setMenuLocation({item->getPos().x + (item->getSize().x / 2.0f),
          item->getPos().y - (item->getSize().y / 2.0)});
    }

    mBounds.height += item->getSize().y;
  }
}

//! @brief Draws the Popup Menu if it is visible
//!
//! @return None
void PopupMenu::draw()
{
  if(mUpdateUI)
  {
    updateUI();
  }

  if(mVisible)
  {
    for(auto& item : mComponents)
    {
      item->draw();
    }
  }
}

//! @brief Sets the preferred size of all Popup Menu Items
//!
//! @param[in] cWidth  Width to set Menu Items
//! @param[in] cHeight Height to set Menu Items
//!
//! @return Popup Menu reference to chain calls
PopupMenu& PopupMenu::setPreferredSize(const float cWidth, const float cHeight)
{
  mPreferredSize = {cWidth, cHeight};
  mUpdateUI = true;
  return *this;
}

//! @brief Handles incoming events
//!
//! @param[in] crEvent Event to handle
//!
//! @return None 
void PopupMenu::handleEvent(const Event& crEvent)
{
  for(auto& item : mComponents)
  {
    item->handleEvent(crEvent);

    if(item->wasClicked())
    {
      // If item is a Menu
      if(item->getPopupMenu())
      {
        mActiveSubMenu = item->getPopupMenu().get();
        mActiveSubMenu->setVisible(true);
      }
      else
      {
        notifyCancelled();
        mVisible = false;
        if(mActiveSubMenu)
        {
          mActiveSubMenu->setVisible(false);
          mActiveSubMenu = nullptr;
        }
        std::cout << item->getString() << std::endl;
      }
    }
    else if(item->isHover())
    {
      if(mActiveSubMenu)
      {
        mActiveSubMenu->setVisible(false);
        mActiveSubMenu = nullptr;
      }

      if(item->getPopupMenu())
      {
        mActiveSubMenu = item->getPopupMenu().get();
        mActiveSubMenu->setVisible(true);
      }
    }
    
  }

  // Check if mouse was pressed out of bounds to close popup menu
  if(Event::EventType::MouseButtonPress == crEvent.Type && GLFW_MOUSE_BUTTON_LEFT == crEvent.MouseButton.Button)
  {
    checkMousePressOutOfBounds(crEvent);
  }
}

//! @brief Checks if mouse press was out of bounds to close Popup Menu
//!
//! @param[in] crEvent Mouse Press Event
//!
//! @return None 
void PopupMenu::checkMousePressOutOfBounds(const Event& crEvent)
{
  if(!mBounds.contains(crEvent.MouseButton.x, crEvent.MouseButton.y) && !mActiveSubMenu)
  {
    notifyCancelled();
    mVisible = false;
  }
}

//! @brief Sets the Popup Menu location
//!
//! @param[in] crPos Position to set the Popup Menu
//!
//! @return None 
void PopupMenu::setMenuLocation(const glm::vec2& crPos)
{
  mModifier.setPos(crPos);
  mUpdateUI = true;
}

//! @brief Sets the Popup Menu invoker
//!
//! @param[in] cpInvoker The invoker of the Popup Menu
//!
//! @return None 
void PopupMenu::setInvoker(const AbstractButton* cpInvoker)
{
  cmpInvoker = cpInvoker;
}

//! @brief Adds a listener to this Popup Menu
//!
//! @param[in] cpListener Listener to add to Component
//!
//! @return None 
void PopupMenu::addPopupMenuListerner(PopupMenuListener<PopupMenu>* cpListener)
{
  mPopupMenuListeners.push_back(cpListener);
}

//! @brief Notifies listeners that the Popup Menu was cancelled
//!
//! @return None
void PopupMenu::notifyCancelled()
{
  for(auto& listener : mPopupMenuListeners)
  {
    listener->popupMenuCancelled(PopupMenuEvent(this));
  }
}

//! @brief Notifies the listeners that the Popup Menu will go invisible soon
//!
//! @return None
void PopupMenu::notifyInvisible()
{
  for(auto& listener : mPopupMenuListeners)
  {
    listener->popupMenuWillBecomeInvisible(PopupMenuEvent(this));
  }
}

//! @brief Notifies the listeners that the Popup Menu will be visible soon
//!
//! @return None
void PopupMenu::notifyVisible()
{
  for(auto& listener : mPopupMenuListeners)
  {
    listener->popupMenuWillBecomeVisible(PopupMenuEvent(this));
  }
}

//! @brief Handles the Component Popup Menu cancelled event
//!
//! @param[in] crEvent Popup Menu Event
//!
//! @return None
void PopupMenu::popupMenuCancelled(const PopupMenuEvent<PopupMenu>& crEvent)
{
  mVisible = false;

  if(mActiveSubMenu)
  {
    mActiveSubMenu->setVisible(false);
    mActiveSubMenu = nullptr;
  }

  notifyCancelled();
}

//! @brief Handles the Component Popup Menu becoming invisible event
//!
//! @param[in] crEvent Popup Menu Event
//!
//! @return None
void PopupMenu::popupMenuWillBecomeInvisible(const PopupMenuEvent<PopupMenu>& crEvent)
{
}

//! @brief Handles the Component Popup Menu visible event
//!
//! @param[in] crEvent Popup Menu Event
//!
//! @return None
void PopupMenu::popupMenuWillBecomeVisible(const PopupMenuEvent<PopupMenu>& crEvent)
{
}

//! @brief Sets the component to be visible or not and notifies listeners
//!
//! @param cVisible Controls visibility of component
//!
//! @return None
void PopupMenu::setVisible(const bool cVisible)
{
  mVisible = cVisible;

  if(cVisible)
  {
    notifyVisible();
  }
  else
  {
    notifyInvisible();
  }
}

//! @brief Gets the Menu Item list
//!
//! @return Menu Items
std::vector<std::shared_ptr<MenuItem>> PopupMenu::getMenuItems() const
{
  return mComponents;
}

void PopupMenu::updateUI()
{
  updatePopupMenuItemPositions();
  mUpdateUI = false;
}