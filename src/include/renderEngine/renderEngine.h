#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <map>
#include <string>

#include "renderEngine/texture.h"
#include "glcommon.h"

class RenderEngine
{
  public:
    RenderEngine() = default;
    ~RenderEngine() = default;
    Texture* createTexture(const std::string& crTag, const uint32_t cHeight, const uint32_t cWidth,
                           const int32_t cInternalFormat=GL_RGBA8);
    bool textureExists(const std::string& crTag);
    std::string getTag(const uint32_t cId);
    void removeResource(const std::string& crTag);
  private:
    template <typename T>
    struct ResourceData
    {
      T ResourceType;
      uint32_t Count;
    };

    std::map<std::string, ResourceData<Texture>> mTextureCache;
    std::map<uint32_t, std::string> mTextureIdToTag;
};

#endif