#include "window/window.hpp"
#include "input/input.hpp"
#include "input/windowEvent.hpp"
#include "event/eventDispatcher.hpp"

namespace lg
{
  namespace Window
  {
    WindowView gView;

    void windowResizeCallback(GLFWwindow *pWindow, const int32_t cWidth, const int32_t cHeight)
    {
      // EventDispatcher<LestRenderEngine::LestRenderEngineEvents>* dispatcher = 
      // static_cast<EventDispatcher<LestRenderEngine::LestRenderEngineEvents>*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));

      // if(!dispatcher)
      // {
      //   return;
      // }

      Event tempEvent;
      tempEvent.Type = Event::EventType::WindowResize;
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

      // dispatcher->notify<LestRenderEngine::WindowResizeEvent>(LestRenderEngine::WindowResizeEvent(cWidth, cHeight));
      lg::Input::pushEvent(tempEvent, pWindow);
    }
  
    const WindowView& getView()
    {
      return gView;
    }
  }
}