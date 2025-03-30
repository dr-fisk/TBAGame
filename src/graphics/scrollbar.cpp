#include <iostream>

#include "graphics/scrollbar.hpp"
#include "event/lestRenderEngineEventManager.hpp"

Scrollbar::Scrollbar(const ScrollbarOrientation cOrientation, const uint32_t cMin, const uint32_t cMax)
{
  mState = DEFAULT_STATE;
  mOrientation = cOrientation;
  mPrevMousePos = {0, 0};
  mPadding = {0, 0};
  mMinBound = cMin;
  mMaxBound = cMax;

  mButtonClickSub.setCallback(BIND_EVENT_FN(Scrollbar::onButtonEvent));
}

//! @brief Sets a button to the scrollbar
//!
//! @param[in] crButton Button to set
//! 
//! @return Scrollbar reference to chain calls 
Scrollbar& Scrollbar::setButton(const std::shared_ptr<Button> cpButton)
{
  // if (mScrollbarButton)
  // {
  //   // mScrollbarButton
  // }
  mScrollbarButton = cpButton;
  mScrollbarButton->addButtonEventListener(mButtonClickSub);
  mComponents.push_back(mScrollbarButton);
  return *this;
}

void Scrollbar::moveHandler(AbstractButton::ButtonEvent& rButtonEvent)
{
  glm::vec2 moveVector = {0, 0};
  glm::vec2 topLeft = mScrollbarButton->getPos() - (mScrollbarButton->getSize() / 2.0f);
  glm::vec2 bottomRight = mScrollbarButton->getPos() + (mScrollbarButton->getSize() / 2.0f);

  if(ScrollbarOrientation::VERTICAL == mOrientation)
  {
    moveVector = {0, rButtonEvent.y - mPrevMousePos.y};

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
    moveVector = {rButtonEvent.x - mPrevMousePos.x, 0};
    
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
    if(*mScrollbarButton == *component)
    {
      continue;
    }
    // Invert movement for components
    component->movePos({moveVector.x * -1, moveVector.y * -1});
  }

  mPrevMousePos = {rButtonEvent.x, rButtonEvent.y};
}

void Scrollbar::draw()
{
  mScrollbarButton->draw();
}

Scrollbar& Scrollbar::addComponent(const std::shared_ptr<Component> pComponent)
{
  mGraphicsList.push_back(pComponent);
  return *this;
}

void Scrollbar::updateUI()
{
  mScrollbarButton->updateUI();
}

void Scrollbar::onButtonEvent(AbstractButton::ButtonEvent& rButtonEvent)
{
  switch(rButtonEvent.mAction)
  {
    case GuiEvent::GUI_HOVER:
      mPrevMousePos = {rButtonEvent.x, rButtonEvent.y};
      break;
    case GuiEvent::GUI_PRESS:
      moveHandler(rButtonEvent);
      break;
  }
}

void Scrollbar::processEvent(I_Event<lre::LestRenderEngineEvents>& rEvent)
{
}