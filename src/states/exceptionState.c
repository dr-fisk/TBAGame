#include "exceptionState.h"

ExceptionState::ExceptionState(const std::stack<std::shared_ptr<State>> &crStates, const std::shared_ptr<BatchBuffer> &crpBatchBuffer, 
                               const std::string &crError) : State(crStates, crpBatchBuffer)
{
  mError = crError;
  mpWindow = std::make_shared<RenderWindow>(800, 800, "Exception Encountered");
  std::vector<Drawable*> vertexes;
  mFont = PngFont("../src/fonts/Font.png");
  Text text1 = Text("TEST", mFont);
  Text text2 = Text(crError, mFont);
  vertexes.push_back(&text1);
  //mTestBB = mpBatchBuffer;
  vertexes.clear();
  vertexes.push_back(&text2);
  //mErrorBatch = BatchBuffer(vertexes, RECTANGLE);
}

void ExceptionState::render(const std::shared_ptr<RenderTarget> &crpTarget)
{
  crpTarget->setActive();
  crpTarget->draw(mTestBB);
  mpWindow->setActive();
  std::cout << "After second active\n";
  mpWindow->draw(mTestBB);
  std::cout << "Draw error\n";
}

bool ExceptionState::shouldStateExit()
{
  return !mpWindow->isOpen();
}

void ExceptionState::update()
{
}

ExceptionState::~ExceptionState()
{
}