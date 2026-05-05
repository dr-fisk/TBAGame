#ifndef POPUP_MENU_EVENT_HPP
#define POPUP_MENU_EVENT_HPP

#include "event/I_Event.hpp"

enum class PopupMenuActionEvent
{
  MENU_CANCELLED,
  MENU_OPENED
};

template <typename T>
class PopupMenuActionEvent : public I_Event<std::string>
{
  public:
    //! @brief Delete Default Constructor
    PopupMenuActionEvent() = delete;

    //! @brief Default Destructor
    ~PopupMenuActionEvent() = default;

    //! @brief Constructor
    //!
    //! @tparam[in] pSrc Source of Event 
    //! @param[in] cX X Mouse Position
    //! @param[in] cY Y MousePosition
    PopupMenuActionEvent(T* pSource, const GuiEvent cAction, const float cX, const float cY) : 
     I_Event("POPUPACTION"), mpSource(pSource), mAction(cAction), x(cX), y(cY){}

    EVENT_CLASS_SCOPELESS_TYPE(std::string, "POPUPACTION");

    T* mpSource;
    PopupMenuActionEvent mAction;
    float x = 0;
    float y = 0;
};

#endif