#include "input/windowEvent.hpp"

namespace lre
{

WindowEvent::WindowEvent(const LestRenderEngineEvents cEventType, const int32_t cWidth, const int32_t cHeight) :
  I_Event(cEventType), mWidth(cWidth), mHeight(cHeight)
{
}

int32_t WindowEvent::getHeight() const
{
  return mHeight;
}

int32_t WindowEvent::getWidth() const
{
  return mWidth;
}

WindowEvent& WindowEvent::operator=(const WindowEvent& rhs)
{
  if(this == &rhs)
  {
    return *this;
  }

  mHeight = rhs.getHeight();
  mWidth = rhs.getWidth();

  return *this;
}

WindowResizeEvent::WindowResizeEvent() : WindowEvent(LestRenderEngineEvents::WINDOW_RESIZE, 0, 0)
 {
 }

WindowResizeEvent::WindowResizeEvent(const int32_t cWidth, const int32_t cHeight) :
  WindowEvent(LestRenderEngineEvents::WINDOW_RESIZE, cWidth, cHeight)
{
}

}