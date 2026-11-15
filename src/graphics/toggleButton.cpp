#include "graphics/toggleButton.hpp"

ToggleButton::ToggleButton()
{
  mLabel.getModifier().setHorizontalAlign(HorizontalAlign::CENTER_OUTSIDE_RIGHT);
  mLabel.getModifier().setVerticalAlign(VerticalAlign::CENTER);
}

ToggleButton& ToggleButton::setSelectedTexture(const std::shared_ptr<FrameSource> cpFrameSource)
{
  mpButtonSelectedTexture = cpFrameSource;
  return *this;
}

ToggleButton& ToggleButton::setUnSelectedTexture(const std::shared_ptr<FrameSource> cpFrameSource)
{
  mpButtonUnselectedTexture = cpFrameSource;
  return *this;
}

void ToggleButton::buttonClicked()
{
  if(!mSelected)
  {
    SelectEvent event(this);
    mSelectedEventDisp.notify(event);
  }

  mSelected = !mSelected;
  mState = ButtonState::HOVER_STATE;
}

void ToggleButton::setButtonTexture()
{
  if(mSelected)
  {
    mLabel.setFrameSource(mpButtonSelectedTexture);
    if(!mIsFocused)
    {
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
      mLabel.setBorder(2.0f);
      mLabel.setBorderColor(lg::Blue);
    }
  }
  else
  {
    if(mpButtonUnselectedTexture)
    {
      mLabel.setFrameSource(mpButtonUnselectedTexture);
    }
    else
    {
      AbstractButton::setButtonTexture();
      mLabel.setFrameSource(nullptr);
    }
  }
}

ToggleButton& ToggleButton::setSelected(const bool cSelected)
{
  mSelected = cSelected;
  ToggleButton::setButtonTexture();
  return *this;
}

ToggleButton& ToggleButton::addSelectedEventListener(EventSubscriber<SelectEvent>& rListener)
{
  mSelectedEventDisp.registerToEvent(rListener);
  return *this;
}