#include "graphics/abstractButton.hpp"
#include "event/lestRenderEngineEventManager.hpp"

//! @brief Default Constructor
//!
//! @return Abstract Button object
AbstractButton::AbstractButton()
{
  mDefaultBackgroundColor = lg::Grey;
  mLabel.setBackgroundColor(mDefaultBackgroundColor);
  mHoverBackgroundColor = lg::Green;
  mPressedBackgroundColor = lg::Red;
  mDefaultBorderColor = lg::Transparent;
  mHoverBorderColor = lg::Transparent;
  mPressedBorderColor = lg::Transparent;
  mState = ButtonState::DEFAULT_STATE;
  SLOT(mMouseButtonPressSub, AbstractButton::onMouseButtonPress);
  SLOT(mMouseButtonReleaseSub, AbstractButton::onMouseButtonRelease);
  SLOT(mMouseMoveSub, AbstractButton::onMouseMove);
}

AbstractButton::~AbstractButton()
{
}

//! @brief Event Handler State Machine that calls appropiate functions
//!
//! @param crEvent Mouse Event to be Processed
//!
//! @return None
void AbstractButton::handleEvent(const Event& crEvent)
{
  mClicked = false;
  if(!mEnabled)
  {
    return;
  }

  switch(crEvent.Type)
  {
    case Event::EventType::MouseMove:
      mouseMoveUpdate(crEvent.MousePos);
      break;
    case Event::EventType::MouseButtonPress:
      if (GLFW_MOUSE_BUTTON_LEFT == crEvent.MouseButton.Button)
      {
        mouseButtonUpdate(crEvent.MouseButton);
      }
      break;
    case Event::EventType::MouseButtonRelease:
      if (GLFW_MOUSE_BUTTON_LEFT == crEvent.MouseButton.Button)
      {
        mouseButtonRelease(crEvent.MouseButton);
      }
      break;
    default:
      break;
  }

}

//! @brief Handles the Mouse Move Event for the button
//!
//! @param crEvent Mouse Move Event
//!
//! @return None
void AbstractButton::mouseMoveUpdate(const Event::MouseMoveEvent& crEvent)
{
  switch(mState)
  {
    case ButtonState::DEFAULT_STATE:
      if(isInAABB({crEvent.x, crEvent.y}))
      {
        mState = ButtonState::HOVER_STATE;
        mUpdateUI = true;
    
      }

      break;
    case ButtonState::HOVER_STATE:
      if(!isInAABB({crEvent.x, crEvent.y}))
      {
        mState = ButtonState::DEFAULT_STATE;
    
        mUpdateUI = true;
      }

      break;
    case ButtonState::PRESSED_STATE:
      if(!isInAABB({crEvent.x, crEvent.y}, mPressedPadding))
      {
        mState = ButtonState::DEFAULT_STATE;
    
        mUpdateUI = true;
      }
      break;
  }
}

//! @brief Handles a Mouse Button Press
//!
//! @param crEvent Mouse Button Press
//!
//! @return None
void AbstractButton::mouseButtonUpdate(const Event::MouseButtonEvent& crEvent)
{
  switch(mState)
  {
    case ButtonState::HOVER_STATE:
      if(isInAABB({crEvent.x, crEvent.y}))
      { 
        mState = ButtonState::PRESSED_STATE;
    
        mUpdateUI = true;
      }

      break;
  }
}

//! @brief Handles Mouse Button Release Event
//!
//! @param crEvent Mouse Button Release Event
//!
//! @return returns true if Button clicked false otherwise
void AbstractButton::mouseButtonRelease(const Event::MouseButtonEvent& crEvent)
{
  switch(mState)
  {
    case ButtonState::PRESSED_STATE:
      if(isInAABB({crEvent.x, crEvent.y}))
      {
        buttonClicked();
    
        for(const auto& actionListener : mActionListeners)
        {
          actionListener->performAction(ActionEvent<AbstractButton>(this, 
                                        ActionEvent<AbstractButton>::ActionEventType::ACTION_OCCURRED));
        }

        if(mCallback)
        {
          mCallback();
        }

        mClicked = true;
      }
      else
      {
        mState = ButtonState::DEFAULT_STATE;
    
      }

      mUpdateUI = true;
      break;
  }
}

