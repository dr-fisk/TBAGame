#include <map>
#include <iostream>

#include "window/mouse.h"
#include "event/event.h"
#include "input/input.h"

namespace lg
{
  namespace Mouse
  {
    static glm::dvec2 gMousePos = glm::dvec2(0, 0);

    //! @brief Callback to receive Mouse Input
    //! @param pWindow Active Window
    //! @param cX      X position of mouse
    //! @param cY      Y position of mouse
    void mousePositionCallback(GLFWwindow *pWindow, const double cX, const double cY)
    {
      gMousePos.x = cX;
      gMousePos.y = cY;

      Event tempEvent;
      tempEvent.Type = Event::MouseMove;
      tempEvent.MousePos.x = cX;
      tempEvent.MousePos.y = cY;
      lg::Input::pushEvent(tempEvent);
    }

    void mouseButtonCallback(GLFWwindow *pWindow, const int32_t cButton, const int32_t cAction, const int32_t cMods)
    {
      Event tempEvent;
      double x = 0;
      double y = 0;

      tempEvent.MouseButton.Button = cButton;
      glfwGetCursorPos(pWindow, &x, &y);
      tempEvent.MouseButton.x = x;
      tempEvent.MouseButton.y = y;


      switch(cAction)
      {
        case GLFW_PRESS:
          tempEvent.Type = Event::MouseButtonPress;
          break;
        case GLFW_RELEASE:
          tempEvent.Type = Event::MouseButtonRelease;
          break;
      }

      lg::Input::pushEvent(tempEvent);
    }

    //! @brief Gets the current mouse position
    //!
    //! @return Mouse Position
    glm::ivec2 getMousePosi()
    {
      return {static_cast<int32_t>(gMousePos.x), static_cast<int32_t>(gMousePos.y)};
    }

    //! @brief Gets the current mouse position
    //!
    //! @return Mouse Position
    glm::vec2 getMousePosf()
    {
      return {static_cast<float>(gMousePos.x), static_cast<float>(gMousePos.y)};
    }
  }
}