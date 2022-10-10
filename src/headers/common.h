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

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

extern void GLClearError();

extern bool GLLogCall(const char* function, const char *file, int line);

#endif