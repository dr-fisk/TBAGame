#include <cmath>
#include <algorithm>
#include <queue>
#include <iostream>
#include "states/mainMenuState.h"
#include "drawable/text.h"

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>>& crStates,
                   const std::shared_ptr<RenderEngine> cpRenderEngine,
                   const std::shared_ptr<BatchBuffer> cpBatchBuffer) : State(crStates, cpRenderEngine, cpBatchBuffer)
{
  std::string temp = "Envy Code R.ttf";
  mStartTime = std::chrono::system_clock::now();
  // mMesh = Mesh("../src/art.png");
  // mTexture = Texture("../src/art.png");
  mNewFont = std::make_shared<Font>(temp, 5, lg::Black);
  // mNewFont->loadGlyphs(12);
  mText = std::make_shared<Text>(mNewFont, "S", mpRenderEngine, mpBatchBuffer, 12, 100, 100);
  // mNewFont->writeGenPoints('g');
  // Vector2<uint32_t> dim = mNewFont->getCharacterDimensions(12,'S');
  // mpBatchBuffer->initTexture(0, mNewFont->getData(12, 'S').data(), dim.y, dim.x, 8);
  // dim = mNewFont->getCharacterDimensions('i');


    // temprect = std::make_shared<Rect>(100,100, dim.y, dim.x, lg::Black);

  // dim = mNewFont->getCharacterDimensions((char)45);
  // mpBatchBuffer->initTexture(1, mNewFont['i'].data(), dim.y, dim.x, 8);
  // dim = mNewFont->getCharacterDimensions('m');
    // std::cout << dim;

  // mpBatchBuffer->initTexture(2, mNewFont['m'].data(), dim.y, dim.x, 8);
  // dim = mNewFont->getCharacterDimensions('a');
  //   std::cout << dim;

  // mpBatchBuffer->initTexture(3, mNewFont['a'].data(), dim.y, dim.x, 8);
  // dim = mNewFont->getCharacterDimensions((char)48);
  // mpBatchBuffer->initTexture(4, mNewFont[(char)48].data(), dim.y, dim.x, 8);
  // std::shared_ptr<Rect> newrect = std::make_shared<Rect>(500,500, dim.y, dim.x, lg::Black);
    // mpBatchBuffer->initTexture(0, "../src/art.png");
  // mpBatchBuffer->bindTexture(0, 0);
  mText->getResource().bind(1);
  // mpBatchBuffer->bindTexture(1, 1);
  // mpBatchBuffer->bindTexture(2, 2);
  // mpBatchBuffer->bindTexture(3, 3);
  // mpBatchBuffer->bindTexture(4, 4);

  // mpBatchBuffer->registerDrawable(text.get());
  // mpBatchBuffer->registerDrawable(temprect);
  // mpBatchBuffer->registerDrawable(newrect);
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