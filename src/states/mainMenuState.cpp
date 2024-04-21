#include <cmath>
#include <algorithm>
#include <queue>
#include <iostream>

#include "states/mainMenuState.hpp"
#include "drawable/text.hpp"
#include "window/mouse.hpp"
#include "shapes/box.hpp"
#include "resource/image.hpp"
#include "renderer/renderer2D.hpp"
#include "renderer/renderCommand.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "math/lestMath.hpp"
MainMenu::MainMenu(const std::stack<std::shared_ptr<State>>& crStates,
                   const std::shared_ptr<RenderEngine>& crpRenderEngine) :
                   State(crStates, crpRenderEngine)
{
  std::string temp = "Envy Code R.ttf";
  mStartTime = std::chrono::system_clock::now();
  std::vector<std::shared_ptr<Button<glm::ivec2>>> mButtons;

  mNewFont = std::make_shared<Font>(temp, 5, lg::Black);
  mText = std::make_shared<Text>(mNewFont, "FPS: 0", mpRenderEngine, 12, glm::vec2{100.0f, 100.0f});
  // mSprite = std::make_shared<Sprite>(glm::vec2{200.0f, 200.0f}, glm::vec2{16, 16}, lg::White);
  mSprite = std::make_shared<Sprite>("../src/art.png", mpRenderEngine, glm::vec2{200.0f, 200.0f}, glm::vec2{16, 16});
  mSprite3 = std::make_shared<Sprite>("../src/heart.png", mpRenderEngine, glm::vec2{50.0f, 300.0f}, glm::vec2{16, 16});
  mSprite2 = std::make_shared<Sprite>("../src/art.png", mpRenderEngine, glm::vec2{600.0f, 600.0f}, glm::vec2{16, 16});
  mButton = std::make_shared<Button<>>(mNewFont, "Test", mpRenderEngine, 12, glm::vec2{0, 0}, glm::vec2{50, 50});
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
  mButtons.push_back(std::make_shared<Button<glm::ivec2>>(mNewFont, "Test1", mpRenderEngine, 12, glm::vec2{0, 0}, glm::vec2{50, 50}));
  mButtons.push_back(std::make_shared<Button<glm::ivec2>>(mNewFont, "Test2", mpRenderEngine, 12, glm::vec2{0, 0}, glm::vec2{50, 50}));
  mButtons.push_back(std::make_shared<Button<glm::ivec2>>(mNewFont, "Test3", mpRenderEngine, 12, glm::vec2{0, 0}, glm::vec2{50, 50}));
  mButtons[0]->setValue(glm::ivec2(0,0));
  mButtons[1]->setValue(glm::ivec2(10,10));
  mButtons[2]->setValue(glm::ivec2(200,200));

  for(auto& button : mButtons)
  {
    button->setDefaultColor(lg::Grey);
    button->setHoverColor(lg::Green);
    button->setPressedColor(lg::Red);
    button->onClick(MainMenu::dropdownCallbacK);
  }

  mMenu = std::make_shared<DropDownMenu<glm::ivec2>>(2, mButtons, glm::vec2(700.0f, 700.0f), glm::vec2{45.0f, 30.0f});

  mButton->setDefaultColor(lg::Grey);
  mButton->setHoverColor(lg::Green);
  mButton->setPressedColor(lg::Red);
  mButton->setSize({40.0f, 30.0f});
  mButton->setPos({250.0f, 250.0f});
  mButton->setValue(nullptr);
  mButton->onClick(MainMenu::buttonCallback);

  mScroll = std::make_shared<Scrollbar>(mpRenderEngine, glm::vec2(900, 50), glm::vec2(20, 60));
  mScroll->setDefaultColor(lg::Grey);
  mScroll->setHoverColor(lg::Green);
  mScroll->setPressedColor(lg::Green);
  mScroll->setPressedPadding(glm::vec2(50, 50));

  // mFbo = std::make_shared<FrameBuffer>();
  // mFbo->bind();
  // RenderCommand::enableBlend();
  // RenderCommand::setClearColor(0.3f, 0.0f, 0.0f, 1.0f);
  // mFbo->unbind();
  // mFbo->invalidate(glm::uvec2{gWindowWidth, gWindowHeight}, mpRenderEngine);
  // mView = std::make_shared<Sprite>(glm::vec2{gWindowWidth / 2.0f, gWindowHeight / 2.0f}, glm::vec2{gWindowWidth, gWindowHeight}, lg::White);

  // mView->setTexture(mFbo->getTexture(), true);
  mCam = std::make_shared<OrthCamera>(0, 1920, 1080, 0);
  Box<glm::vec2> testBox = mSprite->getGlobalBounds(*mCam);

  std::cout << "Pos: " << glm::to_string(testBox.getTopLeft()) << " Size: " << glm::to_string(testBox.getSize()) << std::endl;
  std::cout << sizeof(glm::vec2) << std::endl;
  // mCam.setPosition({0.0f, 0.0f, 0.0f});
  curr_pos = mSprite->getPos();
  xMove = 0.0f;
  yMove = 0.0f;
}

void MainMenu::fixedUpdate(const std::shared_ptr<RenderTarget> &crpTarget, const double cDeltaTime)
{
  // std::string temp = "FPS: " + std::to_string(gFps);
  // mText->updateText(temp);

  Event tempEvent;
  sprite_pos = mSprite->getPos();
  // std::cout << glm::to_string(sprite_pos) << std::endl;
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
            // std::cout << "Right\n";
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
            // std::cout << "No more right\n";
            break;
          default:
            break;
        }
        break;
      }
      case Event::WindowResize:
      {
        // Viewport needs to be updated on window resize if you want viewport to be same as windowsize
        mCam->setProjection(tempEvent.WindowView.x, tempEvent.WindowView.Width, tempEvent.WindowView.Height, tempEvent.WindowView.y);
        glViewport(tempEvent.WindowView.x, tempEvent.WindowView.y, tempEvent.WindowView.Width, tempEvent.WindowView.Height);
        // int view[4];
        // glGetIntegerv(GL_VIEWPORT, view);
        // std::cout << "View: (" << tempEvent.WindowView.x << ", " << tempEvent.WindowView.y << ") " << "(" << tempEvent.WindowView.Width << ", " << tempEvent.WindowView.Height << ")\n";
        // std::cout << "View: (" << view[0] << ", " << view[1] << ") " << "(" << view[2] << ", " << view[3] << ")\n";
        break;
      }
      default:
        break;
    }
  }

  float xDir = 300.0f;
  float yDir = 300.0f;
  static glm::vec2 vel(0.0f, 0.0f);
  // static double time = 0;
  // static int dir = 1;
  // time += cDeltaTime;

  vel.x = xDir;
  vel.y = yDir;

  glm::vec2 move(0.0f, 0.0f);
  move.x = vel.x * xMove;

  // if(time >= 7.0d)
  // {
  //   dir *= -1;
  //   time = 0;
  // }

  move.y = vel.y * yMove;
  move *= cDeltaTime;

  curr_pos += move;
  mSprite->setPos(curr_pos);
  // std::cout << "Move: " << glm::to_string(move) << " DT " << cDeltaTime << std::endl;
  // mFbo->bind();
  // mFbo->unbind();
  // Renderer2D::beginScene();
  // mView->draw();
  // Renderer2D::endScene();
  // std::cout << glm::to_string(lg::Mouse::getMousePosf()) << std::endl;
  glm::vec2 temp =lg::Math::lerp(sprite_pos, curr_pos, (float)cDeltaTime / (0.02f));
  mSprite->setPos(temp);
}

void MainMenu::render(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime)
{
  // std::cout << glm::to_string(lg::Math::lerp(sprite_pos, mSprite->getPos(), (float)cDeltaTime)) << std::endl;
  // std::cout << cDeltaTime << std::endl;

  // sprite_pos = mSprite->getPos();
  RenderCommand::clear();
  Renderer2D::beginScene(mCam);
  // mText->draw();
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

void MainMenu::dropdownCallbacK(const Button<glm::ivec2>& rVal)
{
  std::cout << "(" << rVal.getValue().x << ", " << rVal.getValue().y << ")" << std::endl;
}