#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <cstdint>

struct ShaderProgSource
{
  std::string vertexShader;
  std::string fragmentShader;
};

class Shader
{
  public:
    Shader() = default;
    Shader(const std::string& crFilePath);
    ~Shader();
    void bind() const;
    void unbind() const;
    uint32_t getShaderId();
    int32_t getUniform(const std::string& crVar);
  private:
    ShaderProgSource parseShader(const std::string& crFilePath);
    uint32_t createShader(const std::string& crVertexShader, const std::string& crFragmentShader);
    uint32_t compileShader(const uint32_t cType, const std::string& crSource);

    uint32_t mShaderID;
};

#endif