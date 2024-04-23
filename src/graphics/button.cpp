#include "graphics/button.hpp"
#include "window/mouse.hpp"
#include "renderer/renderer2D.hpp"

//! @brief Button constructor
//!
//! @param[in] crBox Dimensions of Button
//!
//! @return Button Object 
template <typename T>
Button<T>::Button(const Box<glm::vec2>& crBox)
{
  mDefaultColor = lg::Transparent;
  mHoverColor = lg::Transparent;
  mPressedColor = lg::Transparent;
  mState = DEFAULT_STATE;
  mBox.setBox(crBox);
  mCallbackDisabled = false;
  mCallback = nullptr;
  mId = -1;
  mPressedPadding = glm::vec2(0, 0);
}

//! @brief Sets the Callback function to be called when the button is clicked
//!
//! @param pFunc Function to call when button is clicked
//!
//! @return None
template <typename T>
void Button<T>::onClick(std::function<void(const Button<T>&)> pFunc)
{
  mCallback = pFunc;
}

//! @brief Handles the Mouse Move Event for the button
//!
//! @param crEvent Mouse Move Event
//!
//! @return None
template <typename T>
void Button<T>::mouseMoveUpdate(const Event::MouseMoveEvent& crEvent)
{
  switch(mState)
  {
    case DEFAULT_STATE:
      if(isInAABB({crEvent.x, crEvent.y}))
      {
        mState = HOVER_STATE;
        setButtonTexture();
      }

      break;
    case HOVER_STATE:
      if(!isInAABB({crEvent.x, crEvent.y}))
      {
        mState = DEFAULT_STATE;
        setButtonTexture();
      }

      break;
    case PRESSED_STATE:
      if(!isInAABB({crEvent.x, crEvent.y}, mPressedPadding))
      {
        mState = DEFAULT_STATE;
        setButtonTexture();
      }
      break;
  }
}

//! @brief Handles a Mouse Button Press
//!
//! @param crEvent Mouse Button Press
//!
//! @return None
template <typename T>
void Button<T>::mouseButtonUpdate(const Event::MouseButtonEvent& crEvent)
{
  switch(mState)
  {
    case HOVER_STATE:
      if(isInAABB({crEvent.x, crEvent.y}))
      { 
        mState = PRESSED_STATE;
        setButtonTexture();
      }

      break;
  }
}

//! @brief Handles Mouse Button Release Event
//!
//! @param crEvent Mouse Button Release Event
//!
//! @return returns true if Button clicked false otherwise
template <typename T>
bool Button<T>::mouseButtonRelease(const Event::MouseButtonEvent& crEvent)
{
  switch(mState)
  {
    case PRESSED_STATE:
      if(isInAABB({crEvent.x, crEvent.y}))
      {
        mState = HOVER_STATE;

        if(!mCallbackDisabled && (nullptr != mCallback))
        {
          mCallback(*this);
        }

        setButtonTexture();

        return true;
      }
      break;
  }

  return false;
}

//! @brief Event Handler State Machine that calls appropiate functions
//!
//! @param crEvent Mouse Event to be Processed
//!
//! @return true if Button clicked false otherwise
template <typename T>
bool Button<T>::clicked(const Event& crEvent)
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
        return mouseButtonRelease(crEvent.MouseButton);
      }
      break;
    default:
      break;
  }

  return false;
}

//! @brief Moves the Button Position
//!
//! @param[in] crMove                The movment vector
//! @param[in] cCheckIfMouseHovering Flag to check if mouse is in AABB of button after moving pos
//!
//! @return None
template <typename T>
void Button<T>::movePos(const glm::vec2& crMove, const bool cCheckIfMouseHovering)
{
  mBox.movePos(crMove);

  if (0 != mText.getLength())
  {
    setTextPos();
  }

  onButtonMoveUpdate(cCheckIfMouseHovering);
}

//! @brief Sets the Button Position
//!
//! @param[in] crPos The new button Position
//! @param[in] cCheckIfMouseHovering Flag to check if mouse is in AABB of button after moving pos
//!
//! @return None
template <typename T>
Button<T>& Button<T>::setPos(const glm::vec2& crPos, const bool cCheckIfMouseHovering)
{
  mBox.setPos(crPos);

  if (0 != mText.getLength())
  {
    setTextPos();
  }

  onButtonMoveUpdate(cCheckIfMouseHovering);
  return *this;
}

