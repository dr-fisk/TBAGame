#include <queue>

#include "input/input.h"

namespace lg
{
  namespace Input
  {
  static std::queue<Event> gEvents;
  const int MAX_QUEUE_SIZE = 512;

  void pushEvent(Event& rEvent)
  {
    if(MAX_QUEUE_SIZE == gEvents.size())
    {
      gEvents.pop();
    }

    gEvents.push(rEvent);
  }

  bool popEvent(Event& rEvent)
  {
    if(gEvents.empty())
    {
      return false;
    }

    rEvent = gEvents.front();
    gEvents.pop();
    return true;
  }
  }
}