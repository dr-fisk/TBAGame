#include <cmath>
#include <algorithm>
#include <queue>
#include <iostream>

#include "states/mainMenuState.hpp"
#include "drawable/text.hpp"
#include "input/mouse.hpp"
#include "shapes/box.hpp"
#include "resource/image.hpp"
#include "renderer/renderer2D.hpp"
#include "renderer/renderCommand.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "math/lestMath.hpp"
#include "event/lestRenderEngineEventManager.hpp"
#include "window/window.hpp"

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>>& crStates) :
                   State(crStates)
{
  std::string temp = "../TtfFont/Limelight.ttf"; //"Envy Code R.ttf";
  mStartTime = std::chrono::system_clock::now();
  mNewFont.loadFromFile(temp, 5);
  mText = std::make_shared<Text>(mNewFont, "FPS: 0", 12);
  mText->setPos({200.0f, 50.0f});
  mText->setColor(lg::Blue);
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
  borderedImgTest.create(tempImg.getDimensions().y, tempImg.getDimensions().x, tempImg.getInternalFormat());
  borderedImgTest.update(tempImg.getImgData().data(), tempImg.getDimensions(), tempImg.getOffset(), tempImg.getFormat(), tempImg.getType());
  tempImg.recolorBorderedShape(lg::Color(135, 135, 135), lg::Color(170, 170, 170), lg::White);
  tempTexture->create(tempImg.getDimensions().y, tempImg.getDimensions().x, tempImg.getInternalFormat());
  tempTexture->update(tempImg.getImgData().data(), tempImg.getDimensions(), tempImg.getOffset(), tempImg.getFormat(), tempImg.getType());
  Image btnImg("../src/ButtonTexture.png");
  Image btnImg2("../src/InvertedButtonTexture.png");
  std::shared_ptr<Texture2D> btnTexture = std::make_shared<Texture2D>();
  btnTexture->create(btnImg.getDimensions().y, btnImg.getDimensions().x, btnImg.getInternalFormat());
  btnTexture->update(btnImg.getImgData().data(), btnImg.getDimensions(), btnImg.getOffset(), btnImg.getFormat(), btnImg.getType());
  std::shared_ptr<Texture2D> btnTexture2 = std::make_shared<Texture2D>();
  btnTexture2->create(btnImg2.getDimensions().y, btnImg2.getDimensions().x, btnImg2.getInternalFormat());
  btnTexture2->update(btnImg2.getImgData().data(), btnImg2.getDimensions(), btnImg2.getOffset(), btnImg2.getFormat(), btnImg2.getType());
  SLOT(mEventSub, MainMenu::OnMouseMove);
  SLOT(mEventSub1, MainMenu::OnMousePress);
  SLOT(mEventSub2, MainMenu::OnMouseRelease);
  SLOT(mEventSub3, MainMenu::OnKeyboardPress);
  SLOT(mEventSub4, MainMenu::OnKeyboardRelease);
  SLOT(mEventSub5, MainMenu::OnWindowResize);
  mNineSliced = std::make_unique<SlicedSprite>();
  Transform test;
  test.setPos({650.0f, 650.0f});
  test.setScale({200.0f, 50.0f});
  mNineSliced->setTexture(borderedImgTest);
  mNineSliced->setBorders(5, 5, 5, 5);
  mNineSliced->fillBorderColor(lg::Red);
  mNineSliced->setTransform(test);
  // This can change to doing the same thing text does for editing colors
  mButton = std::make_shared<Button>();

  // TODO: Figure out how to update label so that order of calls doesn't matter
  // currently if Label is set first and button calls set size and pos, label will use accordingly
  // likewise if after label will use it's own
  //
  // Solution in my mind: Constraints in Modifier() class. This way parent can propagate sizes down and calc constraints
  // when an update happens
  mButton->setLabel(
              Label("ABCDEFGHIJKLMNOPQRSTUV",
                TextModifier().setTextColor(lg::Black)
                  .setFont(mNewFont)
                  .setFontSize(18),
                Modifier().setVerticalAlign(VerticalAlign::CENTER)
                  .setHorizontalAlign(HorizontalAlign::CENTER)))
           .setDefaultTexture(btnTexture)
           .setHoverTexture(btnTexture2)
           .setPressedTexture(btnTexture2)
           .setPos({250.0f, 250.0f})
           .resize({300, 62})
           .setBorder(2)
          //  .setBorderColor(ButtonState::DEFAULT_STATE, lg::Color(135, 135, 135))
          //  .setBorderColor(ButtonState::HOVER_STATE, lg::Color(175, 175, 175))
          //  .setBorderColor(ButtonState::PRESSED_STATE, lg::Color(230, 230, 230))
           .setBorderColor(ButtonState::DEFAULT_STATE, lg::Black)
           .setBorderColor(ButtonState::HOVER_STATE, lg::Black)
           .setBorderColor(ButtonState::PRESSED_STATE, lg::Black)
           .onClick(&MainMenu::buttonCallback);

  mScroll = std::make_shared<Scrollbar>(Scrollbar::VERTICAL, 0, 800);
  std::shared_ptr<Button> tempButton = std::make_shared<Button>();

  tempButton->setBackgroundColor(ButtonState::DEFAULT_STATE, lg::Grey)
          .setBackgroundColor(ButtonState::HOVER_STATE, lg::Green)
          .setBackgroundColor(ButtonState::PRESSED_STATE, lg::Green)
          .setPadding(glm::vec2(50, 50))
          .setPos({900, 50})
          .resize({20, 60});
  mScroll->setButton(tempButton);

  mLabel = std::make_shared<Label>("My label.",
    TextModifier().setFontSize(12)
      .setTextColor(lg::Black)
      .setFont(mNewFont),
    Modifier().setBackGroundColor(lg::White)
        .setPos(glm::vec2(500.0f, 500.0f))
        .setScale(glm::vec2(75.0f, 50.0f))
        .setHorizontalAlign(HorizontalAlign::CENTER)
        .setVerticalAlign(VerticalAlign::CENTER));

  mScroll->addComponent(mLabel)
         .addComponent(mButton);

  mScroll2 = std::make_shared<Scrollbar>(Scrollbar::HORIZONTAL, 0, 1000);
  tempButton = std::make_shared<Button>();
  tempButton->setBackgroundColor(ButtonState::DEFAULT_STATE, lg::Grey)
          .setBackgroundColor(ButtonState::HOVER_STATE, lg::Green)
          .setBackgroundColor(ButtonState::PRESSED_STATE, lg::Green)
          .setPadding(glm::vec2(50, 50))
          .setPos({60, 900})
          .resize({60, 20});
  mScroll2->setButton(tempButton);
  mScroll2->addComponent(mLabel)
         .addComponent(mButton);

  mMenu = std::make_shared<Menu>();
  mMenu->setLabel(
          Label("Menu",
                Modifier().setVerticalAlign(VerticalAlign::CENTER)
                  .setHorizontalAlign(HorizontalAlign::CENTER),
                TextModifier().setFontSize(12)
                  .setTextColor(lg::Black)
                  .setFont(mNewFont)
            ))
       .setPos({900, 900})
       .resize({75, 35});

  std::shared_ptr<MenuItem> tempMenu = std::make_shared<MenuItem>();
  tempMenu->setLabel(
          Label("Menu2",
                Modifier().setVerticalAlign(VerticalAlign::CENTER)
                  .setHorizontalAlign(HorizontalAlign::CENTER),
                TextModifier().setFontSize(12)
                  .setTextColor(lg::Black)
                  .setFont(mNewFont)
            )
        );
  std::shared_ptr<Menu> menu2 = std::make_shared<Menu>();
  menu2->setLabel(
          Label("Drop2",
                Modifier().setVerticalAlign(VerticalAlign::CENTER)
                  .setHorizontalAlign(HorizontalAlign::CENTER),
                TextModifier().setFontSize(12)
                  .setTextColor(lg::Black)
                  .setFont(mNewFont)
            )
        );
  tempMenu = std::make_shared<MenuItem>();
  tempMenu->setLabel(
          Label("Item2",
                Modifier().setVerticalAlign(VerticalAlign::CENTER)
                  .setHorizontalAlign(HorizontalAlign::CENTER),
                TextModifier().setFontSize(12)
                  .setTextColor(lg::Black)
                  .setFont(mNewFont)
            )
        );
  menu2->addMenuItem(tempMenu);
  mMenu->addMenuItem(menu2);
  std::shared_ptr<Menu> menu3 = std::make_shared<Menu>();
  menu3->setLabel(
          Label("Drop3",
                Modifier().setVerticalAlign(VerticalAlign::CENTER)
                  .setHorizontalAlign(HorizontalAlign::CENTER),
                TextModifier().setFontSize(12)
                  .setTextColor(lg::Black)
                  .setFont(mNewFont)
            )
        );
  tempMenu = std::make_shared<MenuItem>();
  tempMenu->setLabel(
          Label("Item3",
                Modifier().setVerticalAlign(VerticalAlign::CENTER)
                  .setHorizontalAlign(HorizontalAlign::CENTER),
                TextModifier().setFontSize(12)
                  .setTextColor(lg::Black)
                  .setFont(mNewFont)
            )
        );
  menu3->addMenuItem(tempMenu);
  mMenu->addMenuItem(menu3);

  mpCheckbox = std::make_unique<ToggleButton>();
  mpCheckbox->resize({32,32})
            .setPos({550, 550})
            .setBackgroundColor(ButtonState::DEFAULT_STATE, lg::White)
            .setBackgroundColor(ButtonState::HOVER_STATE, lg::White)
            .setBackgroundColor(ButtonState::PRESSED_STATE, lg::White)
            .setBorder(2)
            .setBorderColor(ButtonState::DEFAULT_STATE, lg::Black)
            .setBorderColor(ButtonState::HOVER_STATE, lg::Grey)
            .setBorderColor(ButtonState::PRESSED_STATE, lg::White);
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
  while(crpTarget->pollEvent(tempEvent))
  {
    // mButton->handleEvent(tempEvent);
    // mScroll->update(tempEvent);
    // mScroll2->update(tempEvent);
    // mMenu->handleEvent(tempEvent);
    // mpCheckbox->handleEvent(tempEvent);
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
  mpCheckbox->draw();
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

void MainMenu::OnMouseMove(LestRenderEngine::MouseMoveEvent& crEvent)
{
  // std::cout << "We are fucking here\n";
}

void MainMenu::OnMousePress(LestRenderEngine::MouseButtonPressEvent& crEvent)
{
  // std::cout << "Mouse press lesgo\n";
}

void MainMenu::OnMouseRelease(LestRenderEngine::MouseButtonReleaseEvent& crEvent)
{
  // std::cout << "Mouse release lesgo\n";
}

void MainMenu::OnKeyboardPress(LestRenderEngine::KeyboardPressEvent& crEvent)
{
  switch(crEvent.getKey())
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
}

void MainMenu::OnKeyboardRelease(LestRenderEngine::KeyboardReleaseEvent& crEvent)
{
  switch(crEvent.getKey())
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

void MainMenu::OnWindowResize(LestRenderEngine::WindowResizeEvent& crEvent)
{
    lg::Window::WindowView view = lg::Window::getView();
    mCam->setProjection(view.x, crEvent.getWidth(), crEvent.getHeight(), view.y);
    glViewport(view.x, view.y, crEvent.getWidth(), crEvent.getHeight());
}