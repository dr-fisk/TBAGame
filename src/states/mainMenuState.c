#include "mainMenuState.h"

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>> &crStates) : State(crStates) {
  std::vector<Drawable*> vertexes;
  // Make this mesh shit easier so that all you call is just batchbuffer constructor and give it some data
  //mesh = Mesh("../src/fonts/Font.png", 0, 0, 1);
  //mesh2 = Mesh("../src/heart.png", 16,0,1);
  mFont = Font("../src/fonts/Font.png");
  mText = Text("TEST", mFont);
  vertexes.push_back(&mText);
  mTestBB = BatchBuffer(vertexes, RECTANGLE);
}

void MainMenu::render(const std::shared_ptr<RenderTarget> &crpTarget) {
  crpTarget->draw(mTestBB);
}

void MainMenu::update() {
}

MainMenu::~MainMenu() {
}

bool MainMenu::shouldStateExit() {return false;}