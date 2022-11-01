#include "batchBuffer.h"

BatchBuffer::BatchBuffer() {
}

/* Function:    BatchBuffer
   Description: Creates Batch Buffer object which easily handles batch rendering
   Parameters:  Vector - List of drawable items to insert into VBO
                uint32_t  - Shape to draw
   Returns:     None
 */
//TODO: change sizes depending on shape
BatchBuffer::BatchBuffer(std::vector<Drawable*> &bufferData, uint32_t shape) {
  std::vector<RenderData> rendData;
  concatRenderData(bufferData, rendData);
  vao = std::make_shared<VertexArray>(1);
  vbo = std::make_shared<VertexBuffer>(rendData.data(), rendData.size() * sizeof(RenderData));
  layout.push(TWO_D_COORDS, GL_FLOAT);
  layout.push(RGBA, GL_FLOAT);

  std::vector<uint32_t> indices = shape == RECTANGLE? createRectIndices(rendData.size()) : 
                                                      createTriIndices(rendData.size());

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

/* Function:    render
   Description: Renders the vertex buffer object
   Parameters:  RenderTarget - The target to render the VBO to
   Returns:     None
 */
void BatchBuffer::render(const std::shared_ptr<RenderTarget> &target) {
  target->draw(vbo, vao, ibo, layout);
}

/* Function:    concatRenderData
   Description: Concatenates render data for each drawable item into one vector
   Parameters:  Vector - List of drawable items
                Vector - Container for all render data
   Returns:     None
 */
void BatchBuffer::concatRenderData(std::vector<Drawable*> &bufferData, std::vector<RenderData> &data) {
  std::vector<RenderData> temp;

  for (size_t i = 0; i < bufferData.size(); i ++) {
    if (i == 0)
      data = bufferData[i]->getRenderData();
    else {
      temp = bufferData[i]->getRenderData();
      data.insert(data.end(), temp.begin(), temp.end());
      temp.clear();
    }
  }
}
