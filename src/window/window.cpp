#include "window/window.hpp"
#include "input/input.hpp"
#include "input/windowEvent.hpp"
#include "event/applicationEventDispatcher.hpp"

namespace lg
{
  namespace Window
  {
    using LestApplicationDispatcher = lre::ApplicationEventDispatcher<lre::LestRenderEngineEvents>;

    WindowView gView;

    void windowResizeCallback(GLFWwindow *pWindow, const int32_t cWidth, const int32_t cHeight)
    {
      LestApplicationDispatcher* dispatcher = 
      static_cast<LestApplicationDispatcher*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));

      if(!dispatcher)
      {
        return;
      }

      int32_t view[4] = {};
      glGetIntegerv(GL_VIEWPORT, view);      

      gView.x = view[0];
      gView.y = view[1];
      gView.WindowWidth = cWidth;
      gView.WindowHeight = cHeight;
      lre::WindowResizeEvent resizeEvent(cWidth, cHeight);
      dispatcher->dispatch<lre::WindowResizeEvent>(resizeEvent);
    }
  
    const WindowView& getView()
    {
      return gView;
    }
  }
}