#ifndef POPUP_MENU_EVENT_HPP
#define POPUP_MENU_EVENT_HPP

#include "graphics/component.hpp"

template <typename T>
class PopupMenuEvent
{
  public:
    PopupMenuEvent() = delete;
    PopupMenuEvent(T* cpSource);
    ~PopupMenuEvent() = default;

    T* mpSource;
};

#include "../../graphicsEvent/popupMenuEvent.cpp"

#endif