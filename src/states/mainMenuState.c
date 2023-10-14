#include "mainMenuState.h"
#include <cmath>
#include <algorithm>
#include <queue>

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>> &crStates, const std::shared_ptr<BatchBuffer> &crpBatchBuffer) : State(crStates, crpBatchBuffer)
{
  std::vector<Drawable*> vertexes;
  std::vector<RenderData> rendData;
  std::cout << "SETTINGMAIN\n";
  // mFont = PngFont("../src/fonts/Font.png");
  // std::cout << "Png Font done, starting PngText.\n";
  // mText = PngText("TEST", mFont);
  // std::cout << "PngText done starting Mesh\n";

  // std::string temp = "Envy Code R.ttf";
  // mMesh = Mesh("../src/art.png");
  mTexture = Texture("../src/art.png");
  std::cout << "Mesh done\n";
  // mNewFont = Font(temp);
  Rect temprect = Rect(100,100, 16, 16, lg::Black);
  // final = mNewFont['a'];

  // vertexes.push_back(&temprect);
  // vertexes.push_back(&mMesh);
  // for(int i = 0; i < final.size(); i ++ )
  // {
  //   // vertexes.push_back(&(*final[i]));
  // }
  // BatchBuffer::concatRenderData(vertexes, rendData);
  std::cout << "Resgister Drawable" << std::endl;
  mpBatchBuffer->registerDrawable(0, 0, &temprect);
  std::cout << "Register done" << std::endl;
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