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
  mCallback = nullptr;
}

//! @brief Sets the Callback function to be called when the button is clicked
//!
//! @param pFunc Function to call when button is clicked
//!
//! @return None 
void Button::setCallback(std::function<void(void)> pFunc)
{
  mCallback = std::bind(pFunc);
}

//! @brief Handles the Mouse Move Event for the button
//!
//! @param crEvent Mouse Move Event
//!
//! @return None
void Button::mouseMoveUpdate(const Event::MouseMoveEvent& crEvent)
{
  switch(mState)
  {
    case DEFAULT_STATE:
      if(isInAABB({crEvent.x, crEvent.y}))
      {
        mBox->setColor(mHoverColor);
        mState = HOVER_STATE;
      }
    case HOVER_STATE:
      if(!isInAABB({crEvent.x, crEvent.y}))
      {
        mBox->setColor(mDefaultColor);
        mState = DEFAULT_STATE;
      }
  }
}

//! @brief Handles a Mouse Button Press
//!
//! @param crEvent Mouse Button Press
//!
//! @return None
void Button::mouseButtonUpdate(const Event::MouseButtonEvent& crEvent)
{
  switch(mState)
  {
    case HOVER_STATE:
      if(isInAABB({crEvent.x, crEvent.y}))
      {
        mBox->setColor(mPressedColor);
      }

      break;
  }
}

//! @brief Handles Mouse Button Release Event
//!
//! @param crEvent Mouse Button Release Event
//!
//! @return None
void Button::mouseButtonRelease(const Event::MouseButtonEvent& crEvent)
{
  switch(mState)
  {
    case HOVER_STATE:
      if(isInAABB({crEvent.x, crEvent.y}))
      {
        if(nullptr != mCallback)
        {
          mCallback();
        }

        mBox->setColor(mHoverColor);
        mState = HOVER_STATE;
      }
      break;
  }
}

//! @brief Event Handler State Machine that calls appropiate functions
//!
//! @param crEvent Mouse Event to be Processed
//!
//! @retur None 
void Button::handleEvents(const Event& crEvent)
{
  switch(crEvent.Type)
  {
    case Event::MouseMove:
      mouseMoveUpdate(crEvent.MousePos);
      break;
    case Event::MouseButtonPress:
      if (GLFW_MOUSE_BUTTON_LEFT == crEvent.MouseButton.Button)
      {
        mouseButtonUpdate(crEvent.MouseButton);
      }
      break;
    case Event::MouseButtonRelease:
      if (GLFW_MOUSE_BUTTON_LEFT == crEvent.MouseButton.Button)
      {
        mouseButtonRelease(crEvent.MouseButton);
      }
      break;
    default:
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

//! @brief Determines if Mouse Position is in AABB of button
//!
//! @return True if Mouse is in AABB false otherwise
bool Button::isInAABB(const Vector2<float>& crPos)
{
  Box<float> box = mBox->getBox();

  return box.inLocalBounds(crPos);
}