#include <iostream>

#include "renderEngine/renderEngine.h"

//! @brief Wrapper function to create Texture
//!
//! @param[in] crTag           Tag associated with texture to avoid creating repeats
//! @param[in] cHeight         Height of Texture
//! @param[in] cWidth          Width of Texture
//! @param[in] cInternalFormat Specifies the number of color components in the texture
//! @param[in] cFormat         Format of Texture
//!
//! @return Texture Object
Texture* RenderEngine::createTexture(const std::string& crTag, const uint32_t cHeight, const uint32_t cWidth,
                                     const int32_t cInternalFormat, const int32_t cFormat)
{
  if(mTextureCache.find(crTag) != mTextureCache.end())
  {
    mTextureCache[crTag].Count ++;
    return &mTextureCache[crTag].ResourceType;
  }

  mTextureCache[crTag].ResourceType.create(cHeight, cWidth, cInternalFormat, cFormat);
  mTextureCache[crTag].Count ++;
  mTextureIdToTag[mTextureCache[crTag].ResourceType.getTextureId()] = crTag;
  return &mTextureCache[crTag].ResourceType;
}

//! @brief Checks to see if Texture with Tag already exists
//!
//! @param[in] crTag Tag to check against map
//!
//! @return true if Texture exists
//! @return false if Texture does not exist
bool RenderEngine::textureExists(const std::string& crTag)
{
  return mTextureCache.find(crTag) != mTextureCache.end();
}

//! @brief Checks to see if Texture with Tag already exists
//!        Note: Will throw exception if Key is not in map
//!
//! @param[in] cId ID of Texture to get Tag from
//!
//! @return Texture Tag
std::string RenderEngine::getTag(const uint32_t cId)
{
  return mTextureIdToTag.at(cId);
}

//! @brief Decrements Resource Reference Counter, if count == 0 then it is removed from map
//!
//! @param[in] crTag Tag to check against map
//!
//! @return None
void RenderEngine::removeResource(const std::string& crTag)
{
  mTextureCache[crTag].Count --;

  if(0 == mTextureCache[crTag].Count)
  {
    mTextureCache.erase(crTag);
  }
}