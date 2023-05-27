#ifndef GL_COMMON_H
#define GL_COMMON_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vector2D.h"
#include "color.h"
#include "exception.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

struct RenderData {
  Vector2<GLfloat> bottomLeft;
  lg::Color rgba1;
  Vector2<GLfloat> bottomRight;
  lg::Color rgba2;
  Vector2<GLfloat> topRight;
  lg::Color rgba3;
  Vector2<GLfloat> topLeft;
  lg::Color rgba4;
};

extern void GLClearError();

extern bool GLLogCall(const char* function, const char *file, int line);

extern GLfloat gWindowWidth;
extern GLfloat gWindowHeight;

#endif