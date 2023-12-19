#ifndef GL_COMMON_H
#define GL_COMMON_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vector.h"
#include "color.h"
#include "exception.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

struct Vertex {
  Vector2<GLfloat> bottomLeft;
  lg::Color rgba1;
  Vector2<GLfloat> textCoord1;
  GLfloat textureIndex1;
  Vector2<GLfloat> bottomRight;
  lg::Color rgba2;
  Vector2<GLfloat> textCoord2;
  GLfloat textureIndex2;
  Vector2<GLfloat> topRight;
  lg::Color rgba3;
  Vector2<GLfloat> textCoord3;
  GLfloat textureIndex3;
  Vector2<GLfloat> topLeft;
  lg::Color rgba4;
  Vector2<GLfloat> textCoord4;
  GLfloat textureIndex4;
  //update for texture coords and texture index 3 floats
};

extern void GLClearError();

extern bool GLLogCall(const char* function, const char *file, int line);

extern GLfloat gWindowWidth;
extern GLfloat gWindowHeight;

#endif