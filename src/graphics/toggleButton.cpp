#include "graphics/toggleButton.hpp"
#include "resource/image.hpp"
#include <iostream>

ToggleButton::ToggleButton() : mToggled(false)
{
  // Move this out, checkbox and radio will have their own textures
  Image temp_img("../src/Check.png");
  mpCheckedTexture = std::make_shared<Texture2D>();
  mpCheckedTexture->create(temp_img.getDimensions().y, temp_img.getDimensions().x, temp_img.getInternalFormat());
  mpCheckedTexture->update(temp_img.getImgData().data(), temp_img.getDimensions(), temp_img.getOffset(), temp_img.getFormat(), temp_img.getType());
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
    mLabel.setTexture(mpCheckedTexture);

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