#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <cstdint>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lg
{
  namespace Keyboard
  {
    void keyCallback(GLFWwindow* pWindow, const int32_t cKey, const int32_t cScancode, int32_t cAction,
                     const int32_t cMods);
  }
}

#endif