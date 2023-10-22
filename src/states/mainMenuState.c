#include <cmath>
#include <algorithm>
#include <queue>
#include <iostream>
#include "mainMenuState.h"

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>> &crStates, const std::shared_ptr<BatchBuffer> &crpBatchBuffer) : State(crStates, crpBatchBuffer)
{
  std::string temp = "Envy Code R.ttf";
  // mMesh = Mesh("../src/art.png");
  // mTexture = Texture("../src/art.png");
  mNewFont = Font(temp, 2, lg::Black);
  // mNewFont.writeGenPoints('A');
  Vector2<int32_t> dim = mNewFont.getCharacterDimensions('?');
  Rect temprect = Rect(100,100, dim.mY, dim.mX, lg::Black);

  mpBatchBuffer->initTexture(0, mNewFont['?'].data(), dim.mY, dim.mX, 8);
    // mpBatchBuffer->initTexture(0, "../src/art.png");
  mpBatchBuffer->bindTexture(0);

  mpBatchBuffer->registerDrawable(0, 0, &temprect);
  auto uni = mpBatchBuffer->getUniform(0, "u_Textures");
  int sampler[1] = {0};
  GLCall(glUniform1iv(uni, 1, sampler));
}

void MainMenu::render(const std::shared_ptr<RenderTarget> &crpTarget)
{
  crpTarget->draw(mpBatchBuffer->getIndicesCount(0));
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