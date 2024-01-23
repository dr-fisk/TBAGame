#ifndef WINDOW_H
#define WINDOW_H

#include "glcommon.h"

namespace lg
{
  namespace Window
  {
    void windowResizeCallback(GLFWwindow *pWindow, const int32_t cWidth, const int32_t cHeight);
  }
}

#endif