#ifndef BATCHEDBUFFER_H
#define BATCHEDBUFFER_H

#include "common.h"
#include "glcommon.h"
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
    BatchBuffer(const std::vector<RenderData> &crRendData, const uint32_t cShape, const uint32_t cNumVao, const uint32_t cNumVbo, const uint32_t cNumIbo,
                const GLenum cDrawType);
    std::shared_ptr<VertexBuffer> getVbo();
    std::shared_ptr<VertexArray> getVao();
    std::shared_ptr<IndexBuffer> getIbo();
    VertexBufferLayout getLayout();
    ~BatchBuffer();
    int8_t initBatchBuffer(const uint32_t cNumVao, const uint32_t cNumVbo, const uint32_t cNumIbo, const std::vector<RenderData> &crRendData, const GLenum cDrawType);
    int8_t initVao(const uint32_t cNumVao);
    int8_t initVbo(const uint32_t cNumVbo, const std::vector<RenderData> &crRendData, const GLenum cDrawType);
    int8_t initIbo(const uint32_t cNumVbo, const std::vector<std::vector<RenderData>> &crRendData, const uint32_t cShape);
    static void concatRenderData(const std::vector<Drawable*> &crBufferData, std::vector<RenderData> &rData);
    void updateBoundedBufferData(const std::vector<RenderData> &crRendData, const GLenum cDrawType);
  private:
    std::shared_ptr<VertexBuffer> mpVbo;
    std::shared_ptr<VertexArray> mpVao;
    std::shared_ptr<IndexBuffer> mpIbo;
    VertexBufferLayout mLayout;

    std::vector<uint32_t> createRectIndices(const uint32_t cVboSize);
    std::vector<uint32_t> createTriIndices(const uint32_t cVboSize);
};

#endif