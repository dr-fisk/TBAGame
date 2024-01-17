#include <cmath>
#include <algorithm>
#include <queue>
#include <iostream>

#include "states/mainMenuState.h"
#include "drawable/text.h"
#include "window/mouse.h"
#include "shapes/box.h"
#include "resource/image.h"
#include "renderer/renderer2D.h"

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>>& crStates,
                   std::shared_ptr<RenderEngine>& crpRenderEngine) :
                   State(crStates, crpRenderEngine)
{
  std::string temp = "Envy Code R.ttf";
  mStartTime = std::chrono::system_clock::now();
  std::vector<std::shared_ptr<Button<Vector2<int32_t>>>> mButtons;

  mNewFont = std::make_shared<Font>(temp, 5, lg::Black);
  std::cout << "Making text\n";
  mText = std::make_shared<Text>(mNewFont, "FPS: 0", mpRenderEngine, 12, Vector2<float>{100.0f, 100.0f});
  // mSprite = std::make_shared<Sprite>(Vector2<float>{200.0f, 200.0f}, Vector2<float>{16, 16}, lg::White);
  std::cout << "Making sprite1\n";
  mSprite = std::make_shared<Sprite>("../src/art.png", mpRenderEngine, Vector2<float>{200.0f, 200.0f}, Vector2<float>{16, 16});
std::cout << "Making sprite2\n";
  mSprite3 = std::make_shared<Sprite>("../src/heart.png", mpRenderEngine, Vector2<float>{50.0f, 300.0f}, Vector2<float>{16, 16});
std::cout << "Making sprite3\n";
  mSprite2 = std::make_shared<Sprite>("../src/art.png", mpRenderEngine, Vector2<float>{600.0f, 600.0f}, Vector2<float>{16, 16});
std::cout << "Making sprite4\n";
  mButton = std::make_shared<Button<>>(mNewFont, "Test", mpRenderEngine, 12, Vector2<float>{0, 0}, Vector2<float>{50, 50});
  Image tempImg("../src/SquareWBorder.png");
  tempImg.recolorBorderedShape(lg::Color(135, 135, 135), lg::Color(170, 170, 170), lg::White);
  std::shared_ptr<TextureResource> tempTexture = std::make_shared<TextureResource>(tempImg.getName(), mpRenderEngine, tempImg.getDimensions(), tempImg.getInternalFormat());
  tempTexture->update(tempImg.getImgData().data(), tempImg.getDimensions(), tempImg.getOffset(), tempImg.getFormat(), tempImg.getType());
  mButton->setDefaultTexture(tempTexture);
  tempImg.recolorBorderedShape(lg::Color(210, 210, 210), lg::Color(170, 170, 170), lg::Color(170, 170, 170));
  std::shared_ptr<TextureResource> tempTexture2 = std::make_shared<TextureResource>("Hover", mpRenderEngine, tempImg.getDimensions(), tempImg.getInternalFormat());
  tempTexture2->update(tempImg.getImgData().data(), tempImg.getDimensions(), tempImg.getOffset(), tempImg.getFormat(), tempImg.getType());
  mButton->setHoverTexture(tempTexture2);
  tempImg.recolorBorderedShape(lg::Color(230, 230, 230), lg::Color(230, 230, 230), lg::Color(170, 170, 170));
  std::shared_ptr<TextureResource> tempTexture3 = std::make_shared<TextureResource>("Pressed", mpRenderEngine, tempImg.getDimensions(), tempImg.getInternalFormat());
  tempTexture3->update(tempImg.getImgData().data(), tempImg.getDimensions(), tempImg.getOffset(), tempImg.getFormat(), tempImg.getType());
  mButton->setPressedTexture(tempTexture3);

std::cout << "Making button2\n";

  mButtons.push_back(std::make_shared<Button<Vector2<int32_t>>>(mNewFont, "Test1", mpRenderEngine, 12, Vector2<float>{0, 0}, Vector2<float>{50, 50}));
std::cout << "Making button3\n";

  mButtons.push_back(std::make_shared<Button<Vector2<int32_t>>>(mNewFont, "Test2", mpRenderEngine, 12, Vector2<float>{0, 0}, Vector2<float>{50, 50}));
std::cout << "Making button4\n";

  mButtons.push_back(std::make_shared<Button<Vector2<int32_t>>>(mNewFont, "Test3", mpRenderEngine, 12, Vector2<float>{0, 0}, Vector2<float>{50, 50}));
  mButtons[0]->setValue(Vector2<int32_t>(0,0));
  mButtons[1]->setValue(Vector2<int32_t>(10,10));
  mButtons[2]->setValue(Vector2<int32_t>(200,200));

  for(auto& button : mButtons)
  {
    button->setDefaultColor(lg::Grey);
    button->setHoverColor(lg::Green);
    button->setPressedColor(lg::Red);
    button->onClick(MainMenu::dropdownCallbacK);
  }

  mMenu = std::make_shared<DropDownMenu<Vector2<int32_t>>>(2, mButtons, Vector2<float>(700.0f, 700.0f), Vector2<float>{45.0f, 30.0f});

  mButton->setDefaultColor(lg::Grey);
  mButton->setHoverColor(lg::Green);
  mButton->setPressedColor(lg::Red);
  mButton->setSize({40.0f, 30.0f});
  mButton->setPos({250.0f, 250.0f});
  mButton->setValue(nullptr);
  mButton->onClick(MainMenu::buttonCallback);

  mScroll = std::make_shared<Scrollbar>(mpRenderEngine, Vector2<float>(900, 50), Vector2<float>(20, 60));
  mScroll->setDefaultColor(lg::Grey);
  mScroll->setHoverColor(lg::Green);
  mScroll->setPressedColor(lg::Green);
  mScroll->setPressedPadding(Vector2<float>(50, 50));
}

