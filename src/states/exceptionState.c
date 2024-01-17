#include <iostream>

#include "states/exceptionState.h"
#include "drawable/drawable.h"

ExceptionState::ExceptionState(const std::stack<std::shared_ptr<State>>& crStates,
                               std::shared_ptr<RenderEngine> cpRenderEngine,
                               const std::string& crError) : State(crStates, cpRenderEngine)
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

void ExceptionState::update(const std::shared_ptr<RenderTarget>& crpTarget, const float cDeltaTime)
{
}

ExceptionState::~ExceptionState()
{
}