#include "graphics/radioButton.hpp"

RadioButton::RadioButton() : ToggleButton()
{
}

void RadioButton::buttonClicked()
{
  if(!mSelected)
  {
    SelectEvent event(this);
    mSelectedEventDisp.notify(event);
  }
  std::cout << mLabel.getText().getPos().x  << " " << mLabel.getText().getPos().y << std::endl;
  std::cout << mLabel.getText().getString() << std::endl;
  mSelected = true;
  mState = ButtonState::HOVER_STATE;
}