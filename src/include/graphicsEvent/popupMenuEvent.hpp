#ifndef POPUP_MENU_EVENT_HPP
#define POPUP_MENU_EVENT_HPP

#include "graphics/component.hpp"

class PopupMenuEvent
{
  public:
    PopupMenuEvent() = delete;
    PopupMenuEvent(Component* cpSource);
    ~PopupMenuEvent() = default;

    Component* mpSource;
};

#endif