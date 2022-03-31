#include "shader.h"

/* Function:    Shader
   Description: Constructs a shader program
   Parameters:  string - File path location of shader code
   Returns:     None
 */
Shader::Shader(const std::string &filePath) {
  ShaderProgSource shaderProg = parseShader(filePath);
  shaderID = createShader(shaderProg.vertexShader, shaderProg.fragmentShader);
}

/* Function:    ~Shader
   Description: Deletes shader program
   Parameters:  None
   Returns:     None
 */
Shader::~Shader() {
  GLCall(glDeleteProgram(shaderID));
}

/* Function:    bind
   Description: Binds shader program to opengl for use
                Call before drawing to window
   Parameters:  None
   Returns:     None
 */
void Shader::bind() const {
  GLCall(glUseProgram(shaderID));
}

/* Function:    unbind
   Description: Unbinds the shader from opengl
   Parameters:  None
   Returns:     None 
 */
void Shader::unbind() const {
  GLCall(glUseProgram(0));
}

/* Function:    parseShader
   Description: Opens shader file and parses to construct strings
   Parameters:  string - File location for shader code
   Returns:     ShaderProgSource - Separate strings for shader components
 */
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

/* Function:    draw
   Description: Handles rendering all buffers to be displayed on window
                Calls should look like clear()->render()->display() then loop
   Parameters:  string - Vertex Shader code
                string - Fragment Shader code
   Returns:     uint32_t - Shader ID
 */
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

/* Function:    draw
   Description: Compiles and constructs shader components
   Parameters:  uint32_t - Shader component
                string   - Shader component code
   Returns:     uint32_t - Shader component ID
 */
uint32_t Shader::compileShader(uint32_t type, const std::string &source) {
  uint32_t ID = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(ID, 1, &src, nullptr);
  glCompileShader(ID);
  return ID;
}