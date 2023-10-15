#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "renderTarget.h"

class RenderWindow : public RenderTarget {
    public:
      RenderWindow(const uint32_t cWindowWidth, const uint32_t cWindowHeight, const char *cpTitle, GLFWwindow *pWindow=NULL);
      ~RenderWindow() = default;
      bool isOpen();
      virtual uint32_t getWindowWidth();
      virtual uint32_t getWindowHeight();
      virtual void clear();
      virtual void display();
      virtual void draw(Rect &rShape);
      virtual void draw(const uint64_t cCount);

      virtual RenderData createRenderDataBounded(Rect &rShape);
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
};

#endif