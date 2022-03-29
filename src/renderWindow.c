#include "renderWindow.h"

/* Function:    RenderWindow
   Description: Initializes opengl window, shaders (until abstraction) and
                VAO, VBO, and IBO
   Parameters:  uint32_t - Window width
                uint32_t - Window height
                char*    - Window title
   Returns:     None 
 */
RenderWindow::RenderWindow(uint32_t wWidth, uint32_t wHeight, const char *title) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if(!glfwInit()) {
    std::cout << "Failed to open window" << std::endl;
    exit(0);
  }

  this->wWidth = wWidth;
  this->wHeight = wHeight;
  this->title = title;
  this->window = glfwCreateWindow(wWidth, wHeight, title, NULL, NULL);
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  glewInit();

  if (!window) {
    std::cout << "Error opening window" << std::endl;
    glfwTerminate();
    exit(0);
  }

  /* inits the shaders */
  shader = std::make_shared<Shader>("./shaders/shader1.txt");

  /* init vao and vbo must be after glewInit*/
  uint32_t indeces [] = {0,1,2,2,3,0};
  vao = std::make_shared<VertexArray>(1);
  ib  = std::make_shared<IndexBuffer>(indeces, 6);
  glClearColor(0.0, 0.0, 0.0, 1.0);
}

/* Function:    ~RenderWindow
   Description: Cleans up Window memory and terminates opengl
                Due to using smart pts, we need to explicitly destroy
   Parameters:  None
   Returns:     None 
 */
RenderWindow::~RenderWindow(){
  shader->deleteShader();
  ib->deleteIndexBuffer();
  vao->deleteVAO();
  glfwDestroyWindow(window);
  glfwTerminate();
}

/* Function:    clear
   Description: Sets window to background color
   Parameters:  None
   Returns:     None 
 */
void RenderWindow::clear() {
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

/* Function:    display
   Description: Handles displaying data stored in all buffers
   Parameters:  None
   Returns:     None 
 */
void RenderWindow::display() {
  GLCall(glfwSwapBuffers(window));
  GLCall(glfwPollEvents());
  GLCall(glFlush());
}

/* Function:    getVao
   Description: Returns the VAO associated to window
   Parameters:  None
   Returns:     shared_ptr<VertexArray> - Window VAO 
 */
std::shared_ptr<VertexArray> RenderWindow::getVao() {
  return vao;
}

/* Function:    draw
   Description: Handles rendering all buffers to be displayed on window
                Calls should look like clear()->render()->display() then loop
   Parameters:  None
   Returns:     None 
 */
/* TODO: Handle drawing shapes */
void RenderWindow::draw(Rect shape) {
  uint32_t left, top, width, height;
  Vector2f vc[4];
  shape.getDimensions(&left, &top, &width, &height);
  createRectTarget(vc, (GLfloat) left, (GLfloat) top, (GLfloat) width, (GLfloat) height);
  vbo = std::make_shared<VertexBuffer>(vc, SQUARE_BYTE_SIZE);
  VertexBufferLayout layout;
  layout.push(TWO_D_COORDS);
  vao->addBuffer(vbo, layout);
  shader->bind();
  ib->bind();
  GLCall(glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr));
  vbo->deleteVBO();
}

/* Function:    getWindowWidth
   Description: Gets window width
   Parameters:  None
   Returns:     uint32_t - Window width 
 */
uint32_t RenderWindow::getWindowWidth() {
    return wWidth;
}

/* Function:    getWindowHeight
   Description: Gets window height
   Parameters:  None
   Returns:     uint32_t - Window height
 */
uint32_t RenderWindow::getWindowHeight() {
    return wHeight;
}

/* Function:    getWindowWidth
   Description: Checks whether window has been closed
   Parameters:  None
   Returns:     bool - Window open 
 */
bool RenderWindow::isOpen(){
    return !glfwWindowShouldClose(window);
}

/* Function:    createRectTarget
   Description: Normalizes Rect coords to be drawn on window this allows us
                to not have to worry about resolution
   Parameters:  Vector2f - Buffer to store normalized rect coordinates
                GLfloat  - Rect left coord
                GLfloat  - Rect top coord
                GLfloat  - Rect width
                GLfloat  - Rect height
   Returns:     None 
 */
void RenderWindow::createRectTarget(Vector2f *vertices, GLfloat left, GLfloat top, GLfloat width, 
                                GLfloat height) {
  GLfloat wWidth = (GLfloat) getWindowWidth() / 2.0f;
  GLfloat wHeight = (GLfloat) getWindowHeight() / 2.0f;

  boundCoords(&left, &width, &top, &height);

  GLfloat x1 = (left / wWidth) - 1.0f;
  GLfloat x2 = ((left + width)/ wWidth) - 1.0f;
  GLfloat y1 = -1 * ((top / wHeight) - 1.0f);
  GLfloat y2 = -1 * (((top + height) / wHeight) - 1.0f);
  
  vertices[0] = Vector2f(x1, y1);
  vertices[1] = Vector2f(x1, y2);
  vertices[2] = Vector2f(x2, y2);
  vertices[3] = Vector2f(x2, y1);
}

/* Function:    boundCoords
   Description: Ensures coordinates are never out of bounds from resolution
   Parameters:  None
   Returns:     None 
 */
void RenderWindow::boundCoords(GLfloat *left, GLfloat *width, GLfloat *top, GLfloat *height) {
  uint32_t wWidth = getWindowWidth();
  uint32_t wHeight = getWindowHeight();

  if (*width > wWidth)
    *width = wWidth;

  if (*height > wHeight)
    *height = wHeight;

  if (*left > wWidth)
    *left = wWidth;
  
  if (*height > wHeight)
    *height = wHeight;

  if ((*left + *width) > wWidth) {
    *left -= *width;

    if (*left < 0.0f)
      *left = 0.0f;
  }

  if ((*top + *height) > wHeight) {
    *top -= *height;

    if (*top < 0.0f)
      *top = 0.0f;
  }
}

void RenderWindow::pollEvent() {
}