#ifndef MENU_ACTION_EVENT_HPP
#define MENU_ACTION_EVENT_HPP

#include "event/I_Event.hpp"

enum class MenuEvent
{
  MENU_SELECTED,
  MENU_HIDE,
  MENU_CANCELLED
};

template <typename T>
class MenuActionEvent : public I_Event<std::string>
{
  public:
    //! @brief Delete Default Constructor
    MenuActionEvent() = delete;

    //! @brief Default Destructor
    ~MenuActionEvent() = default;

    MenuActionEvent(T* pSource, const MenuEvent cAction) : I_Event("MENUACTION"), mpSource(pSource), mAction(cAction){}

    EVENT_CLASS_SCOPELESS_TYPE(std::string, "MENUACTION");

    T* mpSource;
    MenuEvent mAction;
};

#endif