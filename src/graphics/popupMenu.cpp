#include "graphics/popupMenu.hpp"
#include "event/lestRenderEngineEventManager.hpp"

PopupMenu::PopupMenu()
{
  mBounds.left = 0;
  mBounds.top = 0;
  mBounds.width = 0;
  mBounds.height = 0;
  mPreferredSize = {0, 0};
  mActiveSubMenu = nullptr;
  mButtonEventSub.setCallback(BIND_EVENT_FN(PopupMenu::onButtonEvent));
  mPopupEventSub.setCallback(BIND_EVENT_FN(PopupMenu::onPopupMenuEvent));
  mUpdateUI = true;
}

void PopupMenu::addItem(const std::shared_ptr<MenuItem> cpMenuItem)
{
  // default to left most position, later add center and right
  mItems.push_back(cpMenuItem);

  cpMenuItem->setPos({mBounds.left + (cpMenuItem->getSize().x / 2.0f), 
                      mBounds.top + mBounds.height + (cpMenuItem->getSize().y / 2.0f)});

  std::shared_ptr<PopupMenu> popupMenu = cpMenuItem->getPopupMenu();

  if(popupMenu)
  {
    popupMenu->addPopupMenuListener(mPopupEventSub);
  }
  else
  {
    cpMenuItem->addButtonEventListener(mButtonEventSub);
  }

  mBounds.height += cpMenuItem->getSize().y;
  mUpdateUI = true;
}

PopupMenu& PopupMenu::addPopupMenuListener(EventSubscriber<PopupMenuEvent>& rListener)
{
  mDispatcher.registerToEvent(rListener);
  return *this;
}

void PopupMenu::updatePopupMenuItemPositions()
{ 
  mBounds.height = 0;
  mBounds.width = mModifier.getScale().x;
  mBounds.left = mModifier.getPos().x;
  mBounds.top = mModifier.getPos().y;
  std::shared_ptr<PopupMenu> popupMenu;

  for(auto& item : mItems)
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

void PopupMenu::draw()
{
  if(mUpdateUI)
  {
    updateUI();
  }

  if(mVisible)
  {
    for(auto& item : mItems)
    {
      item->draw();
    }
  }
}

PopupMenu& PopupMenu::setPreferredSize(const float cWidth, const float cHeight)
{
  mPreferredSize = {cWidth, cHeight};
  mUpdateUI = true;
  return *this;
}

void PopupMenu::setMenuLocation(const glm::vec2& crPos)
{
  mModifier.setPos(crPos);
  mUpdateUI = true;
}

void PopupMenu::notifyCancelled()
{
  PopupMenuEvent event(this, MenuEvent::MENU_CANCELLED);
  mDispatcher.notify(event);
}

//! @brief Notifies the listeners that the Popup Menu will go invisible soon
//!
//! @return None
// void PopupMenu::notifyInvisible()
// {
//   for(auto& listener : mPopupMenuListeners)
//   {
//     listener->popupMenuWillBecomeInvisible(PopupMenuEvent(this));
//   }
// }

void PopupMenu::notifyVisible()
{
  PopupMenuEvent event(this, MenuEvent::MENU_SELECTED);
  mDispatcher.notify(event);
}

void PopupMenu::onButtonEvent(AbstractButton::ButtonEvent& rButtonEvent)
{
  switch(rButtonEvent.mAction)
  {
    case GuiEvent::GUI_CLICK:
      notifyCancelled();

      if(mActiveSubMenu)
      {
        mActiveSubMenu->setVisible(false);
        mActiveSubMenu = nullptr;
      }

      std::cout << rButtonEvent.mpSource->getString() << std::endl;
      break;
    case GuiEvent::GUI_HOVER:
      if(mActiveSubMenu)
      {
        mActiveSubMenu->setVisible(false);
        mActiveSubMenu = nullptr;
      }
      break;
  }
}

void PopupMenu::onPopupMenuEvent(PopupMenuEvent& rPopupMenuEvent)
{
  switch(rPopupMenuEvent.mAction)
  {
    case MenuEvent::MENU_CANCELLED:
      if(mActiveSubMenu && *mActiveSubMenu == *rPopupMenuEvent.mpSource)
      {
        mActiveSubMenu = nullptr;
      }
      break;
    case MenuEvent::MENU_SELECTED:
      if(mActiveSubMenu && !(*mActiveSubMenu == *rPopupMenuEvent.mpSource))
      {
        mActiveSubMenu->setVisible(false);
      }
      mActiveSubMenu = rPopupMenuEvent.mpSource;
      break;
  }
}

void PopupMenu::setVisible(const bool cVisible)
{
  if(mVisible == cVisible)
  {
    return;
  }

  mVisible = cVisible;

  if(cVisible)
  {
    mEnabled = true;
    notifyVisible();
  }
  else
  {
    mEnabled = false;
    notifyCancelled();

    if(mActiveSubMenu)
    {
      mActiveSubMenu->setVisible(false);
      mActiveSubMenu = nullptr;
    }
  }

  mUpdateUI = true;
}

std::vector<std::shared_ptr<MenuItem>> PopupMenu::getMenuItems() const
{
  return mItems;
}

void PopupMenu::updateUI()
{
  updatePopupMenuItemPositions();

  if(mUpdateUI)
  {
    for(auto& item : mItems)
    {
      item->setEnabled(mEnabled);
    }
  }

  mUpdateUI = false;
}

void PopupMenu::dispatchEvent(I_Event<lre::LestRenderEngineEvents>& rEvent)
{
  if(!mVisible)
  {
    return;
  }

  //! Below items will call callback functions that the popupmenu will handle
  for(auto& item : mItems)
  {
    item->dispatchEvent(rEvent);
  }

  if(!mActiveSubMenu && lre::LestRenderEngineEvents::MOUSE_BUTTON_PRESS == rEvent.GetEventType())
  {
    lre::MouseButtonPressEvent& event = static_cast<lre::MouseButtonPressEvent&>(rEvent);

    if(!mBounds.contains(event.getX(), event.getY()))
    {
      notifyCancelled();
    }
  }
}