void MainMenu::update(const std::shared_ptr<RenderTarget> &crpTarget, const float cDeltaTime)
{
  std::string temp = "FPS: " + std::to_string(gFps);
  mText->updateText(temp);

  Event tempEvent;
  static float xMove = 0.0f;
  static float yMove = 0.0f;

  while(crpTarget->pollEvent(tempEvent))
  {
    mButton->clicked(tempEvent);
    mMenu->update(tempEvent);
    mScroll->update(tempEvent);

    switch(tempEvent.Type)
    {
      case Event::KeyPress:
      {
        switch(tempEvent.Key.KeyCode)
        {
          case GLFW_KEY_UP:
            yMove += -1.0f;
            break;
          case GLFW_KEY_DOWN:
            yMove += 1.0f;
            break;
          case GLFW_KEY_LEFT:
            xMove += -1.0f;
            break;
          case GLFW_KEY_RIGHT:
            xMove += 1.0f;
            break;
          default:
            break;
        }
        break;
      }
      case Event::KeyRelease:
      {
        switch(tempEvent.Key.KeyCode)
        {
          case GLFW_KEY_UP:
            yMove -= -1.0f;
            break;
          case GLFW_KEY_DOWN:
            yMove -= 1.0f;
            break;
          case GLFW_KEY_LEFT:
            xMove -= -1.0f;
            break;
          case GLFW_KEY_RIGHT:
            xMove -= 1.0f;
            break;
          default:
            break;
        }
      }
      default:
        break;
    }
  }

  float xDir = 300.0f;
  float yDir = 300.0f;
  static Vector2<float> vel(0.0f, 0.0f);

  vel.x = xDir;
  vel.y = yDir;

  Vector2<float> move(0, 0);
  move.x = vel.x * xMove;
  move.y = vel.y * yMove;
  move *= cDeltaTime;

  mSprite->movePos(move);

  Renderer2D::beginScene();
  mText->draw();
  mSprite->draw();
  mSprite2->draw();
  mSprite3->draw();
  mButton->draw();
  mScroll->draw();
  mMenu->draw();
  Renderer2D::endScene();
}

MainMenu::~MainMenu() 
{
}

bool MainMenu::shouldStateExit()
{
  return false;
}

void MainMenu::buttonCallback(const Button<>& rVal)
{
  if(rVal.getValue() == nullptr)
  {
    std::cout << "Bruhhh\n";
  }
  std::cout << "Clicked\n";
}

void MainMenu::dropdownCallbacK(const Button<Vector2<int32_t>>& rVal)
{
  std::cout << rVal.getValue();
}