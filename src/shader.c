#include "shader.h"

const char *vertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShader = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

Shader::Shader() {
  uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertexShader, NULL);
  glCompileShader(vs);
  uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragmentShader, NULL);
  glCompileShader(fs);
  shader = glCreateProgram();
  glAttachShader(shader, vs);
  glAttachShader(shader, fs);
  glLinkProgram(shader);

  glDeleteShader(vs);
  glDeleteShader(fs);
}

Shader::~Shader() {

}

void Shader::bind() {
  GLCall(glUseProgram(shader));
}

void Shader::unbind() {

}