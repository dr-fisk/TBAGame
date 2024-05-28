#include "graphics/toggleButton.hpp"

ToggleButton::ToggleButton() : mToggled(false)
{
}

void ToggleButton::buttonClicked()
{
  mToggled = ~mToggled;
}

void ToggleButton::draw()
{
  if(mVisible)
  {
    AbstractButton::draw();
    // mToggleSprite.draw();
  }
}