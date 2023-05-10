#include "batchBuffer.h"

//TODO: Rename class, this is more of an API for handling VAO, VBO, and IBO creation in the correct order
/* Function:    BatchBuffer
   Description: Default Constructor
   Parameters:  None
   Returns:     None
 */
BatchBuffer::BatchBuffer() {
}

/* Function:    BatchBuffer
   Description: Creates Batch Buffer object which easily handles batch rendering
   Parameters:  Vector - List of drawable items to insert into VBO
                uint32_t - Shape to draw
                uint32_t - Number of Vertex Attribute Objects to generate
                uint32_t - Number of Vertex Buffer Objects to generate
                uint32_t - Number of Index Buffer Objects to generate
                GLenum   - Draw type for opengl to use
   Returns:     None
 */
//TODO: change sizes depending on shape
BatchBuffer::BatchBuffer(const std::vector<RenderData> &crRendData, const uint32_t cShape, const uint32_t cNumVao, const uint32_t cNumVbo, const uint32_t cNumIbo, 
                         const GLenum cDrawType) {
  initBatchBuffer(cNumVao, cNumVbo, cNumIbo, crRendData, cDrawType);
  
  mLayout.push(TWO_D_COORDS, GL_FLOAT);
  mLayout.push(RGBA, GL_FLOAT);

  std::vector<uint32_t> indices = cShape == RECTANGLE ? createRectIndices(crRendData.size()) : 
                                                      createTriIndices(crRendData.size());

  //TODO make IBO more dynamic and update
  mpIbo = std::make_shared<IndexBuffer>(1, indices.data(), indices.size());
  mpIbo->bind(0);
  mpIbo->updateBoundedBufferData(indices.data(), indices.size(), cDrawType);
}

/* Function:    initBatchBuffer
   Description: Calls functions to initialize Batch Buffer
   Parameters:  Vector - List of drawable items to insert into VBO
                uint32_t - Number of Vertex Attribute Objects to generate
                uint32_t - Number of Vertex Buffer Objects to generate
                uint32_t - Number of Index Buffer Objects to generate
                GLenum   - Draw type for opengl to use
   Returns:     None
 */
//TODO: Updates for initIBO
int8_t BatchBuffer::initBatchBuffer(const uint32_t cNumVao, const uint32_t cNumVbo, const uint32_t cNumIbo, const std::vector<RenderData> &crRendData, const GLenum cDrawType) { 
  initVao(cNumVao);
  initVbo(cNumVbo, crRendData, cDrawType);
  return 1;
}

/* Function:    initVao
   Description: initializes Vertex Attribute Object
   Parameters:  uint32_t - Number of Vertex Attribute Objects to generate
   Returns:     uint8_t - Success or Failure of Vertex Attribute Object Generation
 */
int8_t BatchBuffer::initVao(const uint32_t cNumVao) {
  if (cNumVao < 1)
    return -1;

  mpVao = std::make_shared<VertexArray>(cNumVao);
  return 1;
}

/* Function:    initVbo
   Description: initializes Vertex Buffer Object
   Parameters:  uint32_t - Number of Vertex Buffer Objects to generate
   Returns:     uint8_t - Success or Failure of Vertex Buffer Object Generation
 */
int8_t BatchBuffer::initVbo(const uint32_t cNumVbo, const std::vector<RenderData> &crRendData, const GLenum cDrawType) {
  mpVbo = std::make_shared<VertexBuffer>(cNumVbo);
  //Will always bind to 0 by default
  mpVbo->bind(0);

  mpVbo->updateBoundedBufferData(crRendData.data(), crRendData.size() * sizeof(RenderData), cDrawType);

  return 1;
}

//TODO Update commment and add functionality
int8_t BatchBuffer::initIbo(const uint32_t cNumIbo, const std::vector<std::vector<RenderData>> &crRendData, const uint32_t cShape) {
 /* if (cNumIbo < 1)
    return -1;

  std::vector<std::vector<uint32_t>> indices(cNumIbo);

  for (uint32_t i = 0; i < cNumVbo; i ++) {
    indeces[i] = cShape == RECTANGLE ? createRectIndices(crRendData[i].size()) : createTriIndices(crRendData[i].size());
  }

  mpIbo = std::make_shared<IndexBuffer>(indeces);*/
  return 1;
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

/* Function:    updateBoundedBufferData
   Description: Updates the Buffer Data for the Vertex Buffer Object
   Parameters:  Vector - Render data to bound to Vertex Buffer Object
                GLenum - Draw type for OpenGL to use
   Returns:     None
 */
 //TODO: Create new function so that VBO and IBO are handled separately, point is if IBO's remain unchanged due to VBO's having same indeces
 // Then we shouldn't always update IBO, give the user the responsibility to do so
 // Also TODO, create static function for createRectIndices, have user be responsible for supplying current IBO's
void BatchBuffer::updateBoundedBufferData(const std::vector<RenderData> &crRendData, const GLenum cDrawType) {
  mpVbo->updateBoundedBufferData(crRendData.data(), crRendData.size() * sizeof(RenderData), cDrawType);

  //TODO: Temporary, make it so this has to be supplied as well
  std::vector<uint32_t> indices = createRectIndices(crRendData.size());

  mpIbo->updateBoundedBufferData(indices.data(), indices.size(), cDrawType);
  
}
