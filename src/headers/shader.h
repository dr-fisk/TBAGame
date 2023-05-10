#ifndef SHADER_H
#define SHADER_H

#include "common.h"
#include "glcommon.h"

struct ShaderProgSource {
  std::string vertexShader;
  std::string fragmentShader;
};

class Shader {
  public:
    Shader(){}
    Shader(const std::string &crFilePath);
    ~Shader();
    void bind() const;
    void unbind() const;
    uint32_t getShaderId();
  private:
    uint32_t mShaderID;
    ShaderProgSource parseShader(const std::string &crFilePath);
    uint32_t createShader(const std::string &crVertexShader, const std::string &crFragmentShader);
    uint32_t compileShader(const uint32_t cType, const std::string &crSource);
};

#endif