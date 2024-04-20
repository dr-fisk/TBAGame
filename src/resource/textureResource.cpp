#include "resource/textureResource.hpp"

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
//! @param[in] cInternalFormat Specifies the number of color components in the texture
//! @param[in] cFormat         Format of Texture
//!
//! @return Texture Resource object
TextureResource::TextureResource(const std::string& crTag, std::shared_ptr<RenderEngine>& prRenderEngine,
                                 const glm::uvec2& crDimensions, const int32_t cInternalFormat,
                                 const int32_t cFormat)
                                 : Resource(crTag, prRenderEngine),
                                   mpTexture(prRenderEngine->createTexture(crTag, crDimensions.y, crDimensions.x,
                                             cInternalFormat, cFormat))
{
}

//! @brief Wrapper function for Texture Update to update specific part of Buffer from Texture
//!
//! @param[in] pBuffer      Data to place into Texture Buffer
//! @param[in] crDimensions Dimensions of Buffer Data (L x W)
//! @param[in] crOffset     Offset in Texture Buffer to store data in
//! @param[in] cFormat      Specifies the format of the pixel data
//! @param[in] cType        Specifies the data type of the pixel data
//!
//! @return 0 if data in Texture Buffer updated successfully
//! @return -1 if data in Texture Buffer updated unsuccessfully
int8_t TextureResource::update(void *pBuffer, const glm::uvec2& crDimensions, const glm::uvec2& crOffset,
                               const int32_t cFormat, const int32_t cType)
{
  if(nullptr == mpTexture)
  {
    return -1;
  }

  return mpTexture->update(pBuffer, crDimensions, crOffset, cFormat, cType);
}

//! @brief Wrapper function for Texture Update to update specific part of Buffer from Texture
//!
//! @param[in] pBuffer      Data to place into Texture Buffer
//! @param[in] crDimensions Dimensions of Buffer Data (L x W)
//! @param[in] crOffset     Offset in Texture Buffer to store data in
//!
//! @return 0 if Texture in binded
//! @return -1 if Texture not binded
int8_t TextureResource::bind(int32_t cActiveSlot) const
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
void TextureResource::unbind() const
{
  mpTexture->unbind();
}

//! @brief Gets Texture ID associated with Texture Resource
//!
//! @return Texture ID
uint32_t TextureResource::getTextureId() const
{
  return mpTexture->getTextureId();
}

//! @brief Wrapper function to get Texture Dimensions
//!
//! @return (0, 0) if Texture is nullptr
//! @return Dimensions of Texture otherwise
glm::uvec2 TextureResource::getSize() const
{
  if(nullptr == mpTexture)
  {
    return {0, 0};
  }

  return mpTexture->getSize();
}

//! @brief Destructs and removes itself from Resource Manager
//!
//! @return None
TextureResource::~TextureResource()
{
  if(!mTag.empty())
  {
    mpRenderEngine->removeResource(mTag);
  }
}

bool TextureResource::operator==(const TextureResource& rhs) const
{
  return mpTexture->getTextureId() == rhs.getTextureId();
}