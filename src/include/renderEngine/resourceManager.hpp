#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>

#include "renderEngine/texture2D.hpp"

class ResourceManager
{
  public:
    ResourceManager() = default;
    ~ResourceManager() = default;
    Texture2D* createTexture(const std::string& crTag, const uint32_t cHeight, const uint32_t cWidth,
                           const int32_t cInternalFormat=GL_RGBA8, const int32_t cFormat=GL_RGBA);
    // const Texture& createTexture(const std::string& crTag, const uint32_t cHeight, const uint32_t cWidth,
    //                        const int32_t cInternalFormat=GL_RGBA8, const int32_t cFormat=GL_RGBA);
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

    std::map<std::string, ResourceData<Texture2D>> mTextureCache;
    std::map<uint32_t, std::string> mTextureIdToTag;
};

#endif