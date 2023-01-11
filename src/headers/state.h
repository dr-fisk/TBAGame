#ifndef STATE_H
#define STATE_H

#include "common.h"
#include "renderWindow.h"
#include "mesh.h"
#include "font.h"
#include "text.h"
#include "batchBuffer.h"

class State {
  public:
    State(const std::stack<std::shared_ptr<State>> &crStates);
    ~State();
    virtual void render(const std::shared_ptr<RenderTarget> &) = 0;
    virtual void update() = 0;
    virtual bool shouldStateExit() = 0;
  private:
    std::stack<std::shared_ptr<State>> mStates;
};

#endif