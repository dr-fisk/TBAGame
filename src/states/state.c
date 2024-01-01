#include "states/state.h"

//! @brief Constructs new state which contains stack of states and window context
//!
//! @param[in] crStates       Stack of States
//! @param[in] prRenderEngine Resource Manager
//! @param[in] prBatchBuffer  Batch Buffer renderer
//!
//! @return State Object
State::State(const std::stack<std::shared_ptr<State>>& crStates, std::shared_ptr<RenderEngine>& prRenderEngine,
             std::shared_ptr<BatchBuffer>& prBatchBuffer)
{
  mStates = crStates;
  mpRenderEngine = prRenderEngine;
  mpBatchBuffer = prBatchBuffer;
}

//! @brief Renders VBO Data
//!
//! @param crpTarget Target to render to
//!
//! @return None 
void State::render(const std::shared_ptr<RenderTarget>& crpTarget)
{
  mpBatchBuffer->render(0, 0, crpTarget);
}

//! @brief Default Destructor
//!
//! @return None
State::~State()
{
}