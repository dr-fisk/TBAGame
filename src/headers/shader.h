#ifndef SHADER_H
#define SHADER_H

#include "common.h"

class Shader {
  public:
    Shader();
    ~Shader();
    void bind();
    void unbind();
  private:
    uint32_t shader;
};

#endif