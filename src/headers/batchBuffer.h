#ifndef BATCHEDBUFFER_H
#define BATCHEDBUFFER_H

#include "common.h"
#include "renderTarget.h"

class BatchBuffer {
  public:
    BatchBuffer(std::vector<RectVertices> &bufferData, uint32_t shape);
    ~BatchBuffer();
    void render(const std::shared_ptr<RenderTarget> &target);
  private:
    std::shared_ptr<VertexBuffer> vbo;
    std::shared_ptr<VertexArray> vao;
    std::shared_ptr<IndexBuffer> ibo;
    VertexBufferLayout layout;

    std::vector<uint32_t> createRectIndices(uint32_t vboSize);
    std::vector<uint32_t> createTriIndices(uint32_t vboSize);
};

#endif