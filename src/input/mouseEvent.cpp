#include "input/mouseEvent.hpp"

namespace lre
{

MouseButtonEvent::MouseButtonEvent(const LestRenderEngineEvents cEventType, int32_t cMouseButton, const float cX,
  const float cY) : I_Event(cEventType), mMouseButton(cMouseButton), mX(cX), mY(cY)
{

}

int32_t MouseButtonEvent::getMouseButton() const
{
  return mMouseButton;
}

float MouseButtonEvent::getX() const
{
  return mX;
}

float MouseButtonEvent::getY() const
{
  return mY;
}

MouseButtonEvent& MouseButtonEvent::operator=(const MouseButtonEvent& rhs)
{
  if (this == &rhs)
  {
    return *this;
  }

  mX = rhs.getX();
  mY = rhs.getY();
  mMouseButton = rhs.getMouseButton();

  return *this;
}

MouseButtonPressEvent::MouseButtonPressEvent()
: MouseButtonEvent(LestRenderEngineEvents::MOUSE_BUTTON_PRESS, 0, 0, 0)
{
}

MouseButtonPressEvent::MouseButtonPressEvent(int32_t cMouseButton, const float cX, const float cY)
: MouseButtonEvent(LestRenderEngineEvents::MOUSE_BUTTON_PRESS, cMouseButton, cX, cY)
{
}

MouseButtonReleaseEvent::MouseButtonReleaseEvent()
 : MouseButtonEvent(LestRenderEngineEvents::MOUSE_BUTTON_RELEASE, 0, 0, 0)
{
}

MouseButtonReleaseEvent::MouseButtonReleaseEvent(int32_t cMouseButton, const float cX, const float cY)
: MouseButtonEvent(LestRenderEngineEvents::MOUSE_BUTTON_RELEASE, cMouseButton, cX, cY)
{
}

MouseMoveEvent::MouseMoveEvent() : I_Event(LestRenderEngineEvents::MOUSE_MOVE), mX(0), mY(0)
{
}

MouseMoveEvent::MouseMoveEvent(const float cX, const float cY) : I_Event(LestRenderEngineEvents::MOUSE_MOVE),
 mX(cX), mY(cY)
{
}

float MouseMoveEvent::getX() const
{
  return mX;
}

float MouseMoveEvent::getY() const
{
  return mY;
}

}