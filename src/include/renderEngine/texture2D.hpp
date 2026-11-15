#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <vector>
#include <string>
#include <cstdint>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/vec2.hpp"

//! @brief Texture class for rendering images
class Texture2D
{
  public:
    //! @brief Default destructor uses RAII
    Texture2D();

    //! @brief Copy Constructor
    //!
    //! @param rTexture[in] Texture to copy
    Texture2D(const Texture2D& rTexture);

    //! @brief Creates Texture2D Buffer
    //!
    //! @param[in] cHeight         Height of Texture2D
    //! @param[in] cWidth          Width of Texture2D
    //! @param[in] cInternalFormat Specifies the number of color components in the texture
    //! @param[in] cFormat Specifies the number of color components in the texture
    //!
    //! @return 0 on successful create
    //! @return -1 on failed create 
    int8_t create(const uint32_t cHeight, const uint32_t cWidth, const int32_t cInternalFormat=GL_RGBA8,
                  const int32_t cFormat=GL_RGBA);
  
    //! @brief Update specific part of Buffer from Texture2D
    //!
    //! @param[in] pBuffer      Data to place into Texture2D Buffer
    //! @param[in] crDimensions Dimensions of Buffer Data (L x W)
    //! @param[in] crOffset     Offset in Texture2D Buffer to store data in
    //! @param[in] cFormat      Specifies the format of the pixel data
    //! @param[in] cType        Specifies the data type of the pixel data
    //!
    //! @return 0 if data in Texture2D Buffer updated successfully
    //! @return -1 if data in Texture2D Buffer updated unsuccessfully
    int8_t update(void *pBuffer, const glm::uvec2& crDimensions, const glm::uvec2& crOffset,
                  const int32_t cFormat=GL_RGBA, const int32_t cType=GL_UNSIGNED_BYTE);
    //! @brief Binds Texture2D Resource and sets active slot
    //!
    //! @param[in] cSlot Specific Slot number to set active
    void bind(const int32_t cSlot) const;

    //! @brief Binds Texture with no slot
    void bind() const;

    //! @brief Unbinds Texture2D Resource
    void unbind() const;
    
    //! @brief Gets Texture2D ID associated with Texture2D Resource
    //!
    //! @return Texture2D ID
    uint32_t getTextureId() const;

    //! @brief Gets Size of Texture2D
    //!
    //! @return Size of Texture2D in (l x w)
    glm::uvec2 getSize() const;

    //! @brief Destructs Texture2D Object
    ~Texture2D();

    //! @brief Assignment Operator
    //!
    //! @param[in] rhs Texture to assign to this object
    void operator=(const Texture2D& rhs);
    
    //! @brief Equality Operator
    //!
    //! @param rhs[in] Texture to compare to this object
    //!
    //! @return true if textures are the same, false otherwise 
    bool operator==(const Texture2D& rhs) const;

    //! @brief Sets the min filter of the texture
    //!
    //! @param[in] cMinFilter Min Filter to set 
    void setMinFilter(const int32_t cMinFilter);

    //! @brief Sets the magnification filter of the texture
    //!
    //! @param[in] cMagFilter Magnification Filter to set 
    void setMagFilter(const int32_t cMagFilter);
    
    //! @brief Sets the max levels for the texture
    //!
    //! @param[in] cLevels Number of levels 
    void setMaxLevels(const int32_t cLevels);

    //! @brief Gets the min filter of the texture
    //!
    //! @return Min Filter 
    int32_t getMinFilter() const;

    //! @brief Gets the mag filter of the texture
    //!
    //! @return Mag Filter
    int32_t getMagFilter() const;
    
    //! @brief Gets the Texture Wrap S of the texture
    //!
    //! @return Texture Wrap S
    int32_t getTextureWrapS() const;

    //! @brief Gets the Texture Wrap T of the texture
    //!
    //! @return Texture Wrap T
    int32_t getTextureWrapT() const;

    //! @brief Gets the Number of Levels
    //!
    //! @return Number of levels in texture
    int32_t getNumLevels() const;

    //! @brief Determine if texture needs a refresh
    //!
    //! @return true if texture needs a refresh false otherwise
    bool needsRefresh() const;
  private:
    //! Texture ID
    uint32_t mTextureId;

    //! W x H of texture
    glm::uvec2 mSize;

    //! Flag to determine if texture buffer is generated
    bool mBufferGenerated;

    //! Buffer of the texture
    std::vector<uint8_t> mBuffer;

    //! Min Filter
    int32_t mMinFilter = GL_NEAREST;
    
    //! Mag Filter
    int32_t mMagFilter = GL_NEAREST;

    //! Texture Wrap S
    int32_t mTextureWrapS = GL_CLAMP_TO_EDGE;
    
    //! Texture Wrap T
    int32_t mTextureWrapT = GL_CLAMP_TO_EDGE;

    //! Number of levels to texture
    int32_t mNumLevels = 1;

    //! Flag indicating state has changed
    bool mIsDirty = true;
};

#endif