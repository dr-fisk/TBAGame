#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "glcommon.h"

namespace lg
{
  namespace Keyboard
  {
    void keyCallback(GLFWwindow* pWindow, const int32_t cKey, const int32_t cScancode, int32_t cAction,
                     const int32_t cMods);
  }
}

#endif