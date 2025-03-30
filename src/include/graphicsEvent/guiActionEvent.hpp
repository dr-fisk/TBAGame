#ifndef GUI_ACTION_EVENT
#define GUI_ACTION_EVENT

#include "event/I_Event.hpp"

enum class GuiEvent
{
  GUI_HOVER,
  GUI_PRESS,
  GUI_EXIT,
  GUI_CLICK
};

template <typename T>
class GuiActionEvent : public I_Event<std::string>
{
  public:
    //! @brief Delete Default Constructor
    GuiActionEvent() = delete;

    //! @brief Default Destructor
    ~GuiActionEvent() = default;

    //! @brief Constructor
    //!
    //! @tparam[in] pSrc Source of Event 
    //! @param[in] cX X Mouse Position
    //! @param[in] cY Y MousePosition
    GuiActionEvent(T* pSource, const GuiEvent cAction, const float cX, const float cY) : 
     I_Event("GUIACTION"), mpSource(pSource), mAction(cAction), x(cX), y(cY){}

    EVENT_CLASS_SCOPELESS_TYPE(std::string, "GUIACTION");

    T* mpSource;
    GuiEvent mAction;
    float x = 0;
    float y = 0;
};

#endif