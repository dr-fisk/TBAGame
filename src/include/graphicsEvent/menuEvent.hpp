#ifndef MENU_EVENT_HPP
#define MENU_EVENT_HPP

#include "graphics/component.hpp"

class MenuEvent
{
  public:
    MenuEvent() = delete;
    MenuEvent(Component* pSource);
    ~MenuEvent() = default;

    Component* mpSource;
};

#endif