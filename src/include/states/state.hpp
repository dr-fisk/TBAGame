#ifndef STATE_HPP
#define STATE_HPP

#include <stack>

#include "common.hpp"
#include "glcommon.hpp"
#include "window/renderWindow.hpp"
#include "renderEngine/renderEngine.hpp"

class State
{
  public:
    State(const std::stack<std::shared_ptr<State>>& crStates, const std::shared_ptr<RenderTarget>& crpWindow,
          const std::shared_ptr<RenderEngine>& crpRenderEngine);
    ~State();
    virtual void render(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime);
    virtual void update(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime);
    virtual void fixedUpdate(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime) = 0;
    virtual void lateUpdate(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime);
    virtual bool shouldStateExit() = 0;
  protected:
    std::stack<std::shared_ptr<State>> mStates;
    std::shared_ptr<RenderEngine> mpRenderEngine;
    std::shared_ptr<RenderTarget> mpWindow;
};

#endif