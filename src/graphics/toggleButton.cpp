#include "graphics/toggleButton.hpp"
#include "resource/imageImporter.hpp"
#include <iostream>

ToggleButton::ToggleButton() : mToggled(false)
{
  // Move this out, checkbox and radio will have their own textures
  mpCheckedTexture = ImageImporter::buildStaticFrame("../Check.png");
}

void ToggleButton::buttonClicked()
{
  mToggled = !mToggled;
  mState = ButtonState::HOVER_STATE;
}

void ToggleButton::setButtonTexture()
{
  if(mToggled)
  {
    mLabel.setFrameSource(mpCheckedTexture);

    if(mLabel.hasBorder())
    {
      switch(mState)
      {
        case ButtonState::DEFAULT_STATE:
          mLabel.setBorderColor(mDefaultBorderColor);
          break;
        case ButtonState::HOVER_STATE:
          mLabel.setBorderColor(mHoverBorderColor);
          break;
        case ButtonState::PRESSED_STATE:
          mLabel.setBorderColor(mPressedBorderColor);
          break;
        default:
          break;
      }
    }
  }
  else
  {
    AbstractButton::setButtonTexture();
  }
}

// void ToggleButton::draw()
// {
//   if(mVisible)
//   {
//     AbstractButton::draw();
//     // mToggleSprite.draw();
//   }
// }