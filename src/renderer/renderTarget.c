#include "renderTarget.h"
#include "renderWindow.h"

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
                VertexArray  - VAO to draw
                IndexBuffer  - IBO to draw VBO
                VertexBufferLayout - Layout of VBO
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

/* Function:    createRectVertexData
   Description: Virtual Function
   Parameters:  None
   Returns:     None
 */
RectVertexData RenderTarget::createRectVertexDataBounded(Rect shape) {
}