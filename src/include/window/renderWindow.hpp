#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include <memory>
#include <mutex>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window/renderTarget.hpp"
#include "event/event.hpp"

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
      void draw(const uint64_t cCount);
      void setActive();
      void initWindow();
      GLFWwindow *getGlWindow();
      bool pollEvent(Event& rEvent);
      const glm::uvec2& getWindowSize();
      void setWindowTitle(const std::string& crTitle);

      std::shared_ptr<RenderWindow> createSharedWindow();
    private:
      void setCallbacks();
      void boundCoords(GLfloat *pLeft, GLfloat *pWidth, GLfloat *pTop, GLfloat *pHeight);

      glm::uvec2 mWindowSize;
      std::string mTitle;
      GLFWwindow *mpWindow;
      std::mutex mDataAccesMutex;
      static bool msFirstInit;
};

#endif