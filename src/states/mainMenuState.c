#include <cmath>
#include <algorithm>
#include <queue>
#include <iostream>

#include "states/mainMenuState.h"
#include "drawable/text.h"

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>>& crStates,
                   const std::shared_ptr<RenderEngine>& crpRenderEngine,
                   const std::shared_ptr<BatchBuffer>& crpBatchBuffer) :
                   State(crStates, crpRenderEngine, crpBatchBuffer)
{
  std::string temp = "Envy Code R.ttf";
  mStartTime = std::chrono::system_clock::now();
  mNewFont = std::make_shared<Font>(temp, 5, lg::Black);
  mText = std::make_shared<Text>(mNewFont, "FPS: 0", mpRenderEngine, mpBatchBuffer, 12, 100, 100);
  mSprite = std::make_shared<Sprite>("../src/art.png", mpRenderEngine, mpBatchBuffer, 200.0f, 200.0f, 16, 16);
  mSprite2 = std::make_shared<Sprite>(mpBatchBuffer, 600.0f, 600.0f, 16, 16, lg::Blue);
  // mNewFont->writeGenPoints('g');
  auto uni = mpBatchBuffer->getUniform(0, "u_Textures");
  int sampler[5] = {0,1,2,3,4};
  GLCall(glUniform1iv(uni, 5, sampler));
}

void MainMenu::render(const std::shared_ptr<RenderTarget> &crpTarget)
{
  mpBatchBuffer->update(0,0);
  crpTarget->draw(mpBatchBuffer->getIndicesCount(0));
}

void MainMenu::update(const std::shared_ptr<RenderTarget> &crpTarget)
{
  std::string temp = "FPS: " + std::to_string(gFps);
  mText->updateText(temp);

  std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - mStartTime;

  if(elapsed_time.count() >= 0.02f)
  {
  float xMove = 0.0f;
  float yMove = 0.0f;

  if(crpTarget->isKeyPressed(GLFW_KEY_UP) && !crpTarget->isKeyPressed(GLFW_KEY_DOWN))
  {
    yMove = -50.0f;
  }
  else if(crpTarget->isKeyPressed(GLFW_KEY_DOWN) && !crpTarget->isKeyPressed(GLFW_KEY_UP))
  {
    yMove = 50.0f;
  }

  if(crpTarget->isKeyPressed(GLFW_KEY_RIGHT) && !crpTarget->isKeyPressed(GLFW_KEY_LEFT))
  {
    xMove = 50.0f;
  }
  else if(crpTarget->isKeyPressed(GLFW_KEY_LEFT) && !crpTarget->isKeyPressed(GLFW_KEY_RIGHT))
  {
    xMove = -50.0f;
  }

    mSprite->movePos(xMove * 0.02f, yMove * 0.02f);
    mStartTime = std::chrono::system_clock::now();
  }
}

MainMenu::~MainMenu() 
{
}

bool MainMenu::shouldStateExit()
{
  return false;
}