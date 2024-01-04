#ifndef INPUT_H
#define INPUT_H

#include "event/event.h"

namespace lg
{
  namespace Input
  {
    void pushEvent(Event& rEvent);
    bool popEvent(Event& rEvent);
  }
}

#endif