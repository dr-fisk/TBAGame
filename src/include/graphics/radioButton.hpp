#ifndef RADIO_BUTTON_HPP
#define RADIO_BUTTON_HPP

#include "toggleButton.hpp"

class RadioButton : public ToggleButton
{
  public:
    //! @brief Default Constructor
    RadioButton();

    //! @brief Default Destructor
    ~RadioButton() = default;
  private:
    //! @brief Handles Button Clicked logic for the radio button
    void buttonClicked() final;
};

#endif