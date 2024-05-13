#ifndef POPUP_MENU_LISTENER_HPP
#define POPUP_MENU_LISTENER_HPP

#include "event/eventListener.hpp"
#include "graphicsEvent/popupMenuEvent.hpp"

class PopupMenuListener : public EventListener
{
  public:
    PopupMenuListener() = default;
    ~PopupMenuListener() = default;

    virtual void popupMenuCancelled(const PopupMenuEvent& crEvent) = 0;
    virtual void popupMenuWillBecomeInvisible(const PopupMenuEvent& crEvent) = 0;
    virtual void popupMenuWillBecomeVisible(const PopupMenuEvent& crEvent) = 0;
};

#endif