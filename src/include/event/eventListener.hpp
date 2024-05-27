#ifndef EVENT_LISTENER_HPP
#define EVENT_LISTENER_HPP

#include "event/event.hpp"

class EventListener
{
  public:
    EventListener() = default;
    virtual ~EventListener() = default;
  protected:
};

#endif