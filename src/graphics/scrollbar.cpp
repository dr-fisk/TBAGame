#include <iostream>

#include "graphics/scrollbar.hpp"

//! @brief 
//! @param prRenderEngine 
//! @param crPos 
//! @param crSize
//!
//! @return None
Scrollbar::Scrollbar(std::shared_ptr<RenderEngine>& prRenderEngine, const glm::vec2& crPos,
                     const glm::vec2& crSize)
{
  mScrollbarButton = std::make_shared<Button<>>(prRenderEngine, crPos, crSize);
  mState = DEFAULT_STATE;
}

void Scrollbar::setDefaultTexture(const std::shared_ptr<TextureResource>& crpTexture)
{
  mScrollbarButton->setDefaultTexture(crpTexture);
}

void Scrollbar::setHoverTexture(const std::shared_ptr<TextureResource>& crpTexture)
{
  mScrollbarButton->setHoverTexture(crpTexture);
}

void Scrollbar::setPressedTexture(const std::shared_ptr<TextureResource>& crpTexture)
{
  mScrollbarButton->setPressedTexture(crpTexture);
}

void Scrollbar::setDefaultColor(const lg::Color& crColor)
{
  mScrollbarButton->setDefaultColor(crColor);
}

void Scrollbar::setHoverColor(const lg::Color& crColor)
{
  mScrollbarButton->setHoverColor(crColor);
}

void Scrollbar::setPressedColor(const lg::Color& crColor)
{
  mScrollbarButton->setPressedColor(crColor);
}

void Scrollbar::mousePressEvent(const Event& crEvent)
{
  if(GLFW_MOUSE_BUTTON_LEFT  == crEvent.MouseButton.Button && mScrollbarButton->isPressed())
  {
    mPrevMousey = crEvent.MouseButton.y;
    mState = SCROLL_STATE;
  }
}

void Scrollbar::mouseReleaseEvent(const Event& crEvent)
{
  if(GLFW_MOUSE_BUTTON_LEFT  == crEvent.MouseButton.Button)
  {
    mState = DEFAULT_STATE;
  }
}

void Scrollbar::mouseMoveEvent(const Event& crEvent)
{
  switch(mState)
  {
    case SCROLL_STATE:
      if(!mScrollbarButton->isPressed())
      {
        mState = DEFAULT_STATE;
      }
      // Move button by the current mouse y pos - the prev mouse y position then set the prev mouse y position to the
      // current y position
      else
      {
        mScrollbarButton->movePos(glm::vec2(0, crEvent.MousePos.y - mPrevMousey));
        mPrevMousey = crEvent.MousePos.y;
      }
      break;
    default:
      break;
  }
}

void Scrollbar::update(const Event& crEvent)
{
  mScrollbarButton->clicked(crEvent);

  switch(crEvent.Type)
  {
    case Event::MouseMove:
      mouseMoveEvent(crEvent);
      break;
    case Event::MouseButtonPress:
      mousePressEvent(crEvent);
      break;
    case Event::MouseButtonRelease:
      mouseReleaseEvent(crEvent);
      break;
  }
}

void Scrollbar::setPressedPadding(const glm::vec2& crPadding)
{
  mScrollbarButton->setPressedPadding(crPadding);
}

void Scrollbar::draw()
{
  mScrollbarButton->draw();
}