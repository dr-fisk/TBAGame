#include <cmath>
#include <algorithm>
#include <queue>
#include <iostream>

#include "states/mainMenuState.h"
#include "drawable/text.h"
#include "window/mouse.h"
#include "shapes/box.h"
#include "resource/image.h"

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>>& crStates,
                   std::shared_ptr<RenderEngine>& crpRenderEngine,
                   std::shared_ptr<BatchBuffer>& crpBatchBuffer) :
                   State(crStates, crpRenderEngine, crpBatchBuffer)
{
  std::string temp = "Envy Code R.ttf";
  mStartTime = std::chrono::system_clock::now();
  std::vector<std::shared_ptr<Button<Vector2<int32_t>>>> mButtons;

  mNewFont = std::make_shared<Font>(temp, 5, lg::Black);
  mText = std::make_shared<Text>(mNewFont, "FPS: 0", mpRenderEngine, mpBatchBuffer, 12, Vector2<float>{100.0f, 100.0f});
  // mSprite = std::make_shared<Sprite>(mpBatchBuffer, Vector2<float>{200.0f, 200.0f}, Vector2<float>{16, 16}, lg::White);
  mSprite = std::make_shared<Sprite>("../src/art.png", mpRenderEngine, mpBatchBuffer, Vector2<float>{200.0f, 200.0f}, Vector2<float>{16, 16});
  mSprite3 = std::make_shared<Sprite>("../src/heart.png", mpRenderEngine, mpBatchBuffer, Vector2<float>{50.0f, 300.0f}, Vector2<float>{16, 16});
  mSprite2 = std::make_shared<Sprite>("../src/art.png", mpRenderEngine, mpBatchBuffer, Vector2<float>{600.0f, 600.0f}, Vector2<float>{16, 16});
  mButton = std::make_shared<Button<>>(mNewFont, "Test", mpRenderEngine, mpBatchBuffer, 12, Vector2<float>{0, 0}, Vector2<float>{50, 50});
  // mTexture = std::make_shared<TextureResource>(temp.getName(), prRenderEngine, temp.getDimensions(),
  //                                              temp.getInternalFormat());
    void recolorBorderedShape(const lg::Color& crBorderColor, const lg::Color& crFillColor,
                              const lg::Color& crOriginalFillColor);
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

  mButtons.push_back(std::make_shared<Button<Vector2<int32_t>>>(mNewFont, "Test1", mpRenderEngine, mpBatchBuffer, 12, Vector2<float>{0, 0}, Vector2<float>{50, 50}));
  mButtons.push_back(std::make_shared<Button<Vector2<int32_t>>>(mNewFont, "Test2", mpRenderEngine, mpBatchBuffer, 12, Vector2<float>{0, 0}, Vector2<float>{50, 50}));
  mButtons.push_back(std::make_shared<Button<Vector2<int32_t>>>(mNewFont, "Test3", mpRenderEngine, mpBatchBuffer, 12, Vector2<float>{0, 0}, Vector2<float>{50, 50}));

  for(auto& button : mButtons)
  {
    button->setDefaultColor(lg::Grey);
    button->setHoverColor(lg::Green);
    button->setPressedColor(lg::Red);
  }

  mMenu = std::make_shared<DropDownMenu<Vector2<int32_t>>>(mButtons[2], mButtons, Vector2<float>(700.0f, 700.0f), Vector2<float>{45.0f, 30.0f});

  mButton->setDefaultColor(lg::Grey);
  mButton->setHoverColor(lg::Green);
  mButton->setPressedColor(lg::Red);
  mButton->setSize({40.0f, 30.0f});
  mButton->setPos({250.0f, 250.0f});
  mButton->setValue(nullptr);
  mButton->onClick(MainMenu::buttonCallback);
  // mSprite2 = std::make_shared<Sprite>(mpBatchBuffer, 600.0f, 600.0f, 16, 16, lg::Blue);
  // mNewFont->writeGenPoints('g');
}

void MainMenu::update(const std::shared_ptr<RenderTarget> &crpTarget, const float cDeltaTime)
{
  std::string temp = "FPS: " + std::to_string(gFps);
  mText->updateText(temp);

  // mButton->update();
  // std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - mStartTime;

  Event tempEvent;
  static float xMove = 0.0f;
  static float yMove = 0.0f;

  while(crpTarget->pollEvent(tempEvent))
  {
    // std::cout << "EVENT\n";
    mButton->clicked(tempEvent);
    mMenu->update(tempEvent);
    // switch(tempEvent.Type)
    // {
    //   case Event::MouseButtonPress:
    //     std::cout << "Mouse Button pressed at " << tempEvent.MouseButton.x << ", " << tempEvent.MouseButton.y << std::endl;
    // }

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

  // if(!polled)
  //   mButton->update();
  // if(elapsed_time.count() >= 0.02f)
  // {

  float xDir = 300.0f;
  float yDir = 300.0f;
  static Vector2<float> vel(0.0f, 0.0f);

  vel.x = xDir;
  vel.y = yDir;

  // vel.x = std::min(vel.x, xDir);
  // vel.y = std::min(vel.y, yDir);

  // vel.x /= 2.0f;
  // vel.y /= 2.0f;

  // if (mButton->buttonPressed())// && RenderWindow::getKeyPress() == GLFW_KEY_DOWN)
  // {
  //   std::cout << "Woah take it easy man\n";
  // }

  // if(crpTarget->isKeyPressed(GLFW_KEY_UP) && !crpTarget->isKeyPressed(GLFW_KEY_DOWN))
  // {
  //   yMove = -200.0f;
  // }
  // else if(crpTarget->isKeyPressed(GLFW_KEY_DOWN) && !crpTarget->isKeyPressed(GLFW_KEY_UP))
  // {
  //   yMove = 200.0f;
  // }

  // if(crpTarget->isKeyPressed(GLFW_KEY_RIGHT) && !crpTarget->isKeyPressed(GLFW_KEY_LEFT))
  // {
  //   xMove = 200.0f;
  // }
  // else if(crpTarget->isKeyPressed(GLFW_KEY_LEFT) && !crpTarget->isKeyPressed(GLFW_KEY_RIGHT))
  // {
  //   xMove = -200.0f;
  // }

  // vel.x = (vel.x + xMove *);
  // vel.y = (vel.y + yMove *);
  Vector2<float> move(0, 0);
  move.x = vel.x * xMove;
  move.y = vel.y * yMove;
  move *= cDeltaTime;

    mSprite->movePos(move);
  // std::cout << "Mouse Pos: " << lg::Mouse::getMousePosi();
    // mStartTime = std::chrono::system_clock::now();
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