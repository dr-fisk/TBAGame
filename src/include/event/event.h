#ifndef EVENT_H
#define EVENT_H

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

    enum EventType
    {
      MouseButtonPress,
      MouseButtonRelease,
      MouseMove,
      KeyPress,
      KeyRelease
    };

    EventType Type;

    union
    {
      MouseButtonEvent MouseButton;
      KeyEvent Key;
      MouseMoveEvent MousePos;
    };
};

#endif