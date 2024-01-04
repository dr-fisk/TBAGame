#ifndef MOUSE_H
#define MOUSE_H

#include "Vector.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lg
{
  namespace Mouse
  {
    void mousePositionCallback(GLFWwindow *pWindow, const double cX, const double cY);
    void mouseButtonCallback(GLFWwindow *pWindow, const int32_t cButton, const int32_t cAction, const int32_t cMods);

    Vector2<int32_t> getMousePosi();
    Vector2<float> getMousePosf();
  }
}

#endif