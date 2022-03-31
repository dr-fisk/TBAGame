#include "batchBuffer.h"

BatchBuffer::BatchBuffer(std::vector<RectVertices> &bufferData, uint32_t shape) {
  vao = std::make_shared<VertexArray>(1);
  vbo = std::make_shared<VertexBuffer>(bufferData.data(), bufferData.size() * SQUARE_BYTE_SIZE);
  layout.push(TWO_D_COORDS);

  std::vector<uint32_t> indices = shape == RECTANGLE? createRectIndices(bufferData.size()) : 
                                                      createTriIndices(bufferData.size());

  ibo = std::make_shared<IndexBuffer>(indices.data(), indices.size());
}

BatchBuffer::~BatchBuffer() {
}

std::vector<uint32_t> BatchBuffer::createRectIndices(uint32_t vboSize) {
  std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0};
  uint32_t offset = 4;

  for (int i = 1; i < vboSize; i++) {
    indices.push_back(indices[0] + (offset * i)); 
    indices.push_back(indices[1] + (offset * i));
    indices.push_back(indices[2] + (offset * i));
    indices.push_back(indices[3] + (offset * i));
    indices.push_back(indices[4] + (offset * i));
    indices.push_back(indices[5] + (offset * i));
  }

  return indices;
}

std::vector<uint32_t> BatchBuffer::createTriIndices(uint32_t vboSize) {
  std::vector<uint32_t> indices = {0, 1, 2};
  uint32_t offset = 3;

  for (int i = 1; i < vboSize; i++) {
    indices.push_back(indices[0] + (offset * i)); 
    indices.push_back(indices[1] + (offset * i));
    indices.push_back(indices[2] + (offset * i));
  }

  return indices;
}

void BatchBuffer::render(const std::shared_ptr<RenderTarget> &target) {
  target->draw(vbo, vao, ibo, layout);
}