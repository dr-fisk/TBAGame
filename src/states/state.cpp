#include "states/state.hpp"

#include <iostream>

//! @brief Constructs new state which contains stack of states and window context
//!
//! @param[in] crStates        Stack of States
//! @param[in] crpResourceMngr Resource Manager
//!
//! @return State Object
State::State(const std::stack<std::shared_ptr<State>>& crStates, const std::shared_ptr<ResourceManager>& crpResourceMngr)
{
  mStates = crStates;
  mpResourceMngr = crpResourceMngr;
}

//! @brief Renders VBO Data
//!
//! @param crpTarget Target to render to
//!
//! @return None 
void State::render(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime)
{
  std::cout << "Parent render\n";
}

void State::update(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime)
{

}

void State::lateUpdate(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime)
{

}

//! @brief Default Destructor
//!
//! @return None
State::~State()
{
}