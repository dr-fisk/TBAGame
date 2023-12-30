#ifndef STATE_H
#define STATE_H

#include <stack>

#include "common.h"
#include "glcommon.h"
#include "renderWindow.h"
#include "renderEngine/batchBuffer.h"
#include "renderEngine/renderEngine.h"

class State {
  public:
    State(const std::stack<std::shared_ptr<State>>& crStates, const std::shared_ptr<RenderEngine>& crpRenderEngine,
          const std::shared_ptr<BatchBuffer>& crpBatchBuffer);
    ~State();
    virtual void render(const std::shared_ptr<RenderTarget> &) = 0;
    virtual void update(const std::shared_ptr<RenderTarget> &crpTarget) = 0;
    virtual bool shouldStateExit() = 0;
  protected:
    std::stack<std::shared_ptr<State>> mStates;
    std::shared_ptr<RenderEngine> mpRenderEngine;
    std::shared_ptr<BatchBuffer> mpBatchBuffer;
};

#endif