//! @brief Sets the position of Text within the center of the box
//!
//! @return None
template <typename T>
void Button<T>::setTextPos()
{
  glm::vec2 textSize = mText.getSize();
  glm::vec2 buttonCenter = mBox.getPos();
  mText.setPos({buttonCenter.x - (textSize.x / 2.0f), buttonCenter.y - (textSize.y / 2.0f)});
}

//! @brief Sets Button Size
//!
//! @param[in] crSize Size of Button
//!
//! @return None
template <typename T>
Button<T>& Button<T>::setSize(const glm::vec2& crSize)
{
  mBox.setSize(crSize);

  if (0 != mText.getLength())
  {
    setTextPos();
  }

  return *this;
}

//! @brief Sets the Default Button Color
//!
//! @param crColor Color of Button
//!
//! @return None
template <typename T>
Button<T>& Button<T>::setDefaultColor(const lg::Color& crColor)
{
  mDefaultColor = crColor;
  mBox.setColor(crColor);
  return *this;
}

//! @brief Sets the Button Hover Color
//!
//! @param crColor Color of Button
//!
//! @return None
template <typename T>
Button<T>& Button<T>::setHoverColor(const lg::Color& crColor)
{
  mHoverColor = crColor;
  return *this;
}

//! @brief Sets the Button Pressed Color
//!
//! @param crColor Color of Button
//!
//! @return None
template <typename T>
Button<T>& Button<T>::setPressedColor(const lg::Color& crColor)
{
  mPressedColor = crColor;
  return *this;
}

//! @brief Determines if Mouse Position is in AABB of button
//!
//! @param[in] crPos Position to check against button AABB
//!
//! @return True if Mouse is in AABB false otherwise
template <typename T>
bool Button<T>::isInAABB(const glm::vec2& crPos)
{
  Box<glm::vec2> box = mBox.getBox();
  return box.inLocalBounds(crPos);
}

//! @brief Determines if Mouse Position is in AABB of button
//!
//! @param[in] crPos     Position to check against button AABB
//! @param[in] crPadding Padding to add to AABB of button
//!
//! @return True if Mouse is in AABB false otherwise
template <typename T>
bool Button<T>::isInAABB(const glm::vec2& crPos, const glm::vec2& crPadding)
{
  Box<glm::vec2> box = mBox.getBox();
  glm::vec2 size = box.getSize();
  size += crPadding;
  box.setSize(size);
  return box.inLocalBounds(crPos);
}

//! @brief Sets whether to render Button or not
//!
//! @param[in] cEnable Enable/Disable Rendering for button
//!
//! @return None
template <typename T>
Button<T>& Button<T>::setRender(const bool cEnable)
{
  mBox.setRender(cEnable);
  mText.setRender(cEnable);
  return *this;
}

//! @brief Sets the ID of Button
//!        It is not a global ID that is determine by implementation
//!
//! @param[in] cId ID to set on Button
//!
//! @return None
template <typename T>
Button<T>& Button<T>::setId(const int64_t cId)
{
  mId = cId;
  return *this;
}

//! @brief Returns current ID of Button
//!
//! @return Button ID
template <typename T>
int64_t Button<T>::getId() const
{
  return mId;
}

//! @brief Gets Button Position
//!
//! @return Button Position
template <typename T>
glm::vec2 Button<T>::getPos() const
{
  return mBox.getPos();
}

//! @brief Gets Button Size
//!
//! @return Button Size
template <typename T>
glm::vec2 Button<T>::getSize() const
{
  return mBox.getSize();
}

//! @brief Sets the Default Texture for Button to reference
//!        If Button is in Default State, Texture will be applied here
//!
//! @param crpTexture Texture to set
//!
//! @return None
template <typename T>
Button<T>& Button<T>::setDefaultTexture(const std::shared_ptr<Texture2D>& crpTexture)
{
  mDefaultTexture = crpTexture;

  if(DEFAULT_STATE == mState)
  {
    mBox.setTexture(*mDefaultTexture);
  }

  return *this;
}

//! @brief Sets the Hover Texture for Button to reference
//!        If Button is in Hover State, Texture will be applied here
//!
//! @param crpTexture Texture to set
//!
//! @return None
template <typename T>
Button<T>& Button<T>::setHoverTexture(const std::shared_ptr<Texture2D>& crpTexture)
{
  mHoverTexture = crpTexture;

  if(HOVER_STATE == mState)
  {
    mBox.setTexture(*mHoverTexture);
  }

  return *this;
}

//! @brief Sets the Pressed Texture for Button to reference
//!        Texture not automatically applied as it only happens on click events
//!
//! @param crpTexture Texture to set
//!
//! @return None
template <typename T>
Button<T>& Button<T>::setPressedTexture(const std::shared_ptr<Texture2D>& crpTexture)
{
  mPressedTexture = crpTexture;
  return *this;
}

//! @brief Sets a value to store in the Button
//!
//! @param[in] rValue Value to store
//!
//! @return None 
template <typename T>
Button<T>& Button<T>::setValue(const T& rValue)
{
  mValue = rValue;
  return *this;
}

//! @brief Gets the value stored in the Button
//!
//! @return None 
template <typename T>
T Button<T>::getValue() const
{
  return mValue;
}

//! @brief Enable/Disable Callback
//!
//! @param[in] cEnable Enable or Disable Callback
//!
//! @return None 
template <typename T>
void Button<T>::disableCallback(const bool cEnable)
{
  mCallbackDisabled = cEnable;
}

//! @brief Returns if mouse is hovering over button
//!
//! @return true if mouse is hovering false otherwise
template <typename T>
bool Button<T>::isHover() const
{
  return HOVER_STATE == mState;
}

//! @brief Returns if button is pressed
//!
//! @return true if button is pressed false otherwise
template <typename T>
bool Button<T>::isPressed() const
{
  return PRESSED_STATE == mState;
}

//! @brief Sets the Pressed padding 
//!        This means the button will have a larger AABB for the button if the padding is > 0 when in pressed state
//! 
//! @param[in] crPadding The padding to set on the button
//!
//! @return None 
template <typename T>
Button<T>& Button<T>::setPressedPadding(const glm::vec2& crPadding)
{
  mPressedPadding = crPadding;
  return *this;
}

//! @brief Sets the correct Color/Texture depending on button state
//!
//! @return None 
template <typename T>
void Button<T>::setButtonTexture()
{
  switch(mState)
  {
    case DEFAULT_STATE:
      if(nullptr != mDefaultTexture)
      {
        mBox.setTexture(*mDefaultTexture);
      }
      else
      {
        mBox.setColor(mDefaultColor);
      }
      break;
    case HOVER_STATE:
      if(nullptr != mHoverTexture)
      {
        mBox.setTexture(*mHoverTexture);
      }
      else
      {
        mBox.setColor(mHoverColor);
      }
      break;
    case PRESSED_STATE:
      if(nullptr != mPressedTexture)
      {
        mBox.setTexture(*mPressedTexture);
      }
      else
      {
        mBox.setColor(mPressedColor);
      }
      break;
  }
}

//! @brief Handles Updating Button State after position is moved
//!
//! @param[in] cCheckIfMouseHovering Flag to determine if AABB should be checked after moving
//!
//! @return None
template <typename T>
void Button<T>::onButtonMoveUpdate(const bool cCheckIfMouseHovering)
{
  if(cCheckIfMouseHovering)
  {
    switch(mState)
    {
      case HOVER_STATE:
        if(!isInAABB(lg::Mouse::getMousePosf()))
        {
          mState = DEFAULT_STATE;
        }
        break;
      case PRESSED_STATE:
        if(!isInAABB(lg::Mouse::getMousePosf(), mPressedPadding))
        {
          mState = DEFAULT_STATE;
        }
        break;
      case DEFAULT_STATE:
        if(isInAABB(lg::Mouse::getMousePosf()))
        {
          mState = HOVER_STATE;
        }
    }
  }
  else
  {
    mState = DEFAULT_STATE;
  }

  setButtonTexture();
}

//! @brief Draws Button
//!
//! @return None
template <typename T>
void Button<T>::draw()
{
  mBox.draw();

  if(0 != mText.getLength())
  {
    mText.draw();
  }
}

template <typename T>
Button<T>& Button<T>::setText(const Text& crText)
{
  mText = crText;
  setTextPos();
  return *this;
}

template <typename T>
Button<T>& Button<T>::setString(const std::string& crString)
{
  mText.setString(crString);
  return *this;
}

template <typename T>
std::string& Button<T>::getString()
{
  return mText.getString();
}

template <typename T>
Button<T>& Button<T>::setTextColor(const lg::Color &crColor)
{
  mText.setColor(crColor);
  return *this;
}