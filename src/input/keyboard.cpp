#include "input/keyboard.hpp"
#include "input/keyboardEvent.hpp"
#include "event/applicationEventDispatcher.hpp"

#include <cstdint>

namespace lg
{
  namespace Keyboard
  {
    using LestApplicationDispatcher = lre::ApplicationEventDispatcher<lre::LestRenderEngineEvents>;

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
          lre::KeyboardPressEvent keyPressEvent(cKey, cScancode, cAction, cMods);
          dispatcher->dispatch<lre::KeyboardPressEvent>(keyPressEvent);
          break;
        }
        case GLFW_REPEAT:
          break;
        case GLFW_RELEASE:
        {
          lre::KeyboardReleaseEvent keyReleaseEvent(cKey, cScancode, cAction, cMods);
          dispatcher->dispatch<lre::KeyboardReleaseEvent>(keyReleaseEvent);
          break;
        }
      }
    }
  }
}