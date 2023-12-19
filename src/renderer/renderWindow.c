#include <iostream>
#include <vector>

#include "renderWindow.h"
#include "glcommon.h"

bool RenderWindow::msIsInitialized = false;
int RenderWindow::mKeyPressed = GLFW_KEY_UNKNOWN;

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
  if(!msIsInitialized)
  {
    if(!glfwInit())
    {
      std::cout << "Failed to open window" << std::endl;
      exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    msIsInitialized = true;
  }
 
  mWdwWidth = cWindowWidth;
  mWdwHeight = cWindowHeight;
  mTitle = cpTitle;
  mpWindow = glfwCreateWindow(mWdwWidth, mWdwHeight, cpTitle, NULL, pWindow);

  if (!mpWindow) {
    std::cout << "Error opening window" << std::endl;
    glfwTerminate();
    exit(-1);
  }
}

void RenderWindow::enableBlend()
{
  GLCall(glEnable(GL_BLEND));
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void RenderWindow::disableBlend()
{
  GLCall(glDisable(GL_BLEND));
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
  Vertex vc;
  uint32_t indeces [] = {0,1,2,2,3,0};
  vc = createVertexBounded(rShape); 
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

void RenderWindow::draw(const uint64_t cCount) {
  clear();
  GLCall(glDrawElements(GL_TRIANGLES, cCount, GL_UNSIGNED_INT, nullptr));
  display();
}

/* Function:    getWindowWidth
   Description: Gets window width
   Parameters:  None
   Returns:     uint32_t - Window width
 */
uint32_t RenderWindow::getWindowWidth()
{
    return mWdwWidth;
}

/* Function:    getWindowHeight
   Description: Gets window height
   Parameters:  None
   Returns:     uint32_t - Window height
 */
uint32_t RenderWindow::getWindowHeight()
{
    return mWdwHeight;
}

/* Function:    getWindowWidth
   Description: Checks whether window has been closed
   Parameters:  None
   Returns:     bool - Window open
 */
bool RenderWindow::isOpen()
{
    return !glfwWindowShouldClose(mpWindow);
}

/* Function:    createVertex
   Description: Normalizes Rect coords to be drawn on window this allows us
                to not have to worry about resolution
   Parameters:  Rect - Rectangle shape to extract coordinates
   Returns:     Vertex - Vertexes from shape;
 */
Vertex RenderWindow::createVertexBounded(Rect &rShape)
{
  GLfloat left, top, width, height;
  lg::Color rgba = rShape.getRGBA();
  rShape.getDimensions(&left, &top, &width, &height);
  GLfloat wWidth = static_cast<GLfloat>(getWindowWidth()) / 2.0f;
  GLfloat wHeight = static_cast<GLfloat>(getWindowHeight()) / 2.0f;

  boundCoords(&left, &width, &top, &height);

  GLfloat x1 = (left / wWidth) - 1.0f;
  GLfloat x2 = ((left + width)/ wWidth) - 1.0f;
  GLfloat y1 = -1 * ((top / wHeight) - 1.0f);
  GLfloat y2 = -1 * (((top + height) / wHeight) - 1.0f);

  const Vector2<GLfloat> textCoord1(0.0f, 0.0f);
  const Vector2<GLfloat> textCoord2(1.0f, 0.0f);
  const Vector2<GLfloat> textCoord3(1.0f, 1.0f);
  const Vector2<GLfloat> textCoord4(0.0f, 1.0f);

  return { Vector2<GLfloat>(x1, y2), rgba, textCoord1, -1.0f, Vector2<GLfloat>(x2, y2), rgba, textCoord2, -1.0f,
           Vector2<GLfloat>(x2, y1), rgba, textCoord3, -1.0f, Vector2<GLfloat>(x1, y1), rgba, textCoord4, -1.0f };
}

/* Function:    boundCoords
   Description: Ensures coordinates are never out of bounds from resolution
   Parameters:  None
   Returns:     None
 */
void RenderWindow::boundCoords(GLfloat *pLeft, GLfloat *pWidth, GLfloat *pTop, GLfloat *pHeight)
{
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
void RenderWindow::setActive()
{
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
void RenderWindow::destroyWindow()
{
  /* Due to shader, IB, VAO, and VBO being smart pointers,
     reset needs to be called to delete opengl data before
     terminating window */
  // mpShader.reset();
  glfwDestroyWindow(mpWindow);
}

/* Function:    getGlWindow
   Description: Getter function for getting a reference to the currnet Gl Window
   Parameters:  None
   Returns:     GLFWwindow* - A refernce to the GL Window
 */
GLFWwindow* RenderWindow::getGlWindow()
{
  return mpWindow;
}

/* Function:    initWindow
   Description: Inits GL Attributes and must be called after setActive
   Parameters:  None
   Returns:     None
 */
void RenderWindow::initWindow()
{
  GLCall(glClearColor(0.3, 0.0, 0.0, 1.0));
}

void RenderWindow::setKeyCallback()
{
  glfwSetKeyCallback(mpWindow, RenderWindow::keyCallback);
}

int32_t RenderWindow::getKeyPress()
{
  return mKeyPressed;
}

void RenderWindow::keyCallback(GLFWwindow *pWindow, const int32_t cKey, const int32_t cScanCode, const int32_t cAction,
                               const int32_t cMods)
{
  mKeyPressed = cKey;
}

bool RenderWindow::isKeyPressed(const int cKey)
{
  return glfwGetKey(mpWindow, cKey) == GLFW_PRESS;
}