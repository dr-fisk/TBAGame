#ifndef MOUSE_H
#define MOUSE_H

#include "Vector.h"
#include "glcommon.h"

namespace lg
{
  namespace Mouse
  {
    void mousePositionCallback(GLFWwindow *pWindow, const double cX, const double cY);
    void mouseButtonCallback(GLFWwindow *pWindow, const int32_t cButton, const int32_t cAction, const int32_t cMods);

    Vector2<int32_t> getMousePosi();
    Vector2<float> getMousePosf();
    bool isMouseButtonPressed(const int32_t cButton);
    int32_t getMouseButtonState(const int32_t cButton);
  }
}

#endif