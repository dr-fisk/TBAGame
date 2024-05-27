#ifndef POPUP_MENU_LISTENER_HPP
#define POPUP_MENU_LISTENER_HPP

#include "event/eventListener.hpp"
#include "graphicsEvent/popupMenuEvent.hpp"

template <typename T>
class PopupMenuListener : public EventListener
{
  public:
    PopupMenuListener() = default;
    ~PopupMenuListener() = default;

    virtual void popupMenuCancelled(const PopupMenuEvent<T>& crEvent) = 0;
    virtual void popupMenuWillBecomeInvisible(const PopupMenuEvent<T>& crEvent) = 0;
    virtual void popupMenuWillBecomeVisible(const PopupMenuEvent<T>& crEvent) = 0;
};

#endif