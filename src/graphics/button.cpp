#include "graphics/button.hpp"
#include "input/mouse.hpp"
#include "renderer/renderer2D.hpp"

//! @brief Button constructor
//!
//! @param[in] crBox Dimensions of Button
//!
//! @return Button Object 
Button::Button()
{
  mState = ButtonState::DEFAULT_STATE;
  // mCallbackDisabled = false;
  mCallback = nullptr;
  mId = -1;
  mPressedPadding = glm::vec2(0, 0);
}

Button::Button(const Modifier& crModifier, const TextModifier& crTextModifier) :
  AbstractButton(crModifier, crTextModifier)
{
}

//! @brief Sets the Button Position
//!
//! @param[in] crPos The new button Position
//! @param[in] cCheckIfMouseHovering Flag to check if mouse is in AABB of button after moving pos
//!
//! @return None
Button& Button::setPos(const glm::vec2& crPos, const bool cCheckIfMouseHovering)
{
  mModifier.setPos(crPos);

  // onButtonMoveUpdate(cCheckIfMouseHovering);
  return *this;
}

//! @brief Sets whether to render Button or not
//!
//! @param[in] cEnable Enable/Disable Rendering for button
//!
//! @return None
Button& Button::setRender(const bool cEnable)
{
  // mBox.setRender(cEnable);
  // mText.setRender(cEnable);
  return *this;
}

//! @brief Sets the ID of Button
//!        It is not a global ID that is determine by implementation
//!
//! @param[in] cId ID to set on Button
//!
//! @return None
Button& Button::setId(const int64_t cId)
{
  mId = cId;
  return *this;
}

//! @brief Returns current ID of Button
//!
//! @return Button ID
int64_t Button::getId() const
{
  return mId;
}

//! @brief Enable/Disable Callback
//!
//! @param[in] cEnable Enable or Disable Callback
//!
//! @return None 
void Button::disableCallback(const bool cEnable)
{
  // mCallbackDisabled = cEnable;
}

//! @brief Returns if mouse is hovering over button
//!
//! @return true if mouse is hovering false otherwise
bool Button::isHover() const
{
  return ButtonState::HOVER_STATE == mState;
}

//! @brief Returns if button is pressed
//!
//! @return true if button is pressed false otherwise
bool Button::isPressed() const
{
  return ButtonState::PRESSED_STATE == mState;
}

//! @brief Sets the Pressed padding 
//!        This means the button will have a larger AABB for the button if the padding is > 0 when in pressed state
//! 
//! @param[in] crPadding The padding to set on the button
//!
//! @return None 
Button& Button::setPressedPadding(const glm::vec2& crPadding)
{
  mPressedPadding = crPadding;
  return *this;
}

//! @brief Handles a button click event
//!
//! @return None
void Button::buttonClicked()
{
  mState = ButtonState::HOVER_STATE;
}

//! @brief Sets the correct Color/Texture depending on button state
//!
//! @return None 

//! @brief Handles Updating Button State after position is moved
//!
//! @param[in] cCheckIfMouseHovering Flag to determine if AABB should be checked after moving
//!
//! @return None
// void Button::onButtonMoveUpdate(const bool cCheckIfMouseHovering)
// {
//   if(cCheckIfMouseHovering)
//   {
//     switch(mState)
//     {
//       case ButtonState::HOVER_STATE:
//         if(!isInAABB(lg::Mouse::getMousePosf()))
//         {
//           mState = ButtonState::DEFAULT_STATE;
//         }
//         break;
//       case ButtonState::PRESSED_STATE:
//         if(!isInAABB(lg::Mouse::getMousePosf(), mPressedPadding))
//         {
//           mState = ButtonState::DEFAULT_STATE;
//         }
//         break;
//       case ButtonState::DEFAULT_STATE:
//         if(isInAABB(lg::Mouse::getMousePosf()))
//         {
//           mState = ButtonState::HOVER_STATE;
//         }
//     }
//   }
//   else
//   {
//     mState = ButtonState::DEFAULT_STATE;
//   }

//   setButtonTexture();
// }