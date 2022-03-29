#include "state.h"

/* Function:    State
   Description: Constructs new state which contains stack of states and window context
   Parameters:  None
   Returns:     None 
 */
State::State(std::shared_ptr<RenderWindow> wind, std::stack<std::shared_ptr<State>> s) {
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