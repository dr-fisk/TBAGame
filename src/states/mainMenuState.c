#include <cmath>
#include <algorithm>
#include <queue>
#include <iostream>
#include "mainMenuState.h"

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>> &crStates, const std::shared_ptr<BatchBuffer> &crpBatchBuffer) : State(crStates, crpBatchBuffer)
{
  std::cout << "SETTINGMAIN\n";
  // mFont = PngFont("../src/fonts/Font.png");
  // std::cout << "Png Font done, starting PngText.\n";
  // mText = PngText("TEST", mFont);
  // std::cout << "PngText done starting Mesh\n";

  std::string temp = "Envy Code R.ttf";
  // mMesh = Mesh("../src/art.png");
  // mTexture = Texture("../src/art.png");
  std::cout << "Mesh done\n";
  mNewFont = Font(temp, 1, lg::Black);
  Vector2<int32_t> dim = mNewFont.getCharacterDimensions('A');
  Rect temprect = Rect(100,100, dim.mY, dim.mX, lg::Black);

  mpBatchBuffer->initTexture(0, mNewFont['A'].data(), dim.mY, dim.mX, 8);
  mpBatchBuffer->bindTexture(0);

  std::cout << "Resgister Drawable" << std::endl;
  mpBatchBuffer->registerDrawable(0, 0, &temprect);
  std::cout << "Register done" << std::endl;
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