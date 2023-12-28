#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <memory>

#include "renderEngine/renderEngine.h"

class Resource
{
  public:
    Resource() = default;
    Resource(const std::string& crTag, std::shared_ptr<RenderEngine>& prRenderEngine);
    virtual ~Resource() = default;
  protected:
    const std::string mTag;
    std::shared_ptr<RenderEngine> mpRenderEngine;
};

#endif