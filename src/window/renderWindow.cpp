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
  mEventDispatcher.addEventDispatcher<lre::WindowFocusEvent>();
  mFocusSub.setCallback(BIND_EVENT_FN(RenderWindow::onWindowFocusEvent));
  mEventDispatcher.attach(mFocusSub);

  //Vsync off later make it toggable (limits fps)
  glfwSwapInterval(0);
  Renderer2D::registerContext(pWindow, mpWindow);
  lg::Input::registerContext(mpWindow);
  setCallbacks();
  glfwSetWindowUserPointer(mpWindow, &mEventDispatcher);
  int w, h;
  glfwGetWindowSize(mpWindow, &w, &h);
  glfwSetInputMode(mpWindow, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
  mFocused = true;
}

void RenderWindow::display()
{
  if(mFocused)
  {
    glfwSwapBuffers(mpWindow);
  }
}

uint32_t RenderWindow::getWindowWidth()
{
    return mWindowSize.x;
}

uint32_t RenderWindow::getWindowHeight()
{
  return mWindowSize.y;
}

const glm::uvec2& RenderWindow::getWindowSize()
{
  return mWindowSize;
}

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

void RenderWindow::setActive()
{
  glfwMakeContextCurrent(mpWindow);
  glewExperimental = GL_TRUE;
  glewInit();
}

GLFWwindow* RenderWindow::getGlWindow()
{
  return mpWindow;
}

void RenderWindow::initWindow()
{
  GLCall(glClearColor(0.3, 0.0, 0.0, 1.0));
  // glClear(GL_COLOR_BUFFER_BIT);
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

void RenderWindow::setCallbacks()
{
  glfwSetCursorPosCallback(mpWindow, lg::Mouse::mousePositionCallback);
  glfwSetMouseButtonCallback(mpWindow, lg::Mouse::mouseButtonCallback);
  glfwSetKeyCallback(mpWindow, lg::Keyboard::keyCallback);
  glfwSetWindowSizeCallback(mpWindow, lg::Window::windowResizeCallback);
  glfwSetWindowFocusCallback(mpWindow, lg::Window::windowFocusCallback);
}

void RenderWindow::setWindowTitle(const std::string& crTitle)
{
  glfwSetWindowTitle(mpWindow, crTitle.c_str());
}

void RenderWindow::onWindowFocusEvent(lre::WindowFocusEvent& rEvent)
{
  mFocused = rEvent.isFocused();
}

bool RenderWindow::isFocused() const
{
  return mFocused;
}