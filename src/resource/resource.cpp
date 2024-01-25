#include "resource/resource.hpp"

//! @brief Wrapper function for Texture Update to update specific part of Buffer from Texture
//!
//! @param[in] crTag          Tag of Resource
//! @param[in] prRenderEngine Render Engine manager
//!
//! @return Resource Object
Resource::Resource(const std::string& crTag, std::shared_ptr<RenderEngine>& prRenderEngine)
: mTag(crTag), mpRenderEngine(prRenderEngine)
{
}