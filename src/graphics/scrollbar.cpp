#include <iostream>

#include "graphics/scrollbar.hpp"
#include "event/lestRenderEngineEventManager.hpp"

//! @brief Scrollbar Constructor
//!
//! @param[in] cOrientation Orientation of the scrollbar Vertical or Horizontal 
//! @param[in] cMin         Min Coordinates that matches orientation of scrollbar
//! @param[in] cMax         Max Coordinates that matches orientation of scrollbar
//!
//! @return Scrollbar object
Scrollbar::Scrollbar(const ScrollbarOrientation cOrientation, const uint32_t cMin, const uint32_t cMax)
{
  mState = DEFAULT_STATE;
  mOrientation = cOrientation;
  mPrevMousePos = {0, 0};
  mPadding = {0, 0};
  mMinBound = cMin;
  mMaxBound = cMax;
  SLOT(mMouseMoveSub, Scrollbar::onMouseMove);
}

//! @brief Sets a button to the scrollbar
//!
//! @param[in] crButton Button to set
//! 
//! @return Scrollbar reference to chain calls 
Scrollbar& Scrollbar::setButton(const std::shared_ptr<Button> cpButton)
{
  mScrollbarButton = cpButton;
  mScrollbarButton->onClick([this](){ mState = DEFAULT_STATE;});
  return *this;
}

void Scrollbar::onMouseMove(LestRenderEngine::MouseMoveEvent& crEvent)
{
  if(!mScrollbarButton->isPressed())
  {
    mPrevMousePos = {crEvent.getX(), crEvent.getY()};
    return;
  }

  glm::vec2 moveVector = {0, 0};
  glm::vec2 topLeft = mScrollbarButton->getPos() - (mScrollbarButton->getSize() / 2.0f);
  glm::vec2 bottomRight = mScrollbarButton->getPos() + (mScrollbarButton->getSize() / 2.0f);

  if(ScrollbarOrientation::VERTICAL == mOrientation)
  {
    moveVector = {0, crEvent.getY() - mPrevMousePos.y};

    if(bottomRight.y + moveVector.y >= mMaxBound)
    {
      moveVector.y = mMaxBound - bottomRight.y;
    }
    else if(topLeft.y + moveVector.y <= mMinBound)
    {
      moveVector.y = mMinBound - topLeft.y;
    }
  }
  else
  {
    moveVector = {crEvent.getX() - mPrevMousePos.x, 0};
    
    if(bottomRight.x + moveVector.x >= mMaxBound)
    {
      moveVector.x = mMaxBound - bottomRight.x;
    }
    else if(topLeft.x + moveVector.x <= mMinBound)
    {
      moveVector.x = mMinBound - topLeft.x;
    }
  }

  mScrollbarButton->movePos(moveVector);

  for(auto& component : mGraphicsList)
  {
    // Invert movement for components
    component->movePos({moveVector.x * -1, moveVector.y * -1});
  }

  mPrevMousePos = {crEvent.getX(), crEvent.getY()};
}

//! @brief Handles the mouse move event
//!
//! @param[in] crEvent Mouse Event
//!
//! @return None 
void Scrollbar::mouseMoveEvent(const Event& crEvent)
{
  glm::vec2 moveVector = {0, 0};
  glm::vec2 topLeft = mScrollbarButton->getPos() - (mScrollbarButton->getSize() / 2.0f);
  glm::vec2 bottomRight = mScrollbarButton->getPos() + (mScrollbarButton->getSize() / 2.0f);

  if(ScrollbarOrientation::VERTICAL == mOrientation)
  {
    moveVector = {0, crEvent.MousePos.y - mPrevMousePos.y};

    if(bottomRight.y + moveVector.y >= mMaxBound)
    {
      moveVector.y = mMaxBound - bottomRight.y;
    }
    else if(topLeft.y + moveVector.y <= mMinBound)
    {
      moveVector.y = mMinBound - topLeft.y;
    }
  }
  else
  {
    moveVector = {crEvent.MousePos.x - mPrevMousePos.x, 0};
    
    if(bottomRight.x + moveVector.x >= mMaxBound)
    {
      moveVector.x = mMaxBound - bottomRight.x;
    }
    else if(topLeft.x + moveVector.x <= mMinBound)
    {
      moveVector.x = mMinBound - topLeft.x;
    }
  }

  mScrollbarButton->movePos(moveVector);

  for(auto& component : mGraphicsList)
  {
    // Invert movement for components
    component->movePos({moveVector.x * -1, moveVector.y * -1});
  }

  mPrevMousePos = {crEvent.MousePos.x, crEvent.MousePos.y};
}

//! @brief Udates the scrollbar
//!
//! @param crEvent Event to handle
//!
//! @return None
void Scrollbar::update(const Event& crEvent)
{
  mScrollbarButton->handleEvent(crEvent);

  if(mScrollbarButton->isPressed())
  {
    switch(mState)
    {
      case DEFAULT_STATE:
        mState = SCROLL_STATE;
        mPrevMousePos = {crEvent.MouseButton.x, crEvent.MouseButton.y};
        break;
      case SCROLL_STATE:
        switch(crEvent.Type)
        {
          case Event::EventType::MouseMove:
            mouseMoveEvent(crEvent);
            break;
        }
        break;
    }
  }
  else
  {
    mState = DEFAULT_STATE;
  }
}

//! @brief Draws the scrollbar
//!
//! @return None
void Scrollbar::draw()
{
  mScrollbarButton->draw();
}

//! @brief Adds a component to the scrollbar
//!
//! @param[in] pComponent Component to add
//! 
//! @return Scrollbar reference to chain event 
Scrollbar& Scrollbar::addComponent(const std::shared_ptr<Component> pComponent)
{
  mGraphicsList.push_back(pComponent);
  return *this;
}

void Scrollbar::updateUI()
{
  mScrollbarButton->updateUI();
}