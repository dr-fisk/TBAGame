#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include "common.h"
#include "vertexBuffer.h"
#include "vertexArray.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"
#include "shader.h"
#include "rectangle.h"

#define TWO_D_COORDS 2
#define TRIANGLE_VERTICES2D 3
#define SQUARE_VERTICES2D 4
#define RGBA 4
#define SQUARE_INDICES 6
#define SQUARE_BYTE_SIZE 32

enum TARGETS{RECTANGLE, TRIANGLE};

class RenderTarget {
    public:
      RenderTarget();
      ~RenderTarget();
      virtual void clear() = 0;
      virtual void display() = 0;
      virtual void draw(Rect shape) = 0;
      virtual void draw(const std::shared_ptr<VertexBuffer> &VBO, const std::shared_ptr<VertexArray> &VAO,
                        const std::shared_ptr<IndexBuffer> &IBO, const VertexBufferLayout &layout) = 0;
      virtual uint32_t getWindowHeight() = 0;
      virtual uint32_t getWindowWidth() = 0;
      virtual std::shared_ptr<VertexArray> getVao() = 0;
      virtual RectVertexData createRectVertexDataBounded(Rect shape) = 0;
    private:
};

#endif