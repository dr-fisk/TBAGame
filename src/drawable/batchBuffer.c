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
BatchBuffer::BatchBuffer(const std::vector<Drawable*> &crBufferData, const uint32_t cShape) {
  std::vector<RenderData> rendData;
  concatRenderData(crBufferData, rendData);
  mpVao = std::make_shared<VertexArray>(1);
  mpVbo = std::make_shared<VertexBuffer>(rendData.data(), rendData.size() * sizeof(RenderData));
  mLayout.push(TWO_D_COORDS, GL_FLOAT);
  mLayout.push(RGBA, GL_FLOAT);

  std::vector<uint32_t> indices = cShape == RECTANGLE ? createRectIndices(rendData.size()) : 
                                                      createTriIndices(rendData.size());

  mpIbo = std::make_shared<IndexBuffer>(indices.data(), indices.size());
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
std::vector<uint32_t> BatchBuffer::createRectIndices(const uint32_t cVboSize) {
  std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0};
  uint32_t offset = SQUARE_VERTICES2D;

  /* Squares contain 6 Vertices indexed from 0-5*/
  for (uint32_t i = 1; i < cVboSize; i++) {
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
std::vector<uint32_t> BatchBuffer::createTriIndices(const uint32_t cVboSize) {
  std::vector<uint32_t> indices = {0, 1, 2};
  uint32_t offset = TRIANGLE_VERTICES2D;

  /* Triangles contain 3 vertices indexed 0-2 */
  for (int i = 1; i < cVboSize; i++) {
    indices.push_back(indices[0] + (offset * i)); 
    indices.push_back(indices[1] + (offset * i));
    indices.push_back(indices[2] + (offset * i));
  }

  return indices;
}

/* Function:    getVbo
   Description: Getter function for member variable mpVbo
   Parameters:  None
   Returns:     std::shared_ptr - Pointer to Vertex Buffer Object
 */
std::shared_ptr<VertexBuffer> BatchBuffer::getVbo() {
  return mpVbo;
}

/* Function:    getVao
   Description: Getter function for member variable mpVao
   Parameters:  None
   Returns:     std::shared_ptr - Pointer to Vertex Attribute Object
 */
std::shared_ptr<VertexArray> BatchBuffer::getVao() {
  return mpVao;
}

/* Function:    getIbo
   Description: Getter function for member variable mpIbo
   Parameters:  None
   Returns:     std::shared_ptr - Pointer to Index Buffer Object
 */
std::shared_ptr<IndexBuffer> BatchBuffer::getIbo() {
  return mpIbo;
}

/* Function:    getLayout
   Description: Getter function for member variable mLayout
   Parameters:  None
   Returns:     VertexBufferLayout - Reference to Vertex Buffer Layout Object
 */
VertexBufferLayout BatchBuffer::getLayout() {
  return mLayout;
}

/* Function:    concatRenderData
   Description: Concatenates render data for each drawable item into one vector
   Parameters:  Vector - List of drawable items
                Vector - Container for all render data
   Returns:     None
 */
void BatchBuffer::concatRenderData(const std::vector<Drawable*> &crBufferData, std::vector<RenderData> &rData) {
  std::vector<RenderData> temp;

  for (size_t i = 0; i < crBufferData.size(); i ++) {
    if (i == 0)
      rData = crBufferData[i]->getRenderData();
    else {
      temp = crBufferData[i]->getRenderData();
      rData.insert(rData.end(), temp.begin(), temp.end());
      temp.clear();
    }
  }
}