//! @brief Sets the string to be displayed ontop of the button
//!
//! @param[in] crString String to set
//! 
//! @return Abstract Button to chain calls
AbstractButton& AbstractButton::setString(const std::string& crString)
{
  mLabel.setString(crString);

  return *this;
}

//! @brief Gets the string displayed on the button
//!
//! @return Displayed string 
std::string AbstractButton::getString() const
{
  return mLabel.getString();
}

//! @brief Sets the Default Texture for Button to reference
//!        If Button is in Default State, Texture will be applied here
//!
//! @param crpTexture Texture to set
//!
//! @return None
AbstractButton& AbstractButton::setDefaultTexture(const std::shared_ptr<Texture2D>& crpTexture)
{
  mpDefaultTexture = crpTexture;
  mUpdateUI = true;

  return *this;
}

//! @brief Sets the Hover Texture for Button to reference
//!        If Button is in Hover State, Texture will be applied here
//!
//! @param crpTexture Texture to set
//!
//! @return None
AbstractButton& AbstractButton::setHoverTexture(const std::shared_ptr<Texture2D>& crpTexture)
{
  mpHoverTexture = crpTexture;
  mUpdateUI = true;

  return *this;
}

//! @brief Sets the Pressed Texture for Button to reference
//!        Texture not automatically applied as it only happens on click events
//!
//! @param crpTexture Texture to set
//!
//! @return None
AbstractButton& AbstractButton::setPressedTexture(const std::shared_ptr<Texture2D>& crpTexture)
{
  mpPressedTexture = crpTexture;
  mUpdateUI = true;
  return *this;
}

//! @brief Determines if Mouse Position is in AABB of button
//!
//! @param[in] crPos Position to check against button AABB
//!
//! @return True if Mouse is in AABB false otherwise
bool AbstractButton::isInAABB(const glm::vec2& crPos)
{
  glm::vec2 topLeft = mModifier.getPos() - (mModifier.getScale() / 2.0f);

  return (crPos.x > topLeft.x) && (crPos.x < (topLeft.x + mModifier.getScale().x)) &&
        (crPos.y > topLeft.y) && (crPos.y < (topLeft.y + mModifier.getScale().y));
}

//! @brief Determines if Mouse Position is in AABB of button
//!
//! @param[in] crPos     Position to check against button AABB
//! @param[in] crPadding Padding to add to AABB of button
//!
//! @return True if Mouse is in AABB false otherwise
bool AbstractButton::isInAABB(const glm::vec2& crPos, const glm::vec2& crPadding)
{

  glm::vec2 size = mModifier.getScale() + crPadding;
  glm::vec2 topLeft = mModifier.getPos() - (size / 2.0f);

  return (crPos.x > topLeft.x) && (crPos.x < (topLeft.x + size.x)) &&
        (crPos.y > topLeft.y) && (crPos.y < (topLeft.y + size.y));
}

//! @brief Sets the correct Color/Texture depending on button state
//!
//! @return None 
void AbstractButton::setButtonTexture()
{
  switch(mState)
  {
    case ButtonState::DEFAULT_STATE:
      if(nullptr != mpDefaultTexture)
      {
        mLabel.setTexture(mpDefaultTexture);
      }
      else
      {
        mLabel.setBackgroundColor(mDefaultBackgroundColor);
      }

      if(mLabel.hasBorder())
      {
        mLabel.setBorderColor(mDefaultBorderColor);
      }
      break;
    case ButtonState::HOVER_STATE:
      if(nullptr != mpHoverTexture)
      {
        mLabel.setTexture(mpHoverTexture);
      }
      else
      {
        mLabel.setBackgroundColor(mHoverBackgroundColor);
      }

      if(mLabel.hasBorder())
      {
        mLabel.setBorderColor(mHoverBorderColor);
      }
      break;
    case ButtonState::PRESSED_STATE:
      if(nullptr != mpPressedTexture)
      {
        mLabel.setTexture(mpPressedTexture);
      }
      else
      {
        mLabel.setBackgroundColor(mPressedBackgroundColor);
      }

      if(mLabel.hasBorder())
      {
        mLabel.setBorderColor(mPressedBorderColor);
      }
      break;
  }
}

