#ifndef INPUT_HPP
#define INPUT_HPP

#include "event/event.hpp"

namespace lg
{
  namespace Input
  {
    void pushEvent(Event& rEvent);
    bool popEvent(Event& rEvent);
  }
}

#endif