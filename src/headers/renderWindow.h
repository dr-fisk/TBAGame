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
      virtual void draw(const std::shared_ptr<VertexBuffer> &VBO, const std::shared_ptr<VertexArray> &VAO,
                        const std::shared_ptr<IndexBuffer> &IBO, const VertexBufferLayout &layout);
      virtual std::shared_ptr<VertexArray> getVao();
      virtual RectVertices createRectVertices(Rect shape);
      void pollEvent();
    private:
      uint32_t wHeight;
      uint32_t wWidth;
      std::shared_ptr<VertexArray> vao;
      std::shared_ptr<VertexBuffer> vbo;
      std::shared_ptr<IndexBuffer> ib;
      std::shared_ptr<Shader> shader;
      std::string title;
      GLFWwindow *window;
      void boundCoords(GLfloat *left, GLfloat *width, GLfloat *top, GLfloat *height);
};

#endif