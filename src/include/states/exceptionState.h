#ifndef EXCEPTION_STATE_H
#define EXCEPTION_STATE_H

#include <memory>
#include <string>
#include <stack>

#include "exception.h"
#include "window/renderWindow.h"
#include "state.h"

class ExceptionState : public State {
  public:
    ExceptionState(const std::stack<std::shared_ptr<State>>& crStates,
                   const std::shared_ptr<RenderTarget>& crpWindow,
                   const std::shared_ptr<RenderEngine> crpRenderEngine,
                   const std::string& crError);
    ~ExceptionState();
    void update(const std::shared_ptr<RenderTarget>& crpTarget, const float cDeltaTime);
    bool shouldStateExit();
  private:
    std::shared_ptr<RenderWindow> mpWindow;
    std::string mError;
};

#endif