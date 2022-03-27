#include "common.h"

void GLClearError() {
  while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char *file, int line) {
  std::ofstream fp("errorLog.txt");
  
  while (GLenum error = glGetError()) {
    fp << "[OpenGL Error] (" << error << ") In " << function << " located in " << file << " on line number " << line << std::endl;
    fp.close();
    return 0;
  }
  fp.close();
  return 1;
}