//! @brief Draws Button
//!
//! @return None
void AbstractButton::draw()
{
  // Abstract buttons do not need to update anything itself, other classes that extend may have to

  if(mUpdateUI)
  {
    updateUI();
  }

  mLabel.draw();
}

//! @brief Moves the button by a specified amount
//!
//! @param[in] crMove The amount to move the button
//! 
//! @return Abstract button to chain calls
AbstractButton& AbstractButton::movePos(const glm::vec2& crMove)
{
  mModifier.moveTransform(crMove);
  mLabel.movePos(crMove);
  mUpdateUI = true;
  return *this;
}

//! @brief Sets the position of the button
//!
//! @param[in] crPos Position to set button
//! 
//! @return Abstract button to chain calls 
AbstractButton& AbstractButton::setPos(const glm::vec2& crPos)
{
  mModifier.setPos(crPos);
  mLabel.setPos(crPos);
  mUpdateUI = true;
  return *this;
}

//! @brief Resizes the button
//!
//! @param[in] crSize Size of Button
//!
//! @return None
AbstractButton& AbstractButton::resize(const glm::vec2& crSize)
{
  mModifier.setScale(crSize);
  mLabel.resize(crSize);
  mUpdateUI = true;
  return *this;
}

AbstractButton& AbstractButton::setLabel(const Label& crLabel)
{
  mLabel = crLabel;
  mUpdateUI = true;
  return *this;
}

//! @brief Sets the Callback function to be called when the button is clicked
//!
//! @param pFunc Function to call when button is clicked
//!
//! @return Abstract Button reference to chain calls
AbstractButton& AbstractButton::onClick(std::function<void()> pFunc)
{
  mCallback = pFunc;
  return *this;
}

//! @brief Gets Button Position
//!
//! @return Button Position
glm::vec2 AbstractButton::getPos() const
{
  return mModifier.getPos();
}

//! @brief Gets the size of button
//!
//! @return Size of button 
glm::vec2 AbstractButton::getSize() const
{
  return mModifier.getScale();
}

//! @brief Sets padding to allow users to click on button
//!
//! @param[in] crPadding Padding to set on button 
//!
//! @return Abstract Button to chain calls
AbstractButton& AbstractButton::setPadding(const glm::vec2& crPadding)
{
  mPressedPadding = crPadding;
  return *this;
}

//! @brief Returns whether the button was clicked
//!
//! @return true if clicked, false otherwise 
bool AbstractButton::wasClicked() const
{
  return mClicked;
}

//! @brief Returns whether Button is pressed
//!
//! @return true if pressed, false otherwise 
bool AbstractButton::isPressed() const
{
  return mState == ButtonState::PRESSED_STATE;
}

//! @brief TODO
//! @param pItemListener 
//! @return 
AbstractButton& AbstractButton::addItemListener(ItemListener* pItemListener)
{
  mItemListeners.push_back(pItemListener);
  return *this;
}

//! @brief Adds action listener to listeners list
//!
//! @param[in] pActionListener Listener 
//!
//! @return Abstract Button reference to chain calls
AbstractButton& AbstractButton::addActionListener(ActionListener<AbstractButton>* pActionListener)
{
  mActionListeners.push_back(pActionListener);
  return *this;
}

//! @brief Removes action listener from list
//!
//! @param[in] cpActionListener Listener
//!
//! @return None
void AbstractButton::removeActionListener(const ActionListener<AbstractButton>* cpActionListener)
{
  for(auto itr = mActionListeners.begin(); itr != mActionListeners.end();)
  {
    if(*itr == cpActionListener)
    {
      mActionListeners.erase(itr);
      break;
    }

    itr++;
  }
}

Label& AbstractButton::getLabel()
{
  return mLabel;
}

//! @brief Returns whether Button has mouse hovering over it
//!
//! @return true if mouse hovering over button, false otherwise 
bool AbstractButton::isHover() const
{
  return mState == ButtonState::HOVER_STATE;
}

//! @brief Returns whether Button is in a default state meaning not pressed, not hover
//!
//! @return true if button is in default state, false otherwise 
bool AbstractButton::isDefault() const
{
  return mState == ButtonState::DEFAULT_STATE;
}

AbstractButton& AbstractButton::setBorder(const float cBorderSize)
{
  mLabel.setBorder(cBorderSize);
  mUpdateUI = true;
  return *this;
}

AbstractButton& AbstractButton::setBackgroundColor(const ButtonState cState, const lg::Color& crColor)
{
  switch(cState)
  {
    case ButtonState::DEFAULT_STATE:
      mDefaultBackgroundColor = crColor;
      break;
    case ButtonState::HOVER_STATE:
      mHoverBackgroundColor = crColor;
      break;
    case ButtonState::PRESSED_STATE:
      mPressedBackgroundColor = crColor;
      break;
    default:
      return *this;  
  }

  mUpdateUI = true;
  return *this;
}

AbstractButton& AbstractButton::setBorderColor(const ButtonState cState, const lg::Color& crColor)
{
  switch(cState)
  {
    case ButtonState::DEFAULT_STATE:
      mDefaultBorderColor = crColor;
      break;
    case ButtonState::HOVER_STATE:
      mHoverBorderColor = crColor;
      break;
    case ButtonState::PRESSED_STATE:
      mPressedBorderColor = crColor;
      break;
    default:
      return *this;  
  }

  mUpdateUI = true;
  return *this; 
}

void AbstractButton::updateUI()
{
  setButtonTexture();
  mUpdateUI = false;
}

void AbstractButton::onMouseMove(LestRenderEngine::MouseMoveEvent& crEvent)
{
  switch(mState)
  {
    case ButtonState::DEFAULT_STATE:
      if(isInAABB({crEvent.getX(), crEvent.getY()}))
      {
        mState = ButtonState::HOVER_STATE;
        mUpdateUI = true;
    
      }

      break;
    case ButtonState::HOVER_STATE:
      if(!isInAABB({crEvent.getX(), crEvent.getY()}))
      {
        mState = ButtonState::DEFAULT_STATE;
    
        mUpdateUI = true;
      }

      break;
    case ButtonState::PRESSED_STATE:
      if(!isInAABB({crEvent.getX(), crEvent.getY()}, mPressedPadding))
      {
        mState = ButtonState::DEFAULT_STATE;
    
        mUpdateUI = true;
      }
      break;
  }
}

void AbstractButton::onMouseButtonPress(LestRenderEngine::MouseButtonPressEvent& crEvent)
{
  if (GLFW_MOUSE_BUTTON_LEFT == crEvent.getMouseButton() && mState == ButtonState::HOVER_STATE)
  {
    mState = ButtonState::PRESSED_STATE;
    mUpdateUI = true;
    // switch(mState)
    // {
    //   case ButtonState::HOVER_STATE:
    //     if(isInAABB({crEvent.getX(), crEvent.getY()}))
    //     { 
    //       mState = ButtonState::PRESSED_STATE;
      
    //       mUpdateUI = true;
    //     }

    //     break;
    // }
  }
}

void AbstractButton::onMouseButtonRelease(LestRenderEngine::MouseButtonReleaseEvent& crEvent)
{
  if (GLFW_MOUSE_BUTTON_LEFT == crEvent.getMouseButton())
  {
    switch(mState)
    {
      case ButtonState::PRESSED_STATE:
        if(isInAABB({crEvent.getX(), crEvent.getY()}))
        {
          buttonClicked();
      
          for(const auto& actionListener : mActionListeners)
          {
            actionListener->performAction(ActionEvent<AbstractButton>(this, 
                                          ActionEvent<AbstractButton>::ActionEventType::ACTION_OCCURRED));
          }

          if(mCallback)
          {
            mCallback();
          }

          mClicked = true;
        }
        else
        {
          mState = ButtonState::DEFAULT_STATE;
      
        }

        mUpdateUI = true;
        break;
    }
  }
}
