#ifndef STATE_H
#define STATE_H

#include <stack>

#include "common.h"
#include "glcommon.h"
#include "window/renderWindow.h"
#include "renderEngine/renderEngine.h"

class State
{
  public:
    State(const std::stack<std::shared_ptr<State>>& crStates, const std::shared_ptr<RenderTarget>& crpWindow,
          const std::shared_ptr<RenderEngine>& crpRenderEngine);
    ~State();
    virtual void render(const std::shared_ptr<RenderTarget>& crpTarget);
    virtual void update(const std::shared_ptr<RenderTarget>& crpTarget, const float cDeltaTime) = 0;
    virtual bool shouldStateExit() = 0;
  protected:
    std::stack<std::shared_ptr<State>> mStates;
    std::shared_ptr<RenderEngine> mpRenderEngine;
    std::shared_ptr<RenderTarget> mpWindow;
};

#endif