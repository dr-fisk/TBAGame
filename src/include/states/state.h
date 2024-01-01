#ifndef STATE_H
#define STATE_H

#include <stack>

#include "common.h"
#include "glcommon.h"
#include "window/renderWindow.h"
#include "renderEngine/batchBuffer.h"
#include "renderEngine/renderEngine.h"

class State
{
  public:
    State(const std::stack<std::shared_ptr<State>>& crStates, std::shared_ptr<RenderEngine>& prRenderEngine,
          std::shared_ptr<BatchBuffer>& prBatchBuffer);
    ~State();
    void render(const std::shared_ptr<RenderTarget>& crpTarget);
    virtual void update(const std::shared_ptr<RenderTarget>& crpTarget) = 0;
    virtual bool shouldStateExit() = 0;
  protected:
    std::stack<std::shared_ptr<State>> mStates;
    std::shared_ptr<RenderEngine> mpRenderEngine;
    std::shared_ptr<BatchBuffer> mpBatchBuffer;
};

#endif