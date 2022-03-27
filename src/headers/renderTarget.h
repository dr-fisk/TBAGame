#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include "common.h"
#include "Vector2D.h"
#include "vertexBuffer.h"
#include "vertexArray.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"

#define TRIANGLE_VERTICES2D 3
#define RECT_VERTICES2D 4
#define SQUARE_BYTE_SIZE 32

class Rect {
  public:
    Rect();
    Rect(uint32_t left, uint32_t top, uint32_t width, uint32_t height);
    ~Rect();
    void getDimensions(uint32_t *left, uint32_t *top, uint32_t *width, uint32_t *height);
  private:
    uint32_t left;
    uint32_t top;
    uint32_t height;
    uint32_t width;
};

class RenderTarget {
    public:
      RenderTarget();
      ~RenderTarget();
      virtual void clear() = 0;
      virtual void display() = 0;
      virtual void draw(Rect shape) = 0;
      virtual uint32_t getWindowHeight() = 0;
      virtual uint32_t getWindowWidth() = 0;
      virtual VertexArray* getVao() = 0;
    private:
      void createRectTarget(Vector2f *vertices, GLfloat left, GLfloat top, GLfloat width, 
                        GLfloat height);
      void boundCoords(GLfloat *left, GLfloat *width, GLfloat *top, GLfloat *height);
};

#endif