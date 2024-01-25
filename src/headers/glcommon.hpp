#ifndef GL_COMMON_HPP
#define GL_COMMON_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "color.hpp"
#include "exception.hpp"
#include "glm/vec2.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

struct Vertex
{
  glm::vec2 Pos;
  lg::Color Rgba;
  glm::vec2 TextCoord;
  float TextureIndex;
};

static const uint8_t sNumQuadVerts = 4;

extern void GLClearError();

extern bool GLLogCall(const char* function, const char *file, int line);

struct WindowView
{
  float WindowWidth;
  float WindowHeight;
  float x;
  float y;
};

extern WindowView gView;

//Temp stuff
extern uint16_t gFrames;
extern uint16_t gFps;

#endif