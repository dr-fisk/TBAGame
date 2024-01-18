#ifndef GL_COMMON_H
#define GL_COMMON_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "color.h"
#include "exception.h"
#include "glm/vec2.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

struct Vertex {
  glm::vec2 bottomLeft;
  lg::Color rgba1;
  glm::vec2 textCoord1;
  GLfloat textureIndex1;
  glm::vec2 bottomRight;
  lg::Color rgba2;
  glm::vec2 textCoord2;
  GLfloat textureIndex2;
  glm::vec2 topRight;
  lg::Color rgba3;
  glm::vec2 textCoord3;
  GLfloat textureIndex3;
  glm::vec2 topLeft;
  lg::Color rgba4;
  glm::vec2 textCoord4;
  GLfloat textureIndex4;
  //update for texture coords and texture index 3 floats
};

extern void GLClearError();

extern bool GLLogCall(const char* function, const char *file, int line);

extern GLfloat gWindowWidth;
extern GLfloat gWindowHeight;
//Temp stuff
extern uint16_t gFrames;
extern uint16_t gFps;

#endif