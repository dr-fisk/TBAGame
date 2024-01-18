#include <iostream>
#include <vector>

#include "window/renderWindow.h"
#include "window/mouse.h"
#include "input/input.h"
#include "window/keyboard.h"

bool RenderWindow::msCallbacksInitialized = false;
int32_t RenderWindow::msWindowId = 0;
int32_t RenderWindow::msActiveWindowId = -1;

//! @brief Initializes opengl window
//!
//! @param[in]  cWindowWidth  Window width
//! @param[in]  cWindowHeight Window height
//! @param[in]  cpTitle       Window title
//! @param[out] pWindow       Allows sharing of resources for when needing multiple windows, is NULL otherwise
//!
//! @return None
RenderWindow::RenderWindow(const uint32_t cWindowWidth, const uint32_t cWindowHeight, const char *cpTitle,
                           GLFWwindow *pWindow)
{ 
  mWdwWidth = cWindowWidth;
  mWdwHeight = cWindowHeight;
  mTitle = cpTitle;
  mpWindow = glfwCreateWindow(mWdwWidth, mWdwHeight, cpTitle, nullptr, pWindow);

  if (!mpWindow)
  {
    std::cout << "Error opening window" << std::endl;
    glfwTerminate();
    exit(-1);
  }


  mWindowId = msWindowId;
  msWindowId ++;
  int w, h;
  glfwGetWindowSize(mpWindow, &w, &h);
  std::cout << "Width: " << w << " Height: " << h << std::endl;
}

//! @brief Handles displaying data stored in all buffers
//!
//! @return None
void RenderWindow::display()
{
  GLCall(glfwSwapBuffers(mpWindow));
}

//! @brief Draws VBO data to window
//!
//! @param cCount Number of Elements to Draw
//!
//! @return None 
void RenderWindow::draw(const uint64_t cCount)
{
  GLCall(glDrawElements(GL_TRIANGLES, cCount, GL_UNSIGNED_INT, nullptr));
}

//! @brief Gets window width
//!
//! @return Window width
uint32_t RenderWindow::getWindowWidth()
{
    return mWdwWidth;
}

//! @brief Gets window height
//!
//! @return Window height
uint32_t RenderWindow::getWindowHeight()
{
  return mWdwHeight;
}

//! @brief Checks whether window has been closed
//!
//! @return true if Window is open false otherwise
bool RenderWindow::isOpen()
{
  return !glfwWindowShouldClose(mpWindow);
}

//! @brief Ensures coordinates are never out of bounds from resolution
//!
//! @return None
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

//! @brief Sets the current window to be the Current OpenGL context useful for working with multiple windows must be called before any GL Funciton Call
//!
//! @return None
void RenderWindow::setActive()
{
  if(msActiveWindowId != mWindowId)
  {
    glfwMakeContextCurrent(mpWindow);

    //Vsync off later make it toggable (limits fps)
    glfwSwapInterval(0);
    glewExperimental = GL_TRUE;
    glewInit();
    
    if(!msCallbacksInitialized)
    {
      setCallbacks();
    }

    msActiveWindowId = mWindowId;
  }
}

//! @brief Cleans up the render window, must be called as this allows for multiple windows to be used
//!
//! @return None
void RenderWindow::destroyWindow()
{
  /* Due to shader, IB, VAO, and VBO being smart pointers,
     reset needs to be called to delete opengl data before
     terminating window  */
  glfwDestroyWindow(mpWindow);
}

//! @brief Getter function for getting a reference to the currnet Gl Window
//! 
//! @return GLFWwindow* - A refernce to the GL Window
GLFWwindow* RenderWindow::getGlWindow()
{
  return mpWindow;
}

//! @brief Inits GL Attributes and must be called after setActive
//!
//! @return None
void RenderWindow::initWindow()
{
  GLCall(glClearColor(0.3, 0.0, 0.0, 1.0));
  // glClear(GL_COLOR_BUFFER_BIT);
}

//! @brief Polls Event queue
//!
//! @param[out] rEvent Event returned from Event Queue
//!
//! @return True if event returned, false otherwise
bool RenderWindow::pollEvent(Event& rEvent)
{
  return lg::Input::popEvent(rEvent);
}

std::shared_ptr<RenderWindow> RenderWindow::createSharedWindow()
{
  if(nullptr == mpWindow)
  {
    return nullptr;
  }

  // Need params here in function
  return std::make_shared<RenderWindow>(800, 600, "A shared window", mpWindow);
}

//! @brief Sets all callbacks used by LestGui
//!
//! @return None
void RenderWindow::setCallbacks()
{
  glfwSetCursorPosCallback(mpWindow, lg::Mouse::mousePositionCallback);
  glfwSetMouseButtonCallback(mpWindow, lg::Mouse::mouseButtonCallback);
  glfwSetKeyCallback(mpWindow, lg::Keyboard::keyCallback);
  msCallbacksInitialized = true;
}