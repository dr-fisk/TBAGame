#ifndef BUTTON_GROUP_HPP
#define BUTTON_GROUP_HPP

#include "graphics/toggleButton.hpp"

class ButtonGroup
{
  public:
    //! @brief Default Constructor
    ButtonGroup();

    //! @brief Default Destructor
    ~ButtonGroup() = default;
  
    //! @brief Adds a toggle button to the Button Group
    //!
    //! @return Button Group reference to chain calls
    ButtonGroup& addButton(const std::shared_ptr<ToggleButton> cpToggleButton);
  private:

    void unselectButtons(ToggleButton::SelectEvent& rSelectEvent);

    //! List of toggle buttons
    std::vector<std::shared_ptr<ToggleButton>> mToggleButtons;

    //! Selected Event Listeners
    EventSubscriber<ToggleButton::SelectEvent> mSelectedEventSub;
};

#endif