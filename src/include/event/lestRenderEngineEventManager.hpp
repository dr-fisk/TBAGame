#ifndef LEST_RENDER_EVENT_MANAGER_HPP
#define LEST_RENDER_EVENT_MANAGER_HPP

#include "event/applicationEventDispatcher.hpp"
#include "event/lestRenderEngineEvent.hpp"

namespace LestRenderEngine
{

class LestRenderEngineEventManager
{
  private:
    using LestApplicationDispatcher = LestRenderEngine::ApplicationEventDispatcher<LestRenderEngine::LestRenderEngineEvents>;
  public:
    template<typename T>
    static bool registerToEvent(const EventSubscriber<T>& crSub)
    {
      LestApplicationDispatcher* dispatcher = static_cast<LestApplicationDispatcher*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));

      if(!dispatcher)
      {
        return false;
      }

      dispatcher->attach(crSub);
      return true;
    }

    template<typename T>
    static bool unregisterFromEvent(const EventSubscriber<T>& crSub)
    {
      LestApplicationDispatcher* dispatcher = static_cast<LestApplicationDispatcher*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));

      if(!dispatcher)
      {
        return false;
      }

      return dispatcher->detach(crSub);
    }
};

}

#endif