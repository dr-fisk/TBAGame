#ifndef BATCHEDBUFFER_H
#define BATCHEDBUFFER_H

#include "common.h"
#include "renderTarget.h"
#include "Drawable.h"

class BatchBuffer {
  public:
    BatchBuffer();
    BatchBuffer(std::vector<Drawable*> &bufferData, uint32_t shape);
    ~BatchBuffer();
    void render(const std::shared_ptr<RenderTarget> &target);
  private:
    std::shared_ptr<VertexBuffer> vbo;
    std::shared_ptr<VertexArray> vao;
    std::shared_ptr<IndexBuffer> ibo;
    VertexBufferLayout layout;

    std::vector<uint32_t> createRectIndices(uint32_t vboSize);
    std::vector<uint32_t> createTriIndices(uint32_t vboSize);
    void concatRenderData(std::vector<Drawable*> &bufferData, std::vector<RenderData> &data);
};

#endif