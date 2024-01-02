#include "graphics/button.h"
#include "window/mouse.h"

//! @brief Constructs Buton
//!
//! @param[in] prFont         Font to use for Text in Button
//! @param[in] crText         String to set in Button
//! @param[in] prRenderEngine Resource Manager
//! @param[in] prBatch        Batch Buffer Manager
//! @param[in] cCharSize      Character Size for Text
//! @param[in] crPos          Position of Button
//! @param[in] crSize         Size of Button
//!
//! @return None
Button::Button(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<RenderEngine>& prRenderEngine,
               std::shared_ptr<BatchBuffer>& prBatch, const uint8_t cCharSize,
              const Vector2<float>& crPos, const Vector2<float>& crSize)
{
  Vector2<float> tempPos(0, 0);
  mBox = std::make_shared<Sprite>(prBatch, tempPos, crSize, lg::Transparent);
  mText = std::make_shared<Text>(prFont, crText, prRenderEngine, prBatch, cCharSize, tempPos);
  mDefaultColor = lg::Transparent;
  mHoverColor = lg::Transparent;
  mPressedColor = lg::Transparent;
  mState = DEFAULT_STATE;
  setPos(crPos);
}

//! @brief Updates Button State
//!
//! @return None
void Button::update()
{
  switch(mState)
  {
    case DEFAULT_STATE:
      if(isInAABB())
      {
        mBox->setColor(lg::Green);
        mState = HOVER_STATE;
      }
      break;
    case HOVER_STATE:
      if(!isInAABB())
      {
        mBox->setColor(mDefaultColor);
        mState = DEFAULT_STATE;
      }
      else if(lg::Mouse::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
      {
        mBox->setColor(mPressedColor);
        mState = PRESSED_STATE;
      }
      break;
    case PRESSED_STATE:
      mState = DEFAULT_STATE;
      mBox->setColor(mDefaultColor);
      break;
  }
}

//! @brief Sets the Button Position
//!
//! @param[in] cLeft Left Position of Button
//! @param[in] cTop  Top Position of Button
//!
//! @return None
void Button::setPos(const Vector2<float>& crPos)
{
  mBox->setPos(crPos);
  Vector2<float> textCenter = mText->getPos();
  Vector2<float> buttonCenter = mBox->getPos();
  mText->setPos({buttonCenter.x - textCenter.x, buttonCenter.y - textCenter.y});
}

//! @brief Sets Button Size
//!
//! @param[in] crSize Size of Button
//!
//! @return None
void Button::setSize(const Vector2<float>& crSize)
{
  mBox->setSize(crSize);
}

//! @brief Sets the Default Button Color
//!
//! @param crColor Color of Button
//!
//! @return None
void Button::setDefaultColor(const lg::Color& crColor)
{
  mDefaultColor = crColor;
  mBox->setColor(crColor);
}

//! @brief Sets the Button Hover Color
//!
//! @param crColor Color of Button
//!
//! @return None
void Button::setHoverColor(const lg::Color& crColor)
{
  mHoverColor = crColor;
}

//! @brief Sets the Button Pressed Color
//!
//! @param crColor Color of Button
//!
//! @return None
void Button::setPressedColor(const lg::Color& crColor)
{
  mPressedColor = crColor;
}

//! @brief Checks if Button is pressed
//!
//! @return true if Button is pressed false otherwise
bool Button::buttonPressed()
{
  return PRESSED_STATE == mState;
}

//! @brief Determines if Mouse Position is in AABB of button
//!
//! @return True if Mouse is in AABB false otherwise
bool Button::isInAABB()
{
  Box<float> box = mBox->getBox();
  Vector2<int32_t> mousePos = lg::Mouse::getMousePosi();

  return box.inLocalBounds(mousePos);
}