#include "resource/resource.hpp"

//! @brief Wrapper function for Texture Update to update specific part of Buffer from Texture
//!
//! @param[in] crTag          Tag of Resource
//! @param[in] prResourceMngr Render Engine manager
//!
//! @return Resource Object
Resource::Resource(const std::string& crTag, std::shared_ptr<ResourceManager>& prResourceMngr)
: mTag(crTag), mpResourceManager(prResourceMngr)
{
}