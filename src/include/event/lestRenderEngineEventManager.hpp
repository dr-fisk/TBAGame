#ifndef LEST_RENDER_EVENT_MANAGER_HPP
#define LEST_RENDER_EVENT_MANAGER_HPP

#include "event/applicationEventDispatcher.hpp"
#include "event/lestRenderEngineEvent.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define SLOT(sub, func){ \
  sub.setCallback(BIND_EVENT_FN(func));\
  lre::LestRenderEngineEventManager::registerToEvent(sub);}

namespace lre
{

class LestRenderEngineEventManager
{
  private:
    using LestApplicationDispatcher = lre::ApplicationEventDispatcher<lre::LestRenderEngineEvents>;
  public:
    template<typename T>
    static bool registerToEvent(EventSubscriber<T>& crSub)
    {
      LestApplicationDispatcher* dispatcher = static_cast<LestApplicationDispatcher*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));

      if(!dispatcher)
      {
        return false;
      }

      crSub.setUnregisterFunc(LestRenderEngineEventManager::unregisterFromEvent<T>);
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

      dispatcher->detach(crSub);
      return true;
    }
};

}

#endif