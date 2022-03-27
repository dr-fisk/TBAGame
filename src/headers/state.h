#ifndef STATE_H
#define STATE_H

#include "common.h"
#include "renderWindow.h"

class State {
  public:
    State(RenderWindow *wind, std::stack<State *> s);
    ~State();
  private:
    RenderWindow *window;
    std::stack<State *> states;
};

#endif