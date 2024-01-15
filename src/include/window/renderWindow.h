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
      void clear();
      void display();
      void draw(const uint64_t cCount);
      void setActive();
      void initWindow();
      void destroyWindow();
      void enableBlend();
      void disableBlend();
      GLFWwindow *getGlWindow();
      bool pollEvent(Event& rEvent);

      // Make this a RenderWindow Object
      std::shared_ptr<RenderWindow> createSharedWindow();

    private:
      void setCallbacks();
      void boundCoords(GLfloat *pLeft, GLfloat *pWidth, GLfloat *pTop, GLfloat *pHeight);

      uint32_t mWdwHeight;
      uint32_t mWdwWidth;
      int32_t mWindowId;
      std::string mTitle;
      GLFWwindow *mpWindow;
      static bool msIsInitialized;
      static bool msCallbacksInitialized;
      static int32_t msWindowId;
      static int32_t msActiveWindowId;
};

#endif