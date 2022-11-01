#ifndef COMMON_H
#define COMMON_H

#ifdef __linux__
  #define LINUX
#elif _WIN32
  #define WINDOWS
#endif
#define GLEW_STATIC
#include <iostream>
#include <cmath>
#include <stack>
#include <queue>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include <stdint.h>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <fstream>
#include <memory>
#include <zlib.h>

#ifdef LINUX
  #include <arpa/inet.h>
#elif defined(WINDOWS)
  #include <winsock2.h>
#endif
#include "Vector2D.h"
#include "color.h"
#include "exception.h"

enum Status {
    FAIL,
    SUCCESS
};

#define MESH16_SIZE 256

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

struct RenderData {
  Vector2f bottomLeft;
  lg::Color rgba1;
  Vector2f bottomRight;
  lg::Color rgba2;
  Vector2f topRight;
  lg::Color rgba3;
  Vector2f topLeft;
  lg::Color rgba4;
};

extern void GLClearError();

extern bool GLLogCall(const char* function, const char *file, int line);

extern GLfloat gWindowWidth;
extern GLfloat gWindowHeight;


#endif