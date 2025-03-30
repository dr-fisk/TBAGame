#include <iostream>
#include <vector>

#include "window/renderWindow.hpp"
#include "input/mouse.hpp"
#include "input/input.hpp"
#include "input/keyboard.hpp"
#include "window/window.hpp"
#include "renderer/renderer2D.hpp"
#include "renderer/renderCommand.hpp"
#include "input/mouseEvent.hpp"
#include "input/keyboardEvent.hpp"
#include "input/windowEvent.hpp"

bool RenderWindow::msFirstInit = true;

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

  if(msFirstInit)
  {
    RenderCommand::init();
  }

  mWindowSize = glm::uvec2(cWindowWidth, cWindowHeight);
  mTitle = cpTitle;
  mpWindow = glfwCreateWindow(mWindowSize.x, mWindowSize.y, cpTitle, nullptr, pWindow);

  if(!mpWindow)
  {
    std::cout << "Error opening window" << std::endl;
    glfwTerminate();
    exit(-1);
  }

  setActive();
  
  if(msFirstInit)
  {
    Renderer2D::init();
    msFirstInit = false;
  }

  mEventDispatcher.addEventDispatcher<lre::MouseMoveEvent>();
  mEventDispatcher.addEventDispatcher<lre::MouseButtonPressEvent>();
  mEventDispatcher.addEventDispatcher<lre::MouseButtonReleaseEvent>();
  mEventDispatcher.addEventDispatcher<lre::KeyboardPressEvent>();
  mEventDispatcher.addEventDispatcher<lre::KeyboardReleaseEvent>();
  mEventDispatcher.addEventDispatcher<lre::WindowResizeEvent>();

  //Vsync off later make it toggable (limits fps)
  glfwSwapInterval(0);
  Renderer2D::registerContext(pWindow, mpWindow);
  lg::Input::registerContext(mpWindow);
  setCallbacks();
  glfwSetWindowUserPointer(mpWindow, &mEventDispatcher);
  int w, h;
  glfwGetWindowSize(mpWindow, &w, &h);
}

//! @brief Handles displaying data stored in all buffers
//!
//! @return None
void RenderWindow::display()
{
  glfwSwapBuffers(mpWindow);
}

//! @brief Gets window width
//!
//! @return Window width
uint32_t RenderWindow::getWindowWidth()
{
    return mWindowSize.x;
}

//! @brief Gets window height
//!
//! @return Window height
uint32_t RenderWindow::getWindowHeight()
{
  return mWindowSize.y;
}

//! @brief  Gets the Window Size
//!
//! @return Window Size in Vector format
const glm::uvec2& RenderWindow::getWindowSize()
{
  return mWindowSize;
}

//! @brief Checks whether window has been closed
//!
//! @return true if Window is open false otherwise
bool RenderWindow::isOpen()
{
  std::unique_lock<std::mutex> lock(mDataAccesMutex);
  return !glfwWindowShouldClose(mpWindow);
}

RenderWindow::~RenderWindow()
{
  Renderer2D::unregisterContext(mpWindow);
  lg::Input::unregisterContext(mpWindow);
  glfwDestroyWindow(mpWindow);
}

//! @brief Sets the current window to be the Current OpenGL context useful for working with multiple windows must be called before any GL Funciton Call
//!
//! @return None
void RenderWindow::setActive()
{
  glfwMakeContextCurrent(mpWindow);
  glewExperimental = GL_TRUE;
  glewInit();
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
  return lg::Input::popEvent(rEvent, mpWindow);
}

std::shared_ptr<RenderWindow> RenderWindow::createSharedWindow()
{
  if(nullptr == mpWindow)
  {
    return nullptr;
  }

  // glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
  std::shared_ptr<RenderWindow> window = std::make_shared<RenderWindow>(800, 600, "A shared window", mpWindow);
  setActive();
  // Need params here in function
  return window;
}

//! @brief Sets all callbacks used by LestGui
//!
//! @return None
void RenderWindow::setCallbacks()
{
  glfwSetCursorPosCallback(mpWindow, lg::Mouse::mousePositionCallback);
  glfwSetMouseButtonCallback(mpWindow, lg::Mouse::mouseButtonCallback);
  glfwSetKeyCallback(mpWindow, lg::Keyboard::keyCallback);
  glfwSetWindowSizeCallback(mpWindow, lg::Window::windowResizeCallback);
}

void RenderWindow::setWindowTitle(const std::string& crTitle)
{
  glfwSetWindowTitle(mpWindow, crTitle.c_str());
}