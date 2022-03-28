#ifndef SHADER_H
#define SHADER_H

#include "common.h"

struct ShaderProgSource {
  std::string vertexShader;
  std::string fragmentShader;
};

class Shader {
  public:
    Shader();
    Shader(const std::string &filePath);
    ~Shader();
    void bind() const;
    void unbind() const;
  private:
    uint32_t shaderID;
    ShaderProgSource parseShader(const std::string &filePath);
    uint32_t createShader(const std::string& vertexShader, const std::string& fragmentShader);
    uint32_t compileShader(uint32_t type, const std::string &source);
};

#endif