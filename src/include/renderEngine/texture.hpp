#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>
#include <string>
#include <cstdint>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/vec2.hpp"

class Texture
{
  public:
    Texture();
    int8_t create(const uint32_t cHeight, const uint32_t cWidth, const int32_t cInternalFormat=GL_RGBA8,
                  const int32_t cFormat=GL_RGBA);
    int8_t update(void *pBuffer, const glm::uvec2& crDimensions, const glm::uvec2& crOffset,
                  const int32_t cFormat=GL_RGBA, const int32_t cType=GL_UNSIGNED_BYTE);
    void bind(const int32_t cSlot) const;
    void unbind() const;
    uint32_t getTextureId() const;
    glm::uvec2 getSize() const;
    ~Texture();
    Texture& operator=(const Texture& rhs) = delete;
    bool operator==(const Texture& rhs) const;
    Texture(const Texture& rhs) = delete;
  private:
    uint32_t mTextureId;
    glm::uvec2 mSize;
    uint32_t mBpp;
    bool mBufferGenerated;
    std::vector<uint8_t> mBuffer;
};

#endif