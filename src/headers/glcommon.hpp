#ifndef GL_COMMON_HPP
#define GL_COMMON_HPP

#include <cstdint>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

extern void GLClearError();

extern bool GLLogCall(const char* function, const char *file, int line);

//Temp stuff
extern uint16_t gFrames;
extern uint16_t gFps;

#endif