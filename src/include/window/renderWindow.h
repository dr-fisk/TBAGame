#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "window/renderTarget.h"

class RenderWindow : public RenderTarget
{
    public:
      RenderWindow(const uint32_t cWindowWidth, const uint32_t cWindowHeight, const char *cpTitle, GLFWwindow *pWindow=NULL);
      ~RenderWindow() = default;
      bool isOpen();
      uint32_t getWindowWidth();
      uint32_t getWindowHeight();
      void clear();
      void display();
      void draw(const uint64_t cCount);
      void setKeyCallback();
      bool isKeyPressed(const int cKey);
      static void keyCallback(GLFWwindow *pWindow, const int32_t cKey, const int32_t cScanCode, const int32_t cAction,
                              const int32_t cMods);
      static int32_t getKeyPress();
      void setActive();
      void initWindow();
      void destroyWindow();
      void enableBlend();
      void disableBlend();
      GLFWwindow *getGlWindow();

    private:
      uint32_t mWdwHeight;
      uint32_t mWdwWidth;
      std::string mTitle;
      GLFWwindow *mpWindow;
      void boundCoords(GLfloat *pLeft, GLfloat *pWidth, GLfloat *pTop, GLfloat *pHeight);
      static bool msIsInitialized;
      static int mKeyPressed;
};

#endif