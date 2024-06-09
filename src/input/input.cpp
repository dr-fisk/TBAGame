#include <queue>
#include <unordered_map>
#include <mutex>

#include "input/input.hpp"

namespace lg
{
  namespace Input
  {
  static std::unordered_map<GLFWwindow*, std::queue<Event>> gContextEventMap;
  static std::mutex gMapMutex;
  const int MAX_QUEUE_SIZE = 512;

  void pushEvent(const Event& crEvent, GLFWwindow* pContext)
  {
    gMapMutex.lock();
    std::queue<Event>* eventQueue = &gContextEventMap.at(pContext);
  
    if(MAX_QUEUE_SIZE == eventQueue->size())
    {
      eventQueue->pop();
    }

    eventQueue->push(crEvent);
    gMapMutex.unlock();
  }

  bool popEvent(Event& rEvent, GLFWwindow* pContext)
  {
    gMapMutex.lock();
    std::queue<Event>* eventQueue = &gContextEventMap.at(pContext);

    if(eventQueue->empty())
    {
      gMapMutex.unlock();
      return false;
    }

    rEvent = eventQueue->front();
    eventQueue->pop();
    gMapMutex.unlock();
    return true;
  }

  void registerContext(GLFWwindow* pContext)
  {
    gMapMutex.lock();
    gContextEventMap[pContext] = std::queue<Event>();
    gMapMutex.unlock();
  }

  void unregisterContext(GLFWwindow* pContext)
  {
    gMapMutex.lock();
    gContextEventMap.erase(pContext);
    gMapMutex.unlock();
  }
  }
}