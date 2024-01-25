#ifndef EVENT_HPP
#define EVENT_HPP

#include <cstdint>

class Event
{
  public:
    Event() = default;
    ~Event() = default;

    struct MouseButtonEvent
    {
      int32_t Button;
      float x;
      float y;
    };

    struct KeyEvent
    {
      int32_t KeyCode;
    };

    struct MouseMoveEvent
    {
      float x;
      float y;
    };

    struct WindowResizeEvent
    {
      float x;
      float y;
      float Width;
      float Height;
    };

    enum EventType
    {
      MouseButtonPress,
      MouseButtonRelease,
      MouseMove,
      KeyPress,
      KeyRelease,
      WindowResize
    };

    EventType Type;

    union
    {
      MouseButtonEvent MouseButton;
      KeyEvent Key;
      MouseMoveEvent MousePos;
      WindowResizeEvent WindowView;
    };
};

#endif