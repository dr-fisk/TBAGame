#ifndef MOUSE_EVENT_HPP
#define MOUSE_EVENT_HPP

#include "event/I_Event.hpp"
#include "event/lestRenderEngineEvent.hpp"

namespace lre
{

class MouseButtonEvent : public I_Event<LestRenderEngineEvents>
{
  public:
    MouseButtonEvent() = default;
    virtual ~MouseButtonEvent() = default;
    int32_t getMouseButton() const;
    float getX() const;
    float getY() const;
    float getXWorldSpace() const;
    float getYWorldSpace() const;
    MouseButtonEvent& operator=(const MouseButtonEvent& rhs);
    MouseButtonEvent(const MouseButtonEvent& crMouseButtonEvent);
  protected:
    MouseButtonEvent(const LestRenderEngineEvents cEventType, int32_t cMouseButton, const float cX, const float cY);

    int32_t mMouseButton = 0;
    float mX = 0;
    float mY = 0;
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
    float getXWorldSpace() const;
    float getYWorldSpace() const;
    MouseMoveEvent& operator=(const MouseMoveEvent& rhs);
    MouseMoveEvent(const MouseMoveEvent &crMouseMoveEvent);
    EVENT_CLASS_SCOPED_TYPE(LestRenderEngineEvents, MOUSE_MOVE)
  private:
    float mX = 0;
    float mY = 0;
};

}

#endif