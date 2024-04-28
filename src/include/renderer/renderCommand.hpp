#ifndef RENDER_COMMAND_HPP
#define RENDER_COMMAND_HPP

#include "glcommon.hpp"

class RenderCommand
{
  public:
    static void init()
    {
      if(!glfwInit())
      {
        std::cout << "Failed to init glfw." << std::endl;
        exit(-1);
      }

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    static void setClearColor(const float cR, const float cG, const float cB, const float cA)
    {
      glClearColor(cR, cG, cB, cA);
    }

    static void clear()
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    static void pollEvents()
    {
      glfwPollEvents();
    }

    static void enableBlend()
    {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    static void disableBlend()
    {
      glDisable(GL_BLEND);
    }

    static void setViewport(const uint32_t cX, const uint32_t cY, const uint32_t cWidth, const uint32_t cHeight)
    {
      glViewport(cX, cY, cWidth, cHeight);
    }
  private:
};

#endif