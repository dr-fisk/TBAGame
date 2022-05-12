#include "batchBuffer.h"

/* Function:    BatchBuffer
   Description: Creates Batch Buffer object which easily handles batch rendering
   Parameters:  Vector - Buffer data to pass to VBO
                uint32_t  - Shape to draw
   Returns:     None
 */
//TODO: change sizes depending on shape
BatchBuffer::BatchBuffer(std::vector<RectVertexData> &bufferData, uint32_t shape) {
  vao = std::make_shared<VertexArray>(1);
  vbo = std::make_shared<VertexBuffer>(bufferData.data(), bufferData.size() * sizeof(RectVertexData));
  layout.push(TWO_D_COORDS, GL_FLOAT);
  layout.push(RGBA, GL_FLOAT);

  std::vector<uint32_t> indices = shape == RECTANGLE? createRectIndices(bufferData.size()) : 
                                                      createTriIndices(bufferData.size());

  ibo = std::make_shared<IndexBuffer>(indices.data(), indices.size());
}

/* Function:    ~BatchBuffer
   Description: Destroys batch buffer
   Parameters:  None
   Returns:     None
 */
BatchBuffer::~BatchBuffer() {
}

/* Function:    createRectIndices
   Description: Creates Rect IBO data to associate with VBO
   Parameters:  uint32_t - Size of VBO
   Returns:     Vector   - Indeces to construct Rect IBO
 */
std::vector<uint32_t> BatchBuffer::createRectIndices(uint32_t vboSize) {
  std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0};
  uint32_t offset = SQUARE_VERTICES2D;

  /* Squares contain 6 Vertices indexed from 0-5*/
  for (uint32_t i = 1; i < vboSize; i++) {
    indices.push_back(indices[0] + (offset * i)); 
    indices.push_back(indices[1] + (offset * i));
    indices.push_back(indices[2] + (offset * i));
    indices.push_back(indices[3] + (offset * i));
    indices.push_back(indices[4] + (offset * i));
    indices.push_back(indices[5] + (offset * i));
  }

  return indices;
}

/* Function:    createTriIndices
   Description: Creates Triangle IBO data to associate with VBO
   Parameters:  uint32_t - Size of VBO
   Returns:     Vector   - Indeces to construct Triangle IBO
 */
std::vector<uint32_t> BatchBuffer::createTriIndices(uint32_t vboSize) {
  std::vector<uint32_t> indices = {0, 1, 2};
  uint32_t offset = TRIANGLE_VERTICES2D;

  /* Triangles contain 3 vertices indexed 0-2 */
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