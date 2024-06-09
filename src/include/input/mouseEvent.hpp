#ifndef MOUSE_EVENT_HPP
#define MOUSE_EVENT_HPP

#include "event/I_Event.hpp"
#include "event/lestRenderEngineEvent.hpp"

namespace LestRenderEngine
{

class MouseButtonEvent : public I_Event<LestRenderEngineEvents>
{
  public:
    MouseButtonEvent() = delete;
    virtual ~MouseButtonEvent() = default;
    int32_t getMouseButton() const;
    float getX() const;
    float getY() const;
  protected:
    MouseButtonEvent(const LestRenderEngineEvents cType, const std::string& crMouseEventName,
                     int32_t cMouseButton, const float cX, const float cY);

    int32_t mMouseButton;
    float mX;
    float mY;
};

class MouseButtonPressEvent : public MouseButtonEvent
{
  public:
    MouseButtonPressEvent();
    MouseButtonPressEvent(int32_t cMouseButton, const float cX, const float cY);
    ~MouseButtonPressEvent() = default;
    EVENT_CLASS_SCOPED_TYPE(LestRenderEngineEvents, MOUSE_BUTTON_PRESS)
  private:
};

class MouseButtonReleaseEvent : public MouseButtonEvent
{
  public:
    MouseButtonReleaseEvent();
    MouseButtonReleaseEvent(int32_t cMouseButton, const float cX, const float cY);
    ~MouseButtonReleaseEvent() = default;

    EVENT_CLASS_SCOPED_TYPE(LestRenderEngineEvents, MOUSE_BUTTON_RELEASE)
  private:
};

class MouseMoveEvent : public I_Event<LestRenderEngineEvents>
{
  public:
    MouseMoveEvent();
    MouseMoveEvent(const float cX, const float cY);
    ~MouseMoveEvent() = default;

    float getX() const;
    float getY() const;

    EVENT_CLASS_SCOPED_TYPE(LestRenderEngineEvents, MOUSE_MOVE)
  private:
    float mX;
    float mY;
};

}

#endif