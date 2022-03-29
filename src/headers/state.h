#ifndef STATE_H
#define STATE_H

#include "common.h"
#include "renderWindow.h"

class State {
  public:
    State(std::shared_ptr<RenderWindow> wind, std::stack<std::shared_ptr<State>> s);
    ~State();
  private:
    std::shared_ptr<RenderWindow> window;
    std::stack<std::shared_ptr<State>> states;
};

#endif