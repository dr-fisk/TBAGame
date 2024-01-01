#ifndef EXCEPTION_STATE_H
#define EXCEPTION_STATE_H

#include <memory>
#include <string>
#include <stack>

#include "exception.h"
#include "window/renderWindow.h"
#include "state.h"
#include "renderEngine/batchBuffer.h"

class ExceptionState : public State {
  public:
    ExceptionState(const std::stack<std::shared_ptr<State>>& crStates,
                    std::shared_ptr<RenderEngine> cpRenderEngine, 
                    std::shared_ptr<BatchBuffer> cpBatchBuffer,
                    const std::string& crError);
    ~ExceptionState();
    void update(const std::shared_ptr<RenderTarget> &crpTarget);
    bool shouldStateExit();
  private:
    std::shared_ptr<RenderWindow> mpWindow;
    std::string mError;
    BatchBuffer mTestBB;
    BatchBuffer mErrorBatch;
};

#endif