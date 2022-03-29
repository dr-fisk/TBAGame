#include "shader.h"

Shader::Shader() {
}

Shader::Shader(const std::string &filePath) {
  ShaderProgSource shaderProg = parseShader(filePath);
  shaderID = createShader(shaderProg.vertexShader, shaderProg.fragmentShader);
}

Shader::~Shader() {
}

void Shader::deleteShader() const {
  GLCall(glDeleteProgram(shaderID));
}

void Shader::bind() const {
  GLCall(glUseProgram(shaderID));
}

void Shader::unbind() const {
  GLCall(glUseProgram(0));
  std::cout << "What\n";
}

ShaderProgSource Shader::parseShader(const std::string &filePath) {
  std::ifstream fp(filePath);

  enum class ShaderType {
      NONE = -1, VERTEX = 0, FRAGMENT = 1
  };

  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;

  while (getline(fp, line)) {
      if (line.find("#shader") != std::string::npos) {
        if (line.find("vertex") != std::string::npos) {
          type = ShaderType::VERTEX;
        } else if (line.find("fragment") != std::string::npos) {
          type = ShaderType::FRAGMENT;
        }
      } else {
        ss[(int)type] << line << '\n';
      }
  }

  return {ss[0].str(), ss[1].str()};
}

uint32_t Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
  uint32_t vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  uint32_t fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
  uint32_t ID = glCreateProgram();
  glAttachShader(ID, vs);
  glAttachShader(ID, fs);
  glLinkProgram(ID);
  glValidateProgram(ID);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return ID;
}

uint32_t Shader::compileShader(uint32_t type, const std::string &source) {
  uint32_t ID = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(ID, 1, &src, nullptr);
  glCompileShader(ID);
  return ID;
}