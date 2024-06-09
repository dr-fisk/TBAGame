#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include <memory>
#include <mutex>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window/renderTarget.hpp"
#include "event/event.hpp"
#include "event/applicationEventDispatcher.hpp"
#include "event/lestRenderEngineEvent.hpp"

class RenderWindow : public RenderTarget
{
    public:
      RenderWindow(const uint32_t cWindowWidth, const uint32_t cWindowHeight, const char *cpTitle,
                   GLFWwindow *pWindow=nullptr);
      ~RenderWindow();
      bool isOpen();
      uint32_t getWindowWidth();
      uint32_t getWindowHeight();
      void display();
      void setActive();
      void initWindow();
      GLFWwindow *getGlWindow();
      bool pollEvent(Event& rEvent);
      const glm::uvec2& getWindowSize();
      void setWindowTitle(const std::string& crTitle);
      std::shared_ptr<RenderWindow> createSharedWindow();
    private:
      void setCallbacks();

      glm::uvec2 mWindowSize;
      std::string mTitle;
      GLFWwindow *mpWindow;
      std::mutex mDataAccesMutex;
      LestRenderEngine::ApplicationEventDispatcher<LestRenderEngine::LestRenderEngineEvents> mEventDispatcher;
      static bool msFirstInit;
};

#endif