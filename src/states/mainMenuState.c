#include "mainMenuState.h"

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>> &crStates, const std::shared_ptr<BatchBuffer> &crpBatchBuffer) : State(crStates, crpBatchBuffer) {
  std::vector<Drawable*> vertexes;
  std::vector<RenderData> rendData;
  std::cout << "SETTINGMAIN\n";
  mFont = Font("../src/fonts/Font.png");
  mText = Text("TEST", mFont);
  vertexes.push_back(&mText);
  BatchBuffer::concatRenderData(vertexes, rendData);
  mpBatchBuffer = std::make_shared<BatchBuffer>( rendData, RECTANGLE, 1, 1, 1);
}

void MainMenu::render(const std::shared_ptr<RenderTarget> &crpTarget) {
  crpTarget->draw(*mpBatchBuffer);
}

void MainMenu::update() {
}

MainMenu::~MainMenu() {
}

bool MainMenu::shouldStateExit() {return false;}