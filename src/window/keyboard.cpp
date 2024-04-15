#include "window/keyboard.hpp"
#include "input/input.hpp"

#include <cstdint>

namespace lg
{
  namespace Keyboard
  {
    void keyCallback(GLFWwindow* pWindow, const int32_t cKey, const int32_t cScancode, int32_t cAction,
                     const int32_t cMods)
    {
      Event tempEvent;

      switch(cAction)
      {
        case GLFW_PRESS:
          tempEvent.Type = Event::KeyPress;
          tempEvent.Key.KeyCode = cKey;
          lg::Input::pushEvent(tempEvent);
          break;
        case GLFW_REPEAT:
          break;
        case GLFW_RELEASE:
          tempEvent.Type = Event::KeyRelease;
          tempEvent.Key.KeyCode = cKey;
          lg::Input::pushEvent(tempEvent);
          break;
      }
    }
  }
}