#ifndef COMPONENT_EVENT_LISTENER
#define COMPONENT_EVENT_LISTENER

#include "event/event.hpp"

class ComponentEventListener
{
  public:
    ComponentEventListener() = default;
    virtual ~ComponentEventListener() = default;
  protected:
};

#endif