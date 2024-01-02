#include <map>
#include "window/mouse.h"

namespace lg
{
  namespace Mouse
  {
    static Vector2<double> gMousePos = Vector2<double>(0, 0);
    static std::map<int32_t, int32_t> MouseButtonStates = {{GLFW_MOUSE_BUTTON_LEFT, GLFW_KEY_UNKNOWN},
                                                           {GLFW_MOUSE_BUTTON_RIGHT, GLFW_KEY_UNKNOWN},
                                                           {GLFW_MOUSE_BUTTON_MIDDLE, GLFW_KEY_UNKNOWN},
                                                           {GLFW_MOUSE_BUTTON_1, GLFW_KEY_UNKNOWN},
                                                           {GLFW_MOUSE_BUTTON_2, GLFW_KEY_UNKNOWN},
                                                           {GLFW_MOUSE_BUTTON_3, GLFW_KEY_UNKNOWN},
                                                           {GLFW_MOUSE_BUTTON_4, GLFW_KEY_UNKNOWN},
                                                           {GLFW_MOUSE_BUTTON_5, GLFW_KEY_UNKNOWN},
                                                           {GLFW_MOUSE_BUTTON_6, GLFW_KEY_UNKNOWN},
                                                           {GLFW_MOUSE_BUTTON_7, GLFW_KEY_UNKNOWN},
                                                           {GLFW_MOUSE_BUTTON_8, GLFW_KEY_UNKNOWN}};

    //! @brief Callback to receive Mouse Input
    //! @param pWindow Active Window
    //! @param cX      X position of mouse
    //! @param cY      Y position of mouse
    void mousePositionCallback(GLFWwindow *pWindow, const double cX, const double cY)
    {
      gMousePos.x = cX;
      gMousePos.y = cY;
    }

    void mouseButtonCallback(GLFWwindow *pWindow, const int32_t cButton, const int32_t cAction, const int32_t cMods)
    {
      MouseButtonStates[cButton] = cAction;
    }

    //! @brief Gets the current mouse position
    //!
    //! @return Mouse Position
    Vector2<int32_t> getMousePosi()
    {
      return {static_cast<int32_t>(gMousePos.x), static_cast<int32_t>(gMousePos.y)};
    }

    //! @brief Gets the current mouse position
    //!
    //! @return Mouse Position
    Vector2<float> getMousePosf()
    {
      return {static_cast<float>(gMousePos.x), static_cast<float>(gMousePos.y)};
    }

    //! @brief Returns if Mouse Button is Pressed
    //!        Note: Does not return true if Button is held down
    //!
    //! @param cButton Mouse button to check state
    //!
    //! @return true if Mouse button is presesd, false otherwise
    bool isMouseButtonPressed(const int32_t cButton)
    {
      return GLFW_PRESS == MouseButtonStates.at(cButton);
    }

    //! @brief Returns the Mouse Button State
    //!
    //! @param cButton Mouse Button State to grab
    //!
    //! @return Mouse Button State 
    int32_t getMouseButtonState(const int32_t cButton)
    {
      return MouseButtonStates.at(cButton);
    }
  }
}