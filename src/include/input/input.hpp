#ifndef INPUT_HPP
#define INPUT_HPP

#include "event/event.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lg
{
  namespace Input
  {
    void pushEvent(const Event& crEvent, GLFWwindow* pContext);
    bool popEvent(Event& rEvent, GLFWwindow* pContext);
    void registerContext(GLFWwindow* pContext);
    void unregisterContext(GLFWwindow* pContext);
  }
}

#endif