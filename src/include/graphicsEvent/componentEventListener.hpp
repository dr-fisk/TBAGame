#ifndef COMPONENT_EVENT_LISTENER_HPP
#define COMPONENT_EVENT_LISTENER_HPP

#include "event/event.hpp"

class ComponentEventListener
{
  public:
    ComponentEventListener() = default;
    virtual ~ComponentEventListener() = default;
  protected:
};

#endif