#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include "glcommon.h"

class RenderCommand
{
  public:
    static void init()
    {
      if(!glfwInit())
      {
        std::cout << "Failed to open window" << std::endl;
        exit(-1);
      }

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    static void setClearColor(const float cR, const float cG, const float cB, const float cA)
    {
      GLCall(glClearColor(cR, cG, cB, cA));
    }

    static void clear()
    {
      GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    static void pollEvents()
    {
      GLCall(glfwPollEvents());
    }

    static void enableBlend()
    {
      GLCall(glEnable(GL_BLEND));
      GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }

    static void disableBlend()
    {
      GLCall(glDisable(GL_BLEND));
    }
  private:
};

#endif