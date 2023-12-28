#include <fstream>
#include <iostream>
#include <sstream>

#include "glcommon.h"
#include "renderEngine/shader.h"

//! @brief Constructs a shader program
//!
//! @param[in] crFilePath File path location of shader code
//!
//! @return None
Shader::Shader(const std::string& crFilePath)
{
  ShaderProgSource shaderProg = parseShader(crFilePath);
  mShaderID = createShader(shaderProg.vertexShader, shaderProg.fragmentShader);
}

//! @brief Deletes shader program
//! 
//! @return None
Shader::~Shader()
{
  GLCall(glDeleteProgram(mShaderID));
}

//! @brief Binds shader program to opengl for use
//!        Call before drawing to window
//!
//! @return None
void Shader::bind() const
{
  GLCall(glUseProgram(mShaderID));
}

//! @brief Unbinds the shader from opengl
//!
//! @return None
void Shader::unbind() const
{
  GLCall(glUseProgram(0));
}

int32_t Shader::getUniform(const std::string &crVar)
{
  GLCall(int32_t location = glGetUniformLocation(mShaderID, crVar.c_str()));
  return location;
}

//! @brief Opens shader file and parses to construct strings
//!
//! @param[in] crFilePath location for shader code
//!
//! @return ShaderProgSource - Separate strings for shader components
ShaderProgSource Shader::parseShader(const std::string& crFilePath)
{
  std::ifstream fp(crFilePath);

  enum class ShaderType
  {
      NONE = -1, VERTEX = 0, FRAGMENT = 1
  };

  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;

  while(getline(fp, line))
  {
      if(line.find("#shader") != std::string::npos)
      {
        if(line.find("vertex") != std::string::npos)
        {
          type = ShaderType::VERTEX;
        }
        else if(line.find("fragment") != std::string::npos)
        {
          type = ShaderType::FRAGMENT;
        }
      }
      else
      {
        ss[(int)type] << line << '\n';
      }
  }

  return {ss[0].str(), ss[1].str()};
}

//! @brief Handles rendering all buffers to be displayed on window
//!        Calls should look like clear()->render()->display() then loop
//!
//! @param[in] crVertexShader   Vertex Shader code
//! @param[in] crFragmentShader Fragment Shader code
//!
//! @return Shader ID
uint32_t Shader::createShader(const std::string& crVertexShader, const std::string& crFragmentShader)
{
  uint32_t vs = compileShader(GL_VERTEX_SHADER, crVertexShader);
  uint32_t fs = compileShader(GL_FRAGMENT_SHADER, crFragmentShader);
  uint32_t ID = glCreateProgram();

  glAttachShader(ID, vs);
  glAttachShader(ID, fs);
  glLinkProgram(ID);
  glValidateProgram(ID);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return ID;
}

//! @brief Compiles and constructs shader components
//!
//! @param[in] cType Shader component
//! @param[in] Shader component code
//!
//! @return uint32_t - Shader component ID
uint32_t Shader::compileShader(const uint32_t cType, const std::string& crSource)
{
  uint32_t ID = glCreateShader(cType);
  const char* src = crSource.c_str();
  glShaderSource(ID, 1, &src, nullptr);
  glCompileShader(ID);

  int32_t result = 0;
  GLCall(glGetShaderiv(ID, GL_COMPILE_STATUS, &result));
  
  if(GL_FALSE == result)
  {
    int32_t length = 0;
    std::string msg;
    GLCall(glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &length));
    msg.resize(length);
    GLCall(glGetShaderInfoLog(ID, length, &length, &msg[0]));
    std::cout << "Failed to compile " << (cType == GL_FRAGMENT_SHADER ? "fragment" : "vertex") << " shader" <<
    std::endl;
    std::cout << msg << std::endl;
  }
  return ID;
}

//! @brief Getter function for member Id variable
//!
//! @return uint32_t - ID associated with the shader
uint32_t Shader::getShaderId()
{
  return mShaderID;
}