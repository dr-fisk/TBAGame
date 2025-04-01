#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include <memory>
#include <mutex>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window/renderTarget.hpp"
#include "event/event.hpp"
#include "event/applicationEventDispatcher.hpp"
#include "event/lestRenderEngineEvent.hpp"
#include "input/windowEvent.hpp"

class RenderWindow : public RenderTarget
{
    public:
    
      //! @brief Initializes opengl window
      //!
      //! @param[in]  cWindowWidth  Window width
      //! @param[in]  cWindowHeight Window height
      //! @param[in]  cpTitle       Window title
      //! @param[out] pWindow       Allows sharing of resources for when needing multiple windows, is NULL otherwise
      //!
      //! @return None
      RenderWindow(const uint32_t cWindowWidth, const uint32_t cWindowHeight, const char *cpTitle,
                   GLFWwindow *pWindow=nullptr);
     
      //! @brief Default Destructor
      ~RenderWindow();

      //! @brief Checks whether window has been closed
      //!
      //! @return true if Window is open false otherwise
      bool isOpen();
      
      //! @brief Gets window width
      //!
      //! @return Window width
      uint32_t getWindowWidth();

      //! @brief Gets window height
      //!
      //! @return Window height
      uint32_t getWindowHeight();

      //! @brief Handles displaying data stored in all buffers
      //!
      //! @return None
      void display();

      //! @brief Sets the current window to be the Current OpenGL context useful for working with multiple windows must be called before any GL Funciton Call
      //!
      //! @return None
      void setActive();
      
      //! @brief Inits GL Attributes and must be called after setActive
      //!
      //! @return None
      void initWindow();

      //! @brief Getter function for getting a reference to the currnet Gl Window
      //! 
      //! @return GLFWwindow* - A refernce to the GL Window
      GLFWwindow *getGlWindow();

      //! @brief  Gets the Window Size
      //!
      //! @return Window Size in Vector format
      const glm::uvec2& getWindowSize();

      //! @brief Sets the window title
      //!
      //! @param[in] crTitle Window Title
      //!
      //! @return None 
      void setWindowTitle(const std::string& crTitle);
      
      //! @brief Creates a shared window
      //!
      //! @return Shared Window
      std::shared_ptr<RenderWindow> createSharedWindow();

      //! @brief Returns whether window is focused or not
      //!
      //! @return true if focused, false otherwise 
      bool isFocused() const;
    private:
      //! @brief Sets all callbacks used by LestGui
      //!
      //! @return None
      void setCallbacks();

      //! @brief Handles Window Focus Event
      //!
      //! @param[out] rEvent WindowFocusEvent
      //!
      //! @return None 
      void onWindowFocusEvent(lre::WindowFocusEvent& rEvent);

      glm::uvec2 mWindowSize;
      std::string mTitle;
      GLFWwindow *mpWindow;
      std::mutex mDataAccesMutex;
      lre::ApplicationEventDispatcher<lre::LestRenderEngineEvents> mEventDispatcher;
      EventSubscriber<lre::WindowFocusEvent> mFocusSub;
      bool mFocused;
      static bool msFirstInit;
};

#endif