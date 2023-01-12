#include "state.h"

/* Function:    State
   Description: Constructs new state which contains stack of states and window context
   Parameters:  None
   Returns:     None
 */
State::State(const std::stack<std::shared_ptr<State>> &crStates, const std::shared_ptr<BatchBuffer> &crpBatchBuffer) {
  mStates = crStates;
  mpBatchBuffer = crpBatchBuffer;
}

/* Function:    ~State
   Description: Destructor
   Parameters:  None
   Returns:     None
 */
State::~State() {
}