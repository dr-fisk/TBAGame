#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "glcommon.hpp"

namespace lg
{
  namespace Window
  {
    void windowResizeCallback(GLFWwindow *pWindow, const int32_t cWidth, const int32_t cHeight);
  }
}

#endif