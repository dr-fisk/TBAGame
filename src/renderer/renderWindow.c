#include "renderWindow.h"

/* Function:    RenderWindow
   Description: Initializes opengl window, shaders (until abstraction) and
                VAO, VBO, and IBO
   Parameters:  uint32_t - Window width
                uint32_t - Window height
                char*    - Window title
                GLFWwindow * - (OPTIONAL) Allows sharing of resources for when needing multiple windows, is NULL otherwise
   Returns:     None
 */
RenderWindow::RenderWindow(const uint32_t cWindowWidth, const uint32_t cWindowHeight, const char *cpTitle, GLFWwindow *pWindow) {
  mWdwWidth = cWindowWidth;
  mWdwHeight = cWindowHeight;
  mTitle = cpTitle;
  mpWindow = glfwCreateWindow(mWdwWidth, mWdwHeight, cpTitle, NULL, pWindow);

  if (!mpWindow) {
    std::cout << "Error opening window" << std::endl;
    glfwTerminate();
    exit(0);
  }
}

/* Function:    ~RenderWindow
   Description: Cleans up Window memory and terminates opengl
                Due to using smart pts, we need to explicitly destroy
   Parameters:  None
   Returns:     None
 */
RenderWindow::~RenderWindow() {
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
  GLCall(glfwSwapBuffers(mpWindow));
  GLCall(glFlush());
}

//TODO: add different shapes?
/* Function:    draw
   Description: Renders one shape at a time, only use for non-intensive operations
                like menus
   Parameters:  Rect - Rectangle to draw
   Returns:     None
 */
void RenderWindow::draw(Rect &rShape) {
/*  clear();
  RenderData vc;
  uint32_t indeces [] = {0,1,2,2,3,0};
  vc = createRenderDataBounded(rShape); 
  std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(&vc, sizeof(vc));
  VertexBufferLayout layout;
  std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>(1);
  std::shared_ptr<IndexBuffer> ibo  = std::make_shared<IndexBuffer>(indeces, 6);
  layout.push(TWO_D_COORDS, GL_FLOAT);
  layout.push(RGBA, GL_FLOAT);
  vao->addBuffer(vbo, layout);
  mpShader->bind();
  ibo->bind();
  GLCall(glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr));
  display();*/
}

void RenderWindow::draw(BatchBuffer &rBuffer) {
  std::shared_ptr<VertexBuffer> vbo = rBuffer.getVbo();
  std::shared_ptr<VertexArray> vao = rBuffer.getVao();
  std::shared_ptr<IndexBuffer> ibo = rBuffer.getIbo();
  VertexBufferLayout layout = rBuffer.getLayout();

  clear();
  draw(vbo, vao, ibo, layout);
  display();
}

/* Function:    draw
   Description: Handles batched rendering
   Parameters:  VertexBuffer - Vertex Buffer to draw
                VertexArray  - Vertex Array to draw
                IndexBuffer  - Index Buffer to draw
                VertexBufferLayout - Layout of VertexBuffer for VAO
   Returns:     None
 */
void RenderWindow::draw(const std::shared_ptr<VertexBuffer> &crpVbo, const std::shared_ptr<VertexArray> &crpVao, 
                        const std::shared_ptr<IndexBuffer> &crpIbo, const VertexBufferLayout &crLayout) {
  //Maybe I'm supposed to do this once per vao
  crpVao->bind(0);
  crpVbo->bind(0);
  crpVao->addBuffer(crLayout);
  mpShader->bind();
  crpIbo->bind(0);
  GLCall(glDrawElements(GL_TRIANGLES, crpIbo->getCount(), GL_UNSIGNED_INT, nullptr));
}

/* Function:    getWindowWidth
   Description: Gets window width
   Parameters:  None
   Returns:     uint32_t - Window width
 */
uint32_t RenderWindow::getWindowWidth() {
    return mWdwWidth;
}

/* Function:    getWindowHeight
   Description: Gets window height
   Parameters:  None
   Returns:     uint32_t - Window height
 */
uint32_t RenderWindow::getWindowHeight() {
    return mWdwHeight;
}

/* Function:    getWindowWidth
   Description: Checks whether window has been closed
   Parameters:  None
   Returns:     bool - Window open
 */
bool RenderWindow::isOpen(){
    return !glfwWindowShouldClose(mpWindow);
}

/* Function:    createRenderData
   Description: Normalizes Rect coords to be drawn on window this allows us
                to not have to worry about resolution
   Parameters:  Rect - Rectangle shape to extract coordinates
   Returns:     RenderData - Vertexes from shape;
 */
RenderData RenderWindow::createRenderDataBounded(Rect &rShape) {
  GLfloat left, top, width, height;
  lg::Color rgba = rShape.getRGBA();
  rShape.getDimensions(&left, &top, &width, &height);
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
void RenderWindow::boundCoords(GLfloat *pLeft, GLfloat *pWidth, GLfloat *pTop, GLfloat *pHeight) {
  uint32_t wWidth = getWindowWidth();
  uint32_t wHeight = getWindowHeight();

  if (*pWidth > wWidth)
    *pWidth = wWidth;

  if (*pHeight > wHeight)
    *pHeight = wHeight;

  if (*pLeft > wWidth)
    *pLeft = wWidth;
  
  if (*pHeight > wHeight)
    *pHeight = wHeight;

  if ((*pLeft + *pWidth) > wWidth) {
    *pLeft -= *pWidth;

    if (*pLeft < 0.0f)
      *pLeft = 0.0f;
  }

  if ((*pTop + *pHeight) > wHeight) {
    *pTop -= *pHeight;

    if (*pTop < 0.0f)
      *pTop = 0.0f;
  }
}

/* Function:    setActive
   Description: Sets the current window to be the Current OpenGL context useful for working with multiple windows must be called before any GL Funciton Call
   Parameters:  None
   Returns:     None
 */
void RenderWindow::setActive() {
  glfwMakeContextCurrent(mpWindow);

  //Vsync off later make it toggable (limits fps)
  glfwSwapInterval(0);
  glewExperimental = GL_TRUE;
  glewInit();
}

/* Function:    destroyWindow
   Description: Cleans up the render window, must be called as this allows for multiple windows to be used
   Parameters:  None
   Returns:     None
 */
void RenderWindow::destroyWindow() {
  /* Due to shader, IB, VAO, and VBO being smart pointers,
     reset needs to be called to delete opengl data before
     terminating window */
  mpShader.reset();
  glfwDestroyWindow(mpWindow);
}

/* Function:    getGlWindow
   Description: Getter function for getting a reference to the currnet Gl Window
   Parameters:  None
   Returns:     GLFWwindow* - A refernce to the GL Window
 */
GLFWwindow* RenderWindow::getGlWindow() {
  return mpWindow;
}

/* Function:    setShader
   Description: Sets the shader to be used for rendering, can actively change shaders
   Parameters:  None
   Returns:     None
 */
void RenderWindow::setShader(const std::shared_ptr<Shader> &crpShader) {
  mpShader = crpShader;
}

/* Function:    setVao
   Description: Sets the Vertex Attribute Object to be used for rendering, can actively change Vertex Attribute Objects
   Parameters:  None
   Returns:     None
 */
void RenderWindow::setVao(const std::shared_ptr<VertexArray> &crpVao) {
  mpVao = crpVao;
}

/* Function:    initWindow
   Description: Inits GL Attributes and must be called after setActive
   Parameters:  None
   Returns:     None
 */
void RenderWindow::initWindow() {
  GLCall(glEnable(GL_BLEND));
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glClearColor(0.3, 0.0, 0.0, 1.0));
}