#include "input/windowEvent.hpp"

namespace LestRenderEngine
{

WindowEvent::WindowEvent(const LestRenderEngineEvents cType, const std::string& crWindowEventName, const int32_t cWidth,
                         const int32_t cHeight) : I_Event(cType, crWindowEventName), mWidth(cWidth), mHeight(cHeight)
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


WindowResizeEvent::WindowResizeEvent()
 : WindowEvent(LestRenderEngineEvents::WINDOW_RESIZE, "WindowResizeEvent", 0, 0)
 {
 }

WindowResizeEvent::WindowResizeEvent(const int32_t cWidth, const int32_t cHeight)
 : WindowEvent(LestRenderEngineEvents::WINDOW_RESIZE, "WindowResizeEvent", cWidth, cHeight)
{
}

}