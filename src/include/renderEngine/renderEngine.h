#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <map>
#include <string>

#include "renderEngine/texture.h"

class RenderEngine
{
  public:
    RenderEngine() = default;
    ~RenderEngine() = default;
    Texture& createTexture(const std::string& crTag, const uint32_t cHeight, const uint32_t cWidth, void* pBuffer);
    Texture& createTexture(const std::string& crTag, const std::string& crPath);
  private:
    std::map<std::string, Texture> mTextureCache;
    std::map<uint32_t, std::string> mTextureIdToTag;
};

#endif