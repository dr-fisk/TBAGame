#ifndef MENU_LISTENER_HPP
#define MENU_LISTENER_HPP

#include "graphicsEvent/componentEventListener.hpp"
#include "graphicsEvent/menuEvent.hpp"

class MenuListener : public ComponentEventListener
{
  public:
    MenuListener() = default;
    ~MenuListener() = default;
    virtual void menuCancelled(const MenuEvent& crEvent) = 0;
    virtual void menuSelected(const MenuEvent& crEvent) = 0;
    virtual void menuDeselected(const MenuEvent& crEvent) = 0;
};

#endif