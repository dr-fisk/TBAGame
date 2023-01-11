#include "state.h"

/* Function:    State
   Description: Constructs new state which contains stack of states and window context
   Parameters:  None
   Returns:     None
 */
State::State(const std::stack<std::shared_ptr<State>> &crStates) {
  mStates = crStates;
}

/* Function:    ~State
   Description: Destructor
   Parameters:  None
   Returns:     None
 */
State::~State() {
}