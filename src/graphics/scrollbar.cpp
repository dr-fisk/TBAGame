#include <iostream>

#include "graphics/scrollbar.hpp"

Scrollbar::Scrollbar(const Box<glm::vec2>& crBox)
{
  mScrollbarButton = std::make_shared<Button<>>(crBox);
  mState = DEFAULT_STATE;
}

Scrollbar& Scrollbar::setDefaultTexture(const std::shared_ptr<Texture2D>& crpTexture)
{
  mScrollbarButton->setDefaultTexture(crpTexture);
  return *this;
}

Scrollbar& Scrollbar::setHoverTexture(const std::shared_ptr<Texture2D>& crpTexture)
{
  mScrollbarButton->setHoverTexture(crpTexture);
  return *this;
}

Scrollbar& Scrollbar::setPressedTexture(const std::shared_ptr<Texture2D>& crpTexture)
{
  mScrollbarButton->setPressedTexture(crpTexture);
  return *this;
}

Scrollbar& Scrollbar::setDefaultColor(const lg::Color& crColor)
{
  mScrollbarButton->setDefaultColor(crColor);
  return *this;
}

Scrollbar& Scrollbar::setHoverColor(const lg::Color& crColor)
{
  mScrollbarButton->setHoverColor(crColor);
  return *this;
}

Scrollbar& Scrollbar::setPressedColor(const lg::Color& crColor)
{
  mScrollbarButton->setPressedColor(crColor);
  return *this;
}

Scrollbar& Scrollbar::setButton(std::shared_ptr<Button<>>& crpButton)
{
  mScrollbarButton = crpButton;
  return *this;
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

Scrollbar& Scrollbar::setPressedPadding(const glm::vec2& crPadding)
{
  mScrollbarButton->setPressedPadding(crPadding);
  return *this;
}

void Scrollbar::draw()
{
  mScrollbarButton->draw();
}