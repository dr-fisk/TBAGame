#ifndef EXCEPTION_STATE_HPP
#define EXCEPTION_STATE_HPP

#include <memory>
#include <string>
#include <stack>

#include "exception.hpp"
#include "window/renderWindow.hpp"
#include "state.hpp"

class ExceptionState : public State {
  public:
    ExceptionState(const std::stack<std::shared_ptr<State>>& crStates,
                   const std::string& crError);
    ~ExceptionState();
    void fixedUpdate(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime);
    bool shouldStateExit();
  private:
    std::shared_ptr<RenderWindow> mpWindow;
    std::string mError;
};

#endif