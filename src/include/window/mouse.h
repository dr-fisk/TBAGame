#ifndef MOUSE_H
#define MOUSE_H

#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/vec2.hpp"
#include "window/renderTarget.h"
#include "renderer/camera.h"

namespace lg
{
  namespace Mouse
  {
    void mousePositionCallback(GLFWwindow *pWindow, const double cX, const double cY);
    void mouseButtonCallback(GLFWwindow *pWindow, const int32_t cButton, const int32_t cAction, const int32_t cMods);

    glm::ivec2 getMousePosi();
    glm::vec2 getMousePosf();
    glm::vec2 getMousePosf(const OrthCamera& crCamera);
    glm::vec2 getMousePosf(const std::shared_ptr<RenderTarget>& crpTarget);
  }
}

#endif