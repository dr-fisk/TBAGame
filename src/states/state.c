#include "states/state.h"

//! @brief Constructs new state which contains stack of states and window context
//!
//! @param[in] crStates        Stack of States
//! @param[in] crpWindow       Window Context for the current state
//! @param[in] crpRenderEngine Resource Manager
//!
//! @return State Object
State::State(const std::stack<std::shared_ptr<State>>& crStates, const std::shared_ptr<RenderTarget>& crpWindow,
             const std::shared_ptr<RenderEngine>& crpRenderEngine)
{
  mStates = crStates;
  mpRenderEngine = crpRenderEngine;
  mpWindow = crpWindow;
}

//! @brief Renders VBO Data
//!
//! @param crpTarget Target to render to
//!
//! @return None 
void State::render(const std::shared_ptr<RenderTarget>& crpTarget)
{
}

//! @brief Default Destructor
//!
//! @return None
State::~State()
{
}