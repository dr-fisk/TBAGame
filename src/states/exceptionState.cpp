#include <iostream>

#include "states/exceptionState.hpp"
#include "drawable/drawable.hpp"

ExceptionState::ExceptionState(const std::stack<std::shared_ptr<State>>& crStates,
                               const std::shared_ptr<ResourceManager> crpResourceMngr,
                               const std::string& crError) : State(crStates, crpResourceMngr)
{
  mError = crError;
  mpWindow = std::make_shared<RenderWindow>(800, 800, "Exception Encountered");
  std::vector<Drawable*> vertexes;
  // vertexes.push_back(&text1);
  // //mTestBB = mpBatchBuffer;
  // vertexes.clear();
  // vertexes.push_back(&text2);
  //mErrorBatch = BatchBuffer(vertexes, RECTANGLE);
}

bool ExceptionState::shouldStateExit()
{
  return !mpWindow->isOpen();
}

void ExceptionState::fixedUpdate(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime)
{
}

ExceptionState::~ExceptionState()
{
}