#include "graphics/popupMenu.hpp"
#include "graphics/dropDownMenu.hpp"

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

std::shared_ptr<PopupMenu> popupMenu;

void PopupMenu::updateListPositions()
{ 
  mBounds.height = 0;
  mBounds.width = mTransform.getScale().x;
  mBounds.left = mTransform.getPos().x;
  mBounds.top = mTransform.getPos().y;

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

void PopupMenu::draw()
{
  if(mUpdateUI)
  {
    updateListPositions();
    mUpdateUI = false;
  }

  if(mVisible)
  {
    for(auto& item : mComponents)
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

void PopupMenu::checkMousePressOutOfBounds(const Event& crEvent)
{
  if(!mBounds.contains(crEvent.MouseButton.x, crEvent.MouseButton.y) && !mActiveSubMenu)
  {
    notifyCancelled();
    mVisible = false;
  }
}

void PopupMenu::setMenuLocation(const glm::vec2& crPos)
{
  mTransform.setPos(crPos);
  mUpdateUI = true;
}

void PopupMenu::setInvoker(const AbstractButton* cpInvoker)
{
  cmpInvoker = cpInvoker;
}

void PopupMenu::addPopupMenuListerner(PopupMenuListener* cpListener)
{
  mPopupMenuListeners.push_back(cpListener);
}

void PopupMenu::notifyCancelled()
{
  for(auto& listener : mPopupMenuListeners)
  {
    listener->popupMenuCancelled(PopupMenuEvent(this));
  }
}

void PopupMenu::notifyInvisible()
{
  for(auto& listener : mPopupMenuListeners)
  {
    listener->popupMenuWillBecomeInvisible(PopupMenuEvent(this));
  }
}

void PopupMenu::notifyVisible()
{
  for(auto& listener : mPopupMenuListeners)
  {
    listener->popupMenuWillBecomeVisible(PopupMenuEvent(this));
  }
}

void PopupMenu::popupMenuCancelled(const PopupMenuEvent& crEvent)
{
  mVisible = false;

  if(mActiveSubMenu)
  {
    mActiveSubMenu->setVisible(false);
    mActiveSubMenu = nullptr;
  }

  notifyCancelled();
}

void PopupMenu::popupMenuWillBecomeInvisible(const PopupMenuEvent& crEvent)
{
}

void PopupMenu::popupMenuWillBecomeVisible(const PopupMenuEvent& crEvent)
{
}

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