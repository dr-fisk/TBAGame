#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "glcommon.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lg
{
  namespace Window
  {
    struct WindowView
    {
      float WindowWidth;
      float WindowHeight;
      float x;
      float y;
    };

    void windowResizeCallback(GLFWwindow *pWindow, const int32_t cWidth, const int32_t cHeight);
    const WindowView& getView();
    void windowFocusCallback(GLFWwindow* pWindow, const int cFocus);
  }
}

#endif