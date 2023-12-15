#include <cmath>
#include <algorithm>
#include <queue>
#include <iostream>
#include "mainMenuState.h"

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>> &crStates, const std::shared_ptr<BatchBuffer> &crpBatchBuffer) : State(crStates, crpBatchBuffer)
{
  std::string temp = "Envy Code R.ttf";
  mStartTime = std::chrono::system_clock::now();
  // mMesh = Mesh("../src/art.png");
  // mTexture = Texture("../src/art.png");
  mNewFont = Font(temp, 5, lg::Black);
  mNewFont.writeGenPoints((char)44);
  Vector2<int32_t> dim = mNewFont.getCharacterDimensions((char)44);
  Rect temprect = Rect(100,100, dim.mY, dim.mX, lg::Black);

  mpBatchBuffer->initTexture(0, mNewFont[(char)44].data(), dim.mY, dim.mX, 8);
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

void MainMenu::update(const std::shared_ptr<RenderTarget> &crpTarget)
{
  static int cha = 33;
  const int32_t ASCII_CHAR_START = 33;
  const int32_t ASCII_CHAR_END = 126;
  std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - mStartTime;
  if(!crpTarget->isKeyPressed(GLFW_KEY_SPACE) && elapsed_time.count() >= 0.3)
  {
    if (cha == 126)
    {
      cha = 33;
    }
    else
    {
      cha ++;
    }

    // std::cout << "Right key press wooh\n";
    Vector2<int32_t> dim = mNewFont.getCharacterDimensions((char)cha);
    mStartTime = std::chrono::system_clock::now();
    auto uni = mpBatchBuffer->getUniform(0, "u_Textures");
    mpBatchBuffer->initTexture(0, mNewFont[(char)cha].data(), dim.mY, dim.mX, 8);
    // mpBatchBuffer->initTexture(0, "../src/art.png");
    mpBatchBuffer->bindTexture(0);
    int sampler[1] = {0};
    GLCall(glUniform1iv(uni, 1, sampler));
  }
}

MainMenu::~MainMenu() 
{
}

bool MainMenu::shouldStateExit()
{
  return false;
}