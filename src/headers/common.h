#define GLEW_STATIC
#include <iostream>
#include <cmath>
#include <stack>
#include <queue>
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
#include "Vector2D.h"
#include "Vector4f.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

extern void GLClearError();

extern bool GLLogCall(const char* function, const char *file, int line);
