#ifndef EXCEPTION_STATE_H
#define EXCEPTION_STATE_H

#include "exception.h"
#include "state.h"

class ExceptionState : public State {
  public:
      ExceptionState(const std::stack<std::shared_ptr<State>> &crStates, const std::shared_ptr<BatchBuffer> &crpBatchBuffer, const std::string &crError);
      ~ExceptionState();
      void render(const std::shared_ptr<RenderTarget> &crpTarget);
      void update();
      bool shouldStateExit();
  private:
    std::shared_ptr<RenderWindow> mpWindow;
    std::string mError;
    Mesh mMesh;
    Mesh mMesh2;
    BatchBuffer mTestBB;
    BatchBuffer mErrorBatch;
    PngFont mFont;
};

#endif