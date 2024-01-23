#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <memory>

#include "window/renderTarget.h"
#include "glcommon.h"
#include "event/event.h"

class RenderWindow : public RenderTarget
{
    public:
      RenderWindow(const uint32_t cWindowWidth, const uint32_t cWindowHeight, const char *cpTitle,
                   GLFWwindow *pWindow=nullptr);
      ~RenderWindow() = default;
      bool isOpen();
      uint32_t getWindowWidth();
      uint32_t getWindowHeight();
      void display();
      void draw(const uint64_t cCount);
      void setActive();
      void initWindow();
      void destroyWindow();
      GLFWwindow *getGlWindow();
      bool pollEvent(Event& rEvent);
      const glm::uvec2& getWindowSize();

      // Make this a RenderWindow Object
      std::shared_ptr<RenderWindow> createSharedWindow();

    private:
      void setCallbacks();
      void boundCoords(GLfloat *pLeft, GLfloat *pWidth, GLfloat *pTop, GLfloat *pHeight);

      glm::uvec2 mWindowSize;
      int32_t mWindowId;
      std::string mTitle;
      GLFWwindow *mpWindow;
      static bool msCallbacksInitialized;
      static int32_t msWindowId;
      static int32_t msActiveWindowId;
};

#endif