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
          dispatcher->dispatch<LestRenderEngine::KeyboardPressEvent>(LestRenderEngine::KeyboardPressEvent(
            cKey, cScancode, cAction, cMods));
          break;
        }
        case GLFW_REPEAT:
          break;
        case GLFW_RELEASE:
        {
          dispatcher->dispatch<LestRenderEngine::KeyboardReleaseEvent>(LestRenderEngine::KeyboardReleaseEvent(
            cKey, cScancode, cAction, cMods));
          break;
        }
      }
    }
  }
}