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
  // mMesh = Mesh("../src/art.png");
  // mTexture = Texture("../src/art.png");
  mNewFont = std::make_shared<Font>(temp, 5, lg::Black);
  // char temp1[1];
  // temp1[0] = (char)33;

  // std::string temp2 = temp1;
  mText = std::make_shared<Text>(mNewFont, "0", mpRenderEngine, mpBatchBuffer, 12, 100, 100);
  // mNewFont->writeGenPoints('g');
    // temprect = std::make_shared<Rect>(100,100, dim.y, dim.x, lg::Black);
  // mpBatchBuffer->initTexture(3, mNewFont['a'].data(), dim.y, dim.x, 8);
  // dim = mNewFont->getCharacterDimensions((char)48);
  // mpBatchBuffer->initTexture(4, mNewFont[(char)48].data(), dim.y, dim.x, 8);
  // std::shared_ptr<Rect> newrect = std::make_shared<Rect>(500,500, dim.y, dim.x, lg::Black);
    // mpBatchBuffer->initTexture(0, "../src/art.png");

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
  // static int cha = 33;
  // const int32_t ASCII_CHAR_START = 33;
  // const int32_t ASCII_CHAR_END = 126;
  mText->updateText(std::to_string(gFps));

  // std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - mStartTime;
  // if(crpTarget->isKeyPressed(GLFW_KEY_SPACE) && elapsed_time.count() >= 0.3)
  // {
  //   if (cha == 126)
  //   {
  //     cha = 33;
  //   }
  //   else
  //   {
  //     cha ++;
  //   }

  //   char temp1[2];
  //   temp1[1] = '\0';
  //   temp1[0] = (char) cha;
  //   std::string temp = temp1;
  //   std::cout << temp << std::endl;
  //   mText->updateText(temp);
  //   mStartTime = std::chrono::system_clock::now();
  // }

  // static int move = 0;

  // if (move != 800)
  // {
  //   temprect->movePos(1,0);
  //   move ++;
  // }
  // std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - mStartTime;

  // if(elapsed_time.count() >= 0.02)
  // {
  // int xMove = 0;
  // int yMove = 0;

  // if(crpTarget->isKeyPressed(GLFW_KEY_UP) && !crpTarget->isKeyPressed(GLFW_KEY_DOWN))
  // {
  //   yMove = -1;
  // }
  // else if(crpTarget->isKeyPressed(GLFW_KEY_DOWN) && !crpTarget->isKeyPressed(GLFW_KEY_UP))
  // {
  //   yMove = 1;
  // }

  // if(crpTarget->isKeyPressed(GLFW_KEY_RIGHT) && !crpTarget->isKeyPressed(GLFW_KEY_LEFT))
  // {
  //   xMove = 1;
  // }
  // else if(crpTarget->isKeyPressed(GLFW_KEY_LEFT) && !crpTarget->isKeyPressed(GLFW_KEY_RIGHT))
  // {
  //   xMove = -1;
  // }

  // temprect->movePos(xMove,yMove);
  // }
  // static int cha = 33;
  // const int32_t ASCII_CHAR_START = 33;
  // const int32_t ASCII_CHAR_END = 126;
  // // std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - mStartTime;
  // if(crpTarget->isKeyPressed(GLFW_KEY_SPACE) && elapsed_time.count() >= 0.3)
  // {
  //   if (cha == 126)
  //   {
  //     cha = 33;
  //   }
  //   else
  //   {
  //     cha ++;
  //   }

  //   // std::cout << "Right key press wooh\n";
  //   Vector2<int32_t> dim = mNewFont->getCharacterDimensions((char)cha);
  //   mStartTime = std::chrono::system_clock::now();
  //   auto uni = mpBatchBuffer->getUniform(0, "u_Textures");
  //   mpBatchBuffer->initTexture(0, mNewFont[(char)cha].data(), dim.y, dim.x, 8);
  //   // mpBatchBuffer->initTexture(0, "../src/art.png");
  //   mpBatchBuffer->bindTexture(0,0);
  //   int sampler[1] = {0};
  //   GLCall(glUniform1iv(uni, 1, sampler));
  // }
}

MainMenu::~MainMenu() 
{
}

bool MainMenu::shouldStateExit()
{
  return false;
}