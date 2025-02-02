#include "input/keyboard.hpp"
#include "input/keyboardEvent.hpp"
#include "event/applicationEventDispatcher.hpp"

#include <cstdint>

namespace lg
{
  namespace Keyboard
  {
    using LestApplicationDispatcher = LestRenderEngine::ApplicationEventDispatcher<LestRenderEngine::LestRenderEngineEvents>;

    void keyCallback(GLFWwindow* pWindow, const int32_t cKey, const int32_t cScancode, int32_t cAction,
                     const int32_t cMods)
    {
      LestApplicationDispatcher* dispatcher = 
      static_cast<LestApplicationDispatcher*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));

      if(!dispatcher)
      {
        return;
      }

      switch(cAction)
      {
        case GLFW_PRESS:
        {
          LestRenderEngine::KeyboardPressEvent keyPressEvent(cKey, cScancode, cAction, cMods);
          dispatcher->dispatch<LestRenderEngine::KeyboardPressEvent>(keyPressEvent);
          break;
        }
        case GLFW_REPEAT:
          break;
        case GLFW_RELEASE:
        {
          LestRenderEngine::KeyboardReleaseEvent keyReleaseEvent(cKey, cScancode, cAction, cMods);
          dispatcher->dispatch<LestRenderEngine::KeyboardReleaseEvent>(keyReleaseEvent);
          break;
        }
      }
    }
  }
}