#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "common.h"
#include "glcommon.h"
#include "renderTarget.h"

class RenderWindow : public RenderTarget {
    public:
      RenderWindow(const uint32_t cWindowWidth, const uint32_t cWindowHeight, const char *cpTitle, GLFWwindow *pWindow=NULL);
      ~RenderWindow();
      bool isOpen();
      virtual uint32_t getWindowWidth();
      virtual uint32_t getWindowHeight();
      virtual void clear();
      virtual void display();
      virtual void draw(Rect &rShape);
      virtual void draw(BatchBuffer &rBuffer);
      virtual void draw(const std::shared_ptr<VertexBuffer> &crpVbo, const std::shared_ptr<VertexArray> &crpVao,
                        const std::shared_ptr<IndexBuffer> &crpIbo, const VertexBufferLayout &rLayout);
      virtual RenderData createRenderDataBounded(Rect &rShape);
      void setActive();
      void initWindow();
      void destroyWindow();
      GLFWwindow *getGlWindow();
      void setShader(const std::shared_ptr<Shader> &crpShader);
      void setVao(const std::shared_ptr<VertexArray> &crpVao);
    private:
      uint32_t mWdwHeight;
      uint32_t mWdwWidth;
      std::shared_ptr<Shader> mpShader;
      std::shared_ptr<VertexArray> mpVao;
      std::string mTitle;
      GLFWwindow *mpWindow;
      void boundCoords(GLfloat *pLeft, GLfloat *pWidth, GLfloat *pTop, GLfloat *pHeight);
};

#endif