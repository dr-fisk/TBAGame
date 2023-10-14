#ifndef STATE_H
#define STATE_H

#include "common.h"
#include "glcommon.h"
#include "renderWindow.h"
#include "drawable/mesh.h"
#include "pngFont.h"
#include "drawable/pngText.h"
#include "drawable/batchBuffer.h"

class State {
  public:
    State(const std::stack<std::shared_ptr<State>> &crStates, const std::shared_ptr<BatchBuffer> &crpBatchBuffer);
    ~State();
    virtual void render(const std::shared_ptr<RenderTarget> &) = 0;
    virtual void update() = 0;
    virtual bool shouldStateExit() = 0;
  protected:
    std::stack<std::shared_ptr<State>> mStates;
    std::shared_ptr<BatchBuffer> mpBatchBuffer;
};

#endif