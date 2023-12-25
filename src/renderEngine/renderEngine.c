#include "renderEngine/renderEngine.h"

Texture& RenderEngine::createTexture(const std::string& crTag, const uint32_t cHeight, const uint32_t cWidth,
                                     void* pBuffer)
{
  if(mTextureCache.find(crTag) != mTextureCache.end())
  {
    return mTextureCache[crTag];
  }

  mTextureCache[crTag].loadTexture(pBuffer, cHeight, cWidth, 8);
  mTextureIdToTag[mTextureCache[crTag].getTextureId()] = crTag;
  return mTextureCache[crTag];
}

Texture& RenderEngine::createTexture(const std::string& crTag, const std::string& crPath)
{
  if(mTextureCache.find(crTag) != mTextureCache.end())
  {
    return mTextureCache[crTag];
  }

  mTextureCache[crTag].loadTexture(crPath);
  mTextureIdToTag[mTextureCache[crTag].getTextureId()] = crTag;
  return mTextureCache[crTag];
}