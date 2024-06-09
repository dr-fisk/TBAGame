#include "input/mouseEvent.hpp"

namespace LestRenderEngine
{

MouseButtonEvent::MouseButtonEvent(const LestRenderEngineEvents cType, const std::string& crMouseEventName,
  int32_t cMouseButton, const float cX, const float cY) : I_Event(cType, crMouseEventName),
  mMouseButton(cMouseButton), mX(cX), mY(cY)
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

MouseButtonPressEvent::MouseButtonPressEvent()
: MouseButtonEvent(LestRenderEngineEvents::MOUSE_BUTTON_PRESS, "MouseButtonPressEvent", 0, 0, 0)
{
}

MouseButtonPressEvent::MouseButtonPressEvent(int32_t cMouseButton, const float cX, const float cY)
: MouseButtonEvent(LestRenderEngineEvents::MOUSE_BUTTON_PRESS, "MouseButtonPressEvent", cMouseButton, cX, cY)
{
}

MouseButtonReleaseEvent::MouseButtonReleaseEvent()
 : MouseButtonEvent(LestRenderEngineEvents::MOUSE_BUTTON_RELEASE, "MouseButtonReleaseEvent", 0, 0, 0)
{
}

MouseButtonReleaseEvent::MouseButtonReleaseEvent(int32_t cMouseButton, const float cX, const float cY)
: MouseButtonEvent(LestRenderEngineEvents::MOUSE_BUTTON_RELEASE, "MouseButtonReleaseEvent", cMouseButton, cX, cY)
{
}

MouseMoveEvent::MouseMoveEvent() : I_Event(LestRenderEngineEvents::MOUSE_MOVE, "MouseMoveEvent"), mX(0), mY(0)
{
}

MouseMoveEvent::MouseMoveEvent(const float cX, const float cY)
: I_Event(LestRenderEngineEvents::MOUSE_MOVE, "MouseMoveEvent"), mX(cX), mY(cY)
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