#include "mainMenuState.h"
#include <cmath>
#include <algorithm>
#include <queue>

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>> &crStates, const std::shared_ptr<BatchBuffer> &crpBatchBuffer) : State(crStates, crpBatchBuffer)
{
  std::vector<Drawable*> vertexes;
  std::vector<RenderData> rendData;
  std::cout << "SETTINGMAIN\n";
  mFont = PngFont("../src/fonts/Font.png");
  mText = Text("TEST", mFont);
  std::string temp = "Envy Code R.ttf";
  mNewFont = Font(temp);

  final = mNewFont['A'];

  for(int i = 0; i < final.size(); i ++ )
  {
    vertexes.push_back(&(*final[i]));
  }
  BatchBuffer::concatRenderData(vertexes, rendData);
  mpBatchBuffer->updateBoundedBufferData(rendData, GL_STREAM_DRAW);
}

void MainMenu::render(const std::shared_ptr<RenderTarget> &crpTarget)
{
  crpTarget->draw(*mpBatchBuffer);
}

void MainMenu::update()
{
}

MainMenu::~MainMenu() 
{
}

bool MainMenu::shouldStateExit()
{
  return false;
}