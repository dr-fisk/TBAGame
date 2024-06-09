#ifndef POPUP_MENU_LISTENER_HPP
#define POPUP_MENU_LISTENER_HPP

#include "graphicsEvent/componentEventListener.hpp"
#include "graphicsEvent/popupMenuEvent.hpp"

template <typename T>
class PopupMenuListener : public ComponentEventListener
{
  public:
    PopupMenuListener() = default;
    ~PopupMenuListener() = default;

    virtual void popupMenuCancelled(const PopupMenuEvent<T>& crEvent) = 0;
    virtual void popupMenuWillBecomeInvisible(const PopupMenuEvent<T>& crEvent) = 0;
    virtual void popupMenuWillBecomeVisible(const PopupMenuEvent<T>& crEvent) = 0;
};

#endif