#include <map>
#include <iostream>

#define GLM_FORCE_CTOR_INIT
#include "input/mouse.hpp"
#include "event/event.hpp"
#include "input/input.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "input/mouseEvent.hpp"
#include "event/applicationEventDispatcher.hpp"

namespace lg
{
  namespace Mouse
  {
    using LestApplicationDispatcher = LestRenderEngine::ApplicationEventDispatcher<LestRenderEngine::LestRenderEngineEvents>;
    static glm::dvec2 gMousePos = glm::dvec2(0, 0);

    //! @brief Callback to receive Mouse Input
    //!
    //! @param[in] pWindow Active Window
    //! @param[in] cX      X position of mouse
    //! @param[in] cY      Y position of mouse
    //!
    //! @return None
    void mousePositionCallback(GLFWwindow *pWindow, const double cX, const double cY)
    {
      LestApplicationDispatcher* dispatcher = 
      static_cast<LestApplicationDispatcher*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
    
      gMousePos.x = cX;
      gMousePos.y = cY;

      if(!dispatcher)
      {
        return;
      }
     
      dispatcher->dispatch(LestRenderEngine::MouseMoveEvent(cX, cY));
      Event tempEvent;
      tempEvent.Type = Event::EventType::MouseMove;
      tempEvent.MousePos.x = cX;
      tempEvent.MousePos.y = cY;
      lg::Input::pushEvent(tempEvent, pWindow);
    }

    void mouseButtonCallback(GLFWwindow *pWindow, const int32_t cButton, const int32_t cAction, const int32_t cMods)
    {
      LestApplicationDispatcher* dispatcher = 
      static_cast<LestApplicationDispatcher*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));

      if(!dispatcher)
      {
        return;
      }

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
          tempEvent.Type = Event::EventType::MouseButtonPress;
          dispatcher->dispatch<LestRenderEngine::MouseButtonPressEvent>(
            LestRenderEngine::MouseButtonPressEvent(cButton, x, y));
          break;
        case GLFW_RELEASE:
          tempEvent.Type = Event::EventType::MouseButtonRelease;
          dispatcher->dispatch<LestRenderEngine::MouseButtonReleaseEvent>(
            LestRenderEngine::MouseButtonReleaseEvent(cButton, x, y));
          break;
      }

      lg::Input::pushEvent(tempEvent, pWindow);
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

    glm::vec2 getMousePosf(const OrthCamera& crCamera)
    {
        const glm::vec4 TOP_LEFT = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(gMousePos.x, gMousePos.y, 0.0f)) *
                              glm::scale(glm::mat4(1.0f), {1.0f, 1.0f, 1.0f});
        return crCamera.getViewProjectionMatrix() * transform * TOP_LEFT;
    }

    glm::vec2 getMousePosf(const std::shared_ptr<RenderTarget>& crpTarget)
    {
      const glm::vec4 TOP_LEFT = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
      const glm::uvec2 WINDOW_SIZE = crpTarget->getWindowSize();
      glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(WINDOW_SIZE.x),
                                              static_cast<float>(WINDOW_SIZE.y),
                                              0.0f, -1.0f, 1.0f);
      glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
      glm::mat4 viewMatrix = glm::inverse(transform);
      glm::mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;

      transform = glm::translate(glm::mat4(1.0f), glm::vec3(gMousePos.x, gMousePos.y, 0.0f)) *
                                 glm::scale(glm::mat4(1.0f), {1.0f, 1.0f, 1.0f});

      auto test = viewProjectionMatrix * transform * TOP_LEFT;
      glm::vec2 temp = glm::vec2((test.x + 1) * (1920.0f / 2.0f), ((test.y * (-1)) + 1 ) * (1080 / 2.0f));
      return temp;
    }
  }
}