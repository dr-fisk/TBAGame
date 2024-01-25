#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "glcommon.hpp"

namespace lg
{
  namespace Keyboard
  {
    void keyCallback(GLFWwindow* pWindow, const int32_t cKey, const int32_t cScancode, int32_t cAction,
                     const int32_t cMods);
  }
}

#endif