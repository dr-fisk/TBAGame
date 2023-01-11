#include "exceptionState.h"

ExceptionState::ExceptionState(const std::stack<std::shared_ptr<State>> &crStates, const std::string &crError) : State(crStates) {
  mError = crError;
  mpWindow = std::make_shared<RenderWindow>(800, 800, "Exception Encountered");
  std::vector<Drawable*> vertexes;
  mFont = Font("../src/fonts/Font.png");
  Text text1 = Text("TEST", mFont);
  Text text2 = Text(crError, mFont);
  vertexes.push_back(&text1);
  mTestBB = BatchBuffer(vertexes, RECTANGLE);
  vertexes.clear();
  vertexes.push_back(&text2);
  mErrorBatch = BatchBuffer(vertexes, RECTANGLE);
}

void ExceptionState::render(const std::shared_ptr<RenderTarget> &crpTarget) {
  crpTarget->draw(mTestBB);
  mpWindow->draw(mErrorBatch);
}

bool ExceptionState::shouldStateExit() {
  return !mpWindow->isOpen();
}

void ExceptionState::update() {
}

ExceptionState::~ExceptionState() {
}