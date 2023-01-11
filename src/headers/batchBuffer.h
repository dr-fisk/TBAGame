#ifndef BATCHEDBUFFER_H
#define BATCHEDBUFFER_H

#include "common.h"
#include "drawable.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexBufferLayout.h"

#define TWO_D_COORDS 2
#define TRIANGLE_VERTICES2D 3
#define SQUARE_VERTICES2D 4
#define RGBA 4
#define SQUARE_INDICES 6
#define SQUARE_BYTE_SIZE 32

enum TARGETS{
  RECTANGLE, 
  TRIANGLE
};

class BatchBuffer {
  public:
    BatchBuffer();
    BatchBuffer(const std::vector<Drawable*> &crBufferData, const uint32_t cShape);
    std::shared_ptr<VertexBuffer> getVbo();
    std::shared_ptr<VertexArray> getVao();
    std::shared_ptr<IndexBuffer> getIbo();
    VertexBufferLayout getLayout();
    ~BatchBuffer();
  private:
    std::shared_ptr<VertexBuffer> mpVbo;
    std::shared_ptr<VertexArray> mpVao;
    std::shared_ptr<IndexBuffer> mpIbo;
    VertexBufferLayout mLayout;

    std::vector<uint32_t> createRectIndices(const uint32_t cVboSize);
    std::vector<uint32_t> createTriIndices(const uint32_t cVboSize);
    void concatRenderData(const std::vector<Drawable*> &crBufferData, std::vector<RenderData> &rData);
};

#endif