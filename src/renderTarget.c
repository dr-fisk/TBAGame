#include "renderTarget.h"
#include "renderWindow.h"

/* Function:    Rect
   Description: Default Constructor
   Parameters:  None
   Returns:     None
 */
Rect::Rect() {
  this->left   = 0;
  this->top    = 0;
  this->width  = 0;
  this->height = 0;
}

/* Function:    Rect
   Description: Creates rectangle shape
   Parameters:  uint32_t - leftmost coordinate
                uint32_t - topmost coordinate
                uint32_t - height of rect
                uint32_t - width of rect
   Returns:     None
 */
Rect::Rect(uint32_t left, uint32_t top, uint32_t height, uint32_t width) {
  this->left   = left;
  this->top    = top;
  this->width  = width;
  this->height = height;
}

/* Function:    getDimensions
   Description: Assigns dimensions of rectangle use function with either pointers
                or pass by reference
   Parameters:  None
   Returns:     None
 */
void Rect::getDimensions(GLfloat *left, GLfloat *top, GLfloat *height, GLfloat *width) {
  *left   = this->left;
  *top    = this->top;
  *height = this->height;
  *width  = this->width;
}

/* Function:    ~Rect
   Description: Destructor
   Parameters:  None
   Returns:     None
 */
Rect::~Rect() {
}

/* Function:    RenderTarget
   Description: Default Contructor
   Parameters:  None
   Returns:     None
 */
RenderTarget::RenderTarget() {
}

/* Function:    ~RenderTarget
   Description: Destructor
   Parameters:  None
   Returns:     None
 */
RenderTarget::~RenderTarget() {
}

/* Function:    clear
   Description: Virtual Function
   Parameters:  None
   Returns:     None
 */
void RenderTarget::clear() {
}

/* Function:    display
   Description: Virtual Function
   Parameters:  None
   Returns:     None
 */
void RenderTarget::display() {
}

/* Function:    draw
   Description: Virtual Function
   Parameters:  Rect - Shape to draw
   Returns:     None
 */
void RenderTarget::draw(Rect shape) {
}

//TODO: Fix Description
/* Function:    draw
   Description: Virtual Function
   Parameters:  VertexBuffer - VBO to draw
                uint32_t     - Number of vertexes
                uint32_t     - Size of each vertex
   Returns:     None
 */
void RenderTarget::draw(const std::shared_ptr<VertexBuffer> &VBO, const std::shared_ptr<VertexArray> &VAO,
                        const std::shared_ptr<IndexBuffer> &IBO, const VertexBufferLayout &layout) {
}

/* Function:    getWindowWidth
   Description: Virtual Function
   Parameters:  None
   Returns:     None
 */
uint32_t RenderTarget::getWindowWidth() {
}

/* Function:    getWindowHeight
   Description: Virtual Function
   Parameters:  None
   Returns:     None
 */
uint32_t RenderTarget::getWindowHeight() {
}

/* Function:    getVao
   Description: Virtual Function
   Parameters:  None
   Returns:     None
 */
std::shared_ptr<VertexArray> RenderTarget::getVao() {
}

/* Function:    createRectVertices
   Description: Virtual Function
   Parameters:  None
   Returns:     None
 */
RectVertices RenderTarget::createRectVertices(Rect shape) {
}