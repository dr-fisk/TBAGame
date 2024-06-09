#ifndef CONTEXT_RESOURCE_MANAGER
#define CONTEXT_RESOURCE_MANAGER

#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

template<typename T>
class ContextResourceManager
{
  public:
    ContextResourceManager();
    ~ContextResourceManager() = default;
    class ContextResourceManagerImpl;
  private:
    std::unique_ptr<ContextResourceManagerImpl> mpContextManager;
};

#endif