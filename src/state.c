#include "state.h"

State::State(RenderWindow *wind, std::stack<State *> s) {
  this->window = wind;
  this->states = s;
}

State::~State() {

}