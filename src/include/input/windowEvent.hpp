#ifndef WINDOW_EVENT_HPP
#define WINDOW_EVENT_HPP

#include "event/I_Event.hpp"
#include "event/lestRenderEngineEvent.hpp"

namespace lre
{

class WindowEvent : public I_Event<LestRenderEngineEvents>
{
  public:
    WindowEvent() = delete;
    virtual ~WindowEvent() = default;
    int32_t getHeight() const;
    int32_t getWidth() const;
    WindowEvent& operator=(const WindowEvent& rhs);
  protected:
      WindowEvent(const LestRenderEngineEvents cEventType, const int32_t cWidth, const int32_t cHeight);

    int32_t mWidth;
    int32_t mHeight;
};

class WindowResizeEvent : public WindowEvent
{
  public:
    WindowResizeEvent();
    WindowResizeEvent(const int32_t cWidth, const int32_t cHeight);
    ~WindowResizeEvent() = default;
    EVENT_CLASS_SCOPED_TYPE(LestRenderEngineEvents, WINDOW_RESIZE)
};

}

#endif