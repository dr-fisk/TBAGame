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
template <typename T>
Button<T>::Button(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<RenderEngine>& prRenderEngine,
               std::shared_ptr<BatchBuffer>& prBatch, const uint8_t cCharSize,
               const Vector2<float>& crPos, const Vector2<float>& crSize)
{
  Vector2<float> tempPos(0, 0);
  mBox = std::make_shared<Sprite>(prBatch, tempPos, crSize, lg::Transparent);
  mBox->setLayer(1);
  mText = std::make_shared<Text>(prFont, crText, prRenderEngine, prBatch, cCharSize, tempPos);
  mDefaultColor = lg::Transparent;
  mHoverColor = lg::Transparent;
  mPressedColor = lg::Transparent;
  mState = DEFAULT_STATE;
  setPos(crPos);
  mCallback = nullptr;
  mId = -1;
  mCallbackDisabled = false;
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
        if(nullptr != mHoverTexture)
        {
          mBox->setTexture(mHoverTexture);
        }
        else
        {
          mBox->setColor(mHoverColor);
        }
        mState = HOVER_STATE;
      }

      break;
    case HOVER_STATE:
      if(!isInAABB({crEvent.x, crEvent.y}))
      {
        if(nullptr != mDefaultTexture)
        {
          mBox->setTexture(mDefaultTexture);
        }
        else
        {
          mBox->setColor(mDefaultColor);
        }
        mState = DEFAULT_STATE;
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
        if(nullptr != mPressedTexture)
        {
          mBox->setTexture(mPressedTexture);
        }
        else
        {
          mBox->setColor(mPressedColor);
        }
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
    case HOVER_STATE:
      if(isInAABB({crEvent.x, crEvent.y}))
      {
        if(!mCallbackDisabled && (nullptr != mCallback))
        {
          mCallback(*this);
        }

        if(nullptr != mHoverTexture)
        {
          mBox->setTexture(mHoverTexture);
        }
        else
        {
          mBox->setColor(mHoverColor);
        }

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

//! @brief Sets the Button Position
//!
//! @param[in] cLeft Left Position of Button
//! @param[in] cTop  Top Position of Button
//!
//! @return None
template <typename T>
void Button<T>::setPos(const Vector2<float>& crPos, const bool cCheckIfMouseHovering)
{
  mBox->setPos(crPos);
  // Vector2<float> textCenter = mText->getPos();
  Vector2<float> textSize = mText->getSize();
  Vector2<float> buttonCenter = mBox->getPos();
  mText->setPos({buttonCenter.x - (textSize.x / 2.0f), buttonCenter.y - (textSize.y / 2.0f)});

  if(cCheckIfMouseHovering && isInAABB(lg::Mouse::getMousePosf()))
  {
    mState = HOVER_STATE;
    if(nullptr != mHoverTexture)
    {
      mBox->setTexture(mHoverTexture);
    }
    else
    {
      mBox->setColor(mHoverColor);
    }
  }
  else
  {
    mState = DEFAULT_STATE;
    
    if(nullptr != mDefaultTexture)
    {
      mBox->setTexture(mDefaultTexture);
    }
    else
    {
      mBox->setColor(mDefaultColor);
    }
  }
}

//! @brief Sets Button Size
//!
//! @param[in] crSize Size of Button
//!
//! @return None
template <typename T>
void Button<T>::setSize(const Vector2<float>& crSize)
{
  mBox->setSize(crSize);
}

//! @brief Sets the Default Button Color
//!
//! @param crColor Color of Button
//!
//! @return None
template <typename T>
void Button<T>::setDefaultColor(const lg::Color& crColor)
{
  mDefaultColor = crColor;
  mBox->setColor(crColor);
}

//! @brief Sets the Button Hover Color
//!
//! @param crColor Color of Button
//!
//! @return None
template <typename T>
void Button<T>::setHoverColor(const lg::Color& crColor)
{
  mHoverColor = crColor;
}

//! @brief Sets the Button Pressed Color
//!
//! @param crColor Color of Button
//!
//! @return None
template <typename T>
void Button<T>::setPressedColor(const lg::Color& crColor)
{
  mPressedColor = crColor;
}

//! @brief Determines if Mouse Position is in AABB of button
//!
//! @return True if Mouse is in AABB false otherwise
template <typename T>
bool Button<T>::isInAABB(const Vector2<float>& crPos)
{
  Box<float> box = mBox->getBox();
  return box.inLocalBounds(crPos);
}

//! @brief Sets whether to render Button or not
//!
//! @param[in] cEnable Enable/Disable Rendering for button
//!
//! @return None
template <typename T>
void Button<T>::setRender(const bool cEnable)
{
  mBox->setRender(cEnable);
  mText->setRender(cEnable);
}

//! @brief Sets the ID of Button
//!        It is not a global ID that is determine by implementation
//!
//! @param[in] cId ID to set on Button
//!
//! @return None
template <typename T>
void Button<T>::setId(const int64_t cId)
{
  mId = cId;
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
Vector2<float> Button<T>::getPos() const
{
  return mBox->getPos();
}

//! @brief Gets Button Size
//!
//! @return Button Size
template <typename T>
Vector2<float> Button<T>::getSize() const
{
  return mBox->getSize();
}

//! @brief Sets the Default Texture for Button to reference
//!        If Button is in Default State, Texture will be applied here
//!
//! @param crpTexture Texture to set
//!
//! @return None
template <typename T>
void Button<T>::setDefaultTexture(const std::shared_ptr<TextureResource>& crpTexture)
{
  mDefaultTexture = crpTexture;

  if(DEFAULT_STATE == mState)
  {
    mBox->setTexture(mDefaultTexture);
  }
}

//! @brief Sets the Hover Texture for Button to reference
//!        If Button is in Hover State, Texture will be applied here
//!
//! @param crpTexture Texture to set
//!
//! @return None
template <typename T>
void Button<T>::setHoverTexture(const std::shared_ptr<TextureResource>& crpTexture)
{
  mHoverTexture = crpTexture;

  if(HOVER_STATE == mState)
  {
    mBox->setTexture(mHoverTexture);
  }
}

//! @brief Sets the Pressed Texture for Button to reference
//!        Texture not automatically applied as it only happens on click events
//!
//! @param crpTexture Texture to set
//!
//! @return None
template <typename T>
void Button<T>::setPressedTexture(const std::shared_ptr<TextureResource>& crpTexture)
{
  mPressedTexture = crpTexture;
}

//! @brief Sets a value to store in the Button
//!
//! @param[in] rValue Value to store
//!
//! @return None 
template <typename T>
void Button<T>::setValue(const T& rValue)
{
  mValue = rValue;
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
void Button<T>::enableCallback(const bool cEnable)
{
  mCallbackDisabled = cEnable;
}