#ifndef WINDOW_EVENT_HPP
#define WINDOW_EVENT_HPP

#include "event/I_Event.hpp"
#include "event/lestRenderEngineEvent.hpp"

namespace LestRenderEngine
{

class WindowEvent : public I_Event<LestRenderEngineEvents>
{
  public:
    WindowEvent() = delete;
    virtual ~WindowEvent() = default;
  protected:
      WindowEvent(const LestRenderEngineEvents cType, const std::string& crWindowEventName, const int32_t cWidth,
                const int32_t cHeight);

    int32_t mWidth;
    int32_t mHeight;
};

class WindowResizeEvent : public WindowEvent
{
  public:
    WindowResizeEvent();
    WindowResizeEvent(const int32_t cWidth, const int32_t cHeight);
    ~WindowResizeEvent() = default;
};

}

#endif