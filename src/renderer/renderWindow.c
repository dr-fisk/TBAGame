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

  //Vsync off later make it toggable (limits fps)
  glfwSwapInterval(0);
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
  glClearColor(0.3, 0.0, 0.0, 1.0);
}

/* Function:    ~RenderWindow
   Description: Cleans up Window memory and terminates opengl
                Due to using smart pts, we need to explicitly destroy
   Parameters:  None
   Returns:     None
 */
RenderWindow::~RenderWindow(){
  /* Due to shader, IB, VAO, and VBO being smart pointers,
     reset needs to be called to delete opengl data before
     terminating window */
  shader.reset();
  ib.reset();
  vao.reset();
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

//TODO: add different shapes?
/* Function:    draw
   Description: Renders one shape at a time, only use for non-intensive operations
                like menus
   Parameters:  Rect - Rectangle to draw
   Returns:     None
 */
void RenderWindow::draw(Rect shape) {
  RectVertexData vc;
  vc = createRectVertexDataBounded(shape); 
  vbo = std::make_shared<VertexBuffer>(&vc, sizeof(vc));
  VertexBufferLayout layout;
  layout.push(TWO_D_COORDS, GL_FLOAT);
  layout.push(RGBA, GL_FLOAT);
  vao->addBuffer(vbo, layout);
  shader->bind();
  ib->bind();
  GLCall(glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr));
  vbo.reset();
}

//TODO: Allow different shaders to be used
/* Function:    draw
   Description: Handles batched rendering
   Parameters:  VertexBuffer - Vertex Buffer to draw
                VertexArray  - Vertex Array to draw
                IndexBuffer  - Index Buffer to draw
                VertexBufferLayout - Layout of VertexBuffer for VAO
   Returns:     None
 */
void RenderWindow::draw(const std::shared_ptr<VertexBuffer> &VBO, const std::shared_ptr<VertexArray> &VAO, 
                        const std::shared_ptr<IndexBuffer> &IBO, const VertexBufferLayout &layout) {
  VAO->addBuffer(VBO, layout);
  /*Soon add own shader*/
  shader->bind();
  IBO->bind();
  GLCall(glDrawElements(GL_TRIANGLES, IBO->getCount(), GL_UNSIGNED_INT, nullptr));
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

/* Function:    createRectVertexData
   Description: Normalizes Rect coords to be drawn on window this allows us
                to not have to worry about resolution
   Parameters:  Rect - Rectangle shape to extract coordinates
   Returns:     RectVertexData - Vertexes from shape;
 */
RectVertexData RenderWindow::createRectVertexDataBounded(Rect shape) {
  GLfloat left, top, width, height;
  lg::Color rgba = shape.getRGBA();
  shape.getDimensions(&left, &top, &width, &height);
  GLfloat wWidth = (GLfloat) getWindowWidth() / 2.0f;
  GLfloat wHeight = (GLfloat) getWindowHeight() / 2.0f;

  boundCoords(&left, &width, &top, &height);

  GLfloat x1 = (left / wWidth) - 1.0f;
  GLfloat x2 = ((left + width)/ wWidth) - 1.0f;
  GLfloat y1 = -1 * ((top / wHeight) - 1.0f);
  GLfloat y2 = -1 * (((top + height) / wHeight) - 1.0f);

  return { Vector2f(x1, y2), rgba, Vector2f(x2, y2), rgba,
           Vector2f(x2, y1), rgba, Vector2f(x1, y1), rgba};
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