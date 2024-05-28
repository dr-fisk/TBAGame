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
                   const std::shared_ptr<ResourceManager>& crpResourceMngr) :
                   State(crStates, crpResourceMngr)
{
  std::string temp = "Envy Code R.ttf";
  mStartTime = std::chrono::system_clock::now();
  mNewFont.loadFromFile(temp, 5);
  // std::cout << "Font loaded\n";
  mText = std::make_shared<Text>(mNewFont, "FPS: 0", 12);
  mText->setPos({200.0f, 50.0f});
  mText->setColor(lg::Blue);
  // std::cout << "Text Done\n";
  Image temp_img("../src/art.png");
  spriteTexture.create(temp_img.getDimensions().y, temp_img.getDimensions().x, temp_img.getInternalFormat());
  spriteTexture.update(temp_img.getImgData().data(), temp_img.getDimensions(), temp_img.getOffset(), temp_img.getFormat(), temp_img.getType());
  mSprite = std::make_shared<Sprite>(spriteTexture, Box(glm::vec2{200.0f, 200.0f}, glm::vec2{16, 16}));
  Image temp_img2("../src/heart.png");
  sprite2Texture.create(temp_img2.getDimensions().y, temp_img2.getDimensions().x, temp_img2.getInternalFormat());
  sprite2Texture.update(temp_img2.getImgData().data(), temp_img2.getDimensions(), temp_img2.getOffset(), temp_img2.getFormat(), temp_img2.getType());
  mSprite3 = std::make_shared<Sprite>(sprite2Texture, Box(glm::vec2{50.0f, 300.0f}, glm::vec2{16, 16}));
  mSprite2 = std::make_shared<Sprite>(spriteTexture, Box(glm::vec2{600.0f, 600.0f}, glm::vec2{16, 16}));
  Image tempImg("../src/SquareWBorder.png");
  std::shared_ptr<Texture2D> tempTexture = std::make_shared<Texture2D>();
  std::shared_ptr<Texture2D> tempTexture2 = std::make_shared<Texture2D>();
  std::shared_ptr<Texture2D> tempTexture3 = std::make_shared<Texture2D>();
  borderedImgTest.create(tempImg.getDimensions().y, tempImg.getDimensions().x, tempImg.getInternalFormat());
  borderedImgTest.update(tempImg.getImgData().data(), tempImg.getDimensions(), tempImg.getOffset(), tempImg.getFormat(), tempImg.getType());
  tempImg.recolorBorderedShape(lg::Color(135, 135, 135), lg::Color(170, 170, 170), lg::White);
  tempTexture->create(tempImg.getDimensions().y, tempImg.getDimensions().x, tempImg.getInternalFormat());
  tempTexture->update(tempImg.getImgData().data(), tempImg.getDimensions(), tempImg.getOffset(), tempImg.getFormat(), tempImg.getType());
  tempImg.recolorBorderedShape(lg::Color(210, 210, 210), lg::Color(170, 170, 170), lg::Color(170, 170, 170));
  tempTexture2->create(tempImg.getDimensions().y, tempImg.getDimensions().x, tempImg.getInternalFormat());
  tempTexture2->update(tempImg.getImgData().data(), tempImg.getDimensions(), tempImg.getOffset(), tempImg.getFormat(), tempImg.getType());
  tempImg.recolorBorderedShape(lg::Color(230, 230, 230), lg::Color(230, 230, 230), lg::Color(170, 170, 170));
  tempTexture3->create(tempImg.getDimensions().y, tempImg.getDimensions().x, tempImg.getInternalFormat());
  tempTexture3->update(tempImg.getImgData().data(), tempImg.getDimensions(), tempImg.getOffset(), tempImg.getFormat(), tempImg.getType());
  mNineSliced = std::make_unique<SlicedSprite>();
  Transform test;
  test.setPos({650.0f, 650.0f});
  test.setScale({200.0f, 50.0f});
  mNineSliced->setTexture(borderedImgTest);
  mNineSliced->setAllBorders(5, 5, 5, 5);
  mNineSliced->fillBorderColor(lg::Red);
  mNineSliced->setTransform(test);
  // This can change to doing the same thing text does for editing colors
  mButton = std::make_shared<Button>();
  Text text = Text(mNewFont, "Iris will be my wife.", 12);
  mButton->setText(text)
           .setTextColor(lg::Red)
           .setDefaultTexture(tempTexture)
           .setHoverTexture(tempTexture2)
           .setPressedTexture(tempTexture3)
           .setVerticalAlignment(Label::VerticalAlign::CENTER)
           .setHorizontalAlignment(Label::HorizontalAlign::CENTER)
           .setPos({250.0f, 250.0f})
           .resize({200, 50})
           .onClick(&MainMenu::buttonCallback);

  mScroll = std::make_shared<Scrollbar>(Scrollbar::VERTICAL, 0, 800);
  Button tempButton = Button();

  tempButton.setDefaultColor(lg::Grey)
          .setHoverColor(lg::Green)
          .setPressedColor(lg::Green)
          .setPadding(glm::vec2(50, 50))
          .setPos({900, 50})
          .resize({20, 60});
  mScroll->setButton(tempButton);

  Text labelText = Text(mNewFont, "My label.", 12);
  labelText.setColor(lg::Black);
  mLabel = std::make_shared<Label>(labelText);
  mLabel->setPos(glm::vec2(500.0f, 500.0f));
  mLabel->resize(glm::vec2(75.0f, 50.0f));
  mLabel->setHorizontalAlign(Label::HorizontalAlign::CENTER);
  mLabel->setVerticalAlign(Label::VerticalAlign::CENTER);
  mLabel->setBackgroundColor(lg::Yellow);

  mScroll->addComponent(mLabel)
         .addComponent(mButton);

  mScroll2 = std::make_shared<Scrollbar>(Scrollbar::HORIZONTAL, 0, 1000);
  tempButton.setDefaultColor(lg::Grey)
          .setHoverColor(lg::Green)
          .setPressedColor(lg::Green)
          .setPadding(glm::vec2(50, 50))
          .setPos({60, 900})
          .resize({60, 20});
  mScroll2->setButton(tempButton);
  mScroll2->addComponent(mLabel)
         .addComponent(mButton);

  labelText.setString("Menu");
  mMenu = std::make_shared<Menu>();
  mMenu->setPos({900, 900})
       .resize({75, 35})
       .setText(labelText)
       .setVerticalAlignment(Label::VerticalAlign::CENTER)
       .setHorizontalAlignment(Label::HorizontalAlign::CENTER);
  std::shared_ptr<MenuItem> tempMenu = std::make_shared<MenuItem>();
  labelText.setString("Menu2");
  tempMenu
       ->setText(labelText)
       .setVerticalAlignment(Label::VerticalAlign::CENTER)
       .setHorizontalAlignment(Label::HorizontalAlign::CENTER);
  mMenu->addMenuItem(tempMenu);
  std::shared_ptr<Menu> menu2 = std::make_shared<Menu>();
  labelText.setString("Drop2");
  menu2->setText(labelText)
       .setVerticalAlignment(Label::VerticalAlign::CENTER)
       .setHorizontalAlignment(Label::HorizontalAlign::CENTER);
  tempMenu = std::make_shared<MenuItem>();
  labelText.setString("Item2");
  tempMenu
       ->setText(labelText)
       .setVerticalAlignment(Label::VerticalAlign::CENTER)
       .setHorizontalAlignment(Label::HorizontalAlign::CENTER);
  menu2->addMenuItem(tempMenu);
  mMenu->addMenuItem(menu2);
  std::shared_ptr<Menu> menu3 = std::make_shared<Menu>();
  labelText.setString("Drop3");
  menu3->setText(labelText)
       .setVerticalAlignment(Label::VerticalAlign::CENTER)
       .setHorizontalAlignment(Label::HorizontalAlign::CENTER);
  tempMenu = std::make_shared<MenuItem>();
  labelText.setString("Item3");
  tempMenu
       ->setText(labelText)
       .setVerticalAlignment(Label::VerticalAlign::CENTER)
       .setHorizontalAlignment(Label::HorizontalAlign::CENTER);
  menu3->addMenuItem(tempMenu);
  mMenu->addMenuItem(menu3);
  // mLabel->setSprite(labelSprite);
  // mLabel->setText(labelText);
  // mFbo = std::make_shared<FrameBuffer>();
  // mFbo->bind();
  // RenderCommand::enableBlend();
  // RenderCommand::setClearColor(0.3f, 0.0f, 0.0f, 1.0f);
  // mFbo->unbind();
  // mFbo->invalidate(glm::uvec2{gWindowWidth, gWindowHeight}, mpResourceMngr);
  // mView = std::make_shared<Sprite>(glm::vec2{gWindowWidth / 2.0f, gWindowHeight / 2.0f}, glm::vec2{gWindowWidth, gWindowHeight}, lg::White);

  // mView->setTexture(mFbo->getTexture(), true);
  mCam = std::make_shared<OrthCamera>(0, 1920, 1080, 0);
  Box<glm::vec2> testBox = mSprite->getGlobalBounds(*mCam);
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
    mButton->handleEvent(tempEvent);
    mScroll->update(tempEvent);
    mScroll2->update(tempEvent);
    mMenu->handleEvent(tempEvent);
    switch(tempEvent.Type)
    {
      case Event::EventType::KeyPress:
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
      case Event::EventType::KeyRelease:
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
      case Event::EventType::WindowResize:
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
  mScroll2->draw();
  mMenu->draw();
  mLabel->draw();
  mNineSliced->draw();
  Renderer2D::endScene();
}

MainMenu::~MainMenu() 
{
}

bool MainMenu::shouldStateExit()
{
  return false;
}

void MainMenu::buttonCallback()
{
  std::cout << "Clicked\n";
}

// void MainMenu::dropdownCallbacK(const Button<glm::ivec2>& rVal)
// {
//   std::cout << "(" << rVal.getValue().x << ", " << rVal.getValue().y << ")" << std::endl;
// }