#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "common.h"
#include "renderTarget.h"

class RenderWindow : public RenderTarget {
    public:
      RenderWindow(uint32_t wWidth, uint32_t wHeight, const char *title);
      ~RenderWindow();
      bool isOpen();
      virtual uint32_t getWindowWidth();
      virtual uint32_t getWindowHeight();
      virtual void clear();
      virtual void display();
      virtual void draw(Rect shape);
      virtual VertexArray* getVao();
      void pollEvent();
    private:
      uint32_t wHeight;
      uint32_t wWidth;
      VertexArray *vao;
      VertexBuffer *vbo;
      IndexBuffer *ib;
      uint32_t shader;
      std::string title;
      GLFWwindow *window;
};

#endif