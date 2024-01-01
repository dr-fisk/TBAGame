#include <cmath>
#include <algorithm>
#include <queue>
#include <iostream>

#include "states/mainMenuState.h"
#include "drawable/text.h"
#include "window/mouse.h"

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>>& crStates,
                   std::shared_ptr<RenderEngine>& crpRenderEngine,
                   std::shared_ptr<BatchBuffer>& crpBatchBuffer) :
                   State(crStates, crpRenderEngine, crpBatchBuffer)
{
  std::string temp = "Envy Code R.ttf";
  mStartTime = std::chrono::system_clock::now();
  mNewFont = std::make_shared<Font>(temp, 5, lg::Black);
  mText = std::make_shared<Text>(mNewFont, "FPS: 0", mpRenderEngine, mpBatchBuffer, 12, 100, 100);
  mSprite = std::make_shared<Sprite>("../src/art.png", mpRenderEngine, mpBatchBuffer, 200.0f, 200.0f, 16, 16);
  mSprite3 = std::make_shared<Sprite>("../src/heart.png", mpRenderEngine, mpBatchBuffer, 300.0f, 50.0f, 16, 16);
  mSprite2 = std::make_shared<Sprite>("../src/art.png", mpRenderEngine, mpBatchBuffer, 600.0f, 600.0f, 16, 16);
  mButton = std::make_shared<Button>(mNewFont, "Test", mpRenderEngine, mpBatchBuffer, 12, 0, 0, 50, 50);
  mButton->setDefaultColor(lg::Grey);
  mButton->setHoverColor(lg::Green);
  mButton->setPressedColor(lg::Red);
  mButton->setPos(250.0f, 250.0f);
  // mSprite2 = std::make_shared<Sprite>(mpBatchBuffer, 600.0f, 600.0f, 16, 16, lg::Blue);
  // mNewFont->writeGenPoints('g');
}

void MainMenu::update(const std::shared_ptr<RenderTarget> &crpTarget)
{
  std::string temp = "FPS: " + std::to_string(gFps);
  mText->updateText(temp);

  mButton->update();
  std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - mStartTime;

  // if(elapsed_time.count() >= 0.02f)
  // {
  float xMove = 0.0f;
  float yMove = 0.0f;
  static Vector2<float> vel(0.0f, 0.0f);

  if (RenderWindow::getKeyPress() == GLFW_KEY_UP)// && RenderWindow::getKeyPress() == GLFW_KEY_DOWN)
  {
    std::cout << "Woah take it easy man\n";
  }

  if(crpTarget->isKeyPressed(GLFW_KEY_UP) && !crpTarget->isKeyPressed(GLFW_KEY_DOWN))
  {
    yMove = -200.0f;
  }
  else if(crpTarget->isKeyPressed(GLFW_KEY_DOWN) && !crpTarget->isKeyPressed(GLFW_KEY_UP))
  {
    yMove = 200.0f;
  }

  if(crpTarget->isKeyPressed(GLFW_KEY_RIGHT) && !crpTarget->isKeyPressed(GLFW_KEY_LEFT))
  {
    xMove = 200.0f;
  }
  else if(crpTarget->isKeyPressed(GLFW_KEY_LEFT) && !crpTarget->isKeyPressed(GLFW_KEY_RIGHT))
  {
    xMove = -200.0f;
  }

  vel.x = (vel.x + xMove * elapsed_time.count()) / 2.0f;
  vel.y = (vel.y + yMove * elapsed_time.count()) / 2.0f;

    mSprite->movePos(vel.x, vel.y);
  // std::cout << "Mouse Pos: " << lg::Mouse::getMousePosi();
    mStartTime = std::chrono::system_clock::now();
}

MainMenu::~MainMenu() 
{
}

bool MainMenu::shouldStateExit()
{
  return false;
}