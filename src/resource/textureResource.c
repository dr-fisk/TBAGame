#include "resource/textureResource.h"

//! @brief Default Constructor
//!
//!
//! @return Texture Resource Object
TextureResource::TextureResource() : mpTexture(nullptr)
{
}

//! @brief Construct Texture Resource
//!
//! @param[in] crTag          Tag associated with resource
//! @param[in] prRenderEngine Render Engine manager
//! @param[in] crDimensions   Dimensions to create new Texture
//!
//! @return Texture Resource object
TextureResource::TextureResource(const std::string& crTag, std::shared_ptr<RenderEngine>& prRenderEngine,
                                 const Vector2<uint32_t>& crDimensions)
                                 : Resource(crTag, prRenderEngine),
                                   mpTexture(&prRenderEngine->createTexture(crTag, crDimensions.y, crDimensions.x))
{
}

//! @brief Wrapper function for Texture Update to update specific part of Buffer from Texture
//!
//! @param[in] pBuffer      Data to place into Texture Buffer
//! @param[in] crDimensions Dimensions of Buffer Data (L x W)
//! @param[in] crOffset     Offset in Texture Buffer to store data in
//!
//! @return 0 if data in Texture Buffer updated successfully
//! @return -1 if data in Texture Buffer updated unsuccessfully
int8_t TextureResource::update(void *pBuffer, const Vector2<uint32_t>& crDimensions, const Vector2<uint32_t>& crOffset)
{
  if(nullptr == mpTexture)
  {
    return -1;
  }

  return mpTexture->update(pBuffer, crDimensions, crOffset);
}

//! @brief Wrapper function for Texture Update to update specific part of Buffer from Texture
//!
//! @param[in] pBuffer      Data to place into Texture Buffer
//! @param[in] crDimensions Dimensions of Buffer Data (L x W)
//! @param[in] crOffset     Offset in Texture Buffer to store data in
//!
//! @return 0 if Texture in binded
//! @return -1 if Texture not binded
int8_t TextureResource::bind(uint32_t cActiveSlot)
{
  if(nullptr == mpTexture)
  {
    return -1;
  }

  mpTexture->bind(cActiveSlot);

  return 0;
}

//! @brief Unbinds Texture Resource
//!
//! @return None
void TextureResource::unbind()
{
  mpTexture->unbind();
}

//! @brief Gets Cache ID of Texture
//!
//! @return Cache ID
uint8_t TextureResource::getCacheId()
{
  return mpTexture->getCacheId();
}

//! @brief Gets Texture ID associated with Texture Resource
//!
//! @return Texture ID
uint32_t TextureResource::getTextureId()
{
  return mpTexture->getTextureId();
}

//! @brief Wrapper function to get Texture Dimensions
//!
//! @return (0, 0) if Texture is nullptr
//! @return Dimensions of Texture otherwise
Vector2<uint32_t> TextureResource::getSize()
{
  if(nullptr == mpTexture)
  {
    return {0, 0};
  }

  return mpTexture->getSize();
}

//! @brief Determine if TextureIndex needs updating
//!
//! @return true if cache ID was updated false otherwise
bool TextureResource::updateTextureIndex()
{
  return mpTexture->updateTextureIndex();
}

//! @brief Unset CacheUpdated flag
//!
//! @return None
void TextureResource::unsetCacheUpdate()
{
  mpTexture->unsetCacheUpdate();
}

//! @brief Destructs and removes itself from Resource Manager
//!
//! @return None
TextureResource::~TextureResource()
{
  if(mTag.empty())
  {
    mpRenderEngine->removeResource(mTag);
  }
}