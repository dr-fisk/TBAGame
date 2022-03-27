#include "state.h"

/* Function:    State
   Description: Constructs new state which contains stack of states and window context
   Parameters:  None
   Returns:     None 
 */
State::State(RenderWindow *wind, std::stack<State *> s) {
  this->window = wind;
  this->states = s;
}

/* Function:    ~State
   Description: Destructor
   Parameters:  None
   Returns:     None 
 */
State::~State() {
}