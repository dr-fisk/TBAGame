#include "window/window.hpp"
#include "input/input.hpp"

namespace lg
{
  namespace Window
  {
    void windowResizeCallback(GLFWwindow *pWindow, const int32_t cWidth, const int32_t cHeight)
    {
      Event tempEvent;
      int32_t view[4] = {};
      glGetIntegerv(GL_VIEWPORT, view);

      gView.x = view[0];
      gView.y = view[1];
      gView.WindowWidth = cWidth;
      gView.WindowHeight = cHeight;

      tempEvent.WindowView.x = gView.x;
      tempEvent.WindowView.y = gView.y;
      tempEvent.WindowView.Width = gView.WindowWidth;
      tempEvent.WindowView.Height = gView.WindowHeight;
      lg::Input::pushEvent(tempEvent);
    }
  }
}