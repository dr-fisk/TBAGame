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
#include "resource/imageImporter.hpp"
#include "resource/gifImporter.hpp"

MainMenu::MainMenu(const std::stack<std::shared_ptr<State>>& crStates) :
                   State(crStates)
{
  std::string temp = "./Envy Code R.ttf"; //"Envy Code R.ttf";
  mStartTime = std::chrono::system_clock::now();
  mNewFont.loadFromFile(temp, 5);
  mText = std::make_shared<Text>(mNewFont, "FPS: 0", 12);
  mText->setPos({200.0f, 50.0f});
  mText->setColor(lg::Blue);
  std::shared_ptr<FrameSource> heartPng = ImageImporter::buildStaticFrame("../art.png");
  mSprite = std::make_shared<Sprite>(heartPng, Rect<float>(200.0f, 200.0f, 16, 16));
  mSprite3 = std::make_shared<Sprite>(ImageImporter::buildStaticFrame("../heart.png"), Rect<float>(50.0f, 300.0f, 16, 16));
  mSprite2 = std::make_shared<Sprite>(heartPng, Rect<float>(600.0f, 600.0f, 16, 16));
  Image tempImg("../SquareWBorder.png");
  tempImg.recolorBorderedShape(lg::Color(135, 135, 135), lg::Color(170, 170, 170), lg::White);
  std::shared_ptr<FrameSource> tempTexture = ImageImporter::buildStaticFrame(tempImg);
  std::shared_ptr<FrameSource> btn1 = ImageImporter::buildStaticFrame("../ButtonTexture.png");
  std::shared_ptr<FrameSource> btn2 = ImageImporter::buildStaticFrame("../InvertedButtonTexture.png");
  std::shared_ptr<FrameSource> gif = GifImporter::buildAnimatedFrameSource("../dancing-banana.gif", true);
  
  mGifSprite = std::make_shared<Sprite>(gif, Rect<float>(400.0f, 400.0f, gif->getCurrentUv().width, gif->getCurrentUv().height), false);

  
  SLOT(mEventSub, MainMenu::OnMouseMove);
  SLOT(mEventSub1, MainMenu::OnMousePress);
  SLOT(mEventSub2, MainMenu::OnMouseRelease);
  SLOT(mEventSub3, MainMenu::OnKeyboardPress);
  SLOT(mEventSub4, MainMenu::OnKeyboardRelease);
  SLOT(mEventSub5, MainMenu::OnWindowResize);
  mNineSliced = std::make_unique<SlicedSprite>();
  Transform test;
  test.setOrigin({650.0f, 650.0f});
  test.setScale({200.0f, 50.0f});
  mNineSliced->setFrameSource(tempTexture);
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
              Label("Menu",
                TextModifier().setTextColor(lg::Black)
                  .setFont(mNewFont)
                  .setFontSize(24),
                Modifier().setVerticalAlign(VerticalAlign::CENTER)
                  .setHorizontalAlign(HorizontalAlign::CENTER)))
           .setDefaultTexture(btn1)
           .setHoverTexture(btn2)
           .setPressedTexture(btn2)
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

  mpCheckbox = std::make_shared<ToggleButton>();
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

  mpTextbox = std::make_shared<TextBox>(
      Modifier().setVerticalAlign(VerticalAlign::CENTER)
        .setHorizontalAlign(HorizontalAlign::CENTER)
        .setPos({100, 100})
        .setScale({160, 32}),
      TextModifier().setTextColor(lg::Black)
        .setFont(mNewFont)
        .setFontSize(16),
      "Default");

      mEventSub6.setCallback(BIND_EVENT_FN(MainMenu::onSubmit));
      mpTextbox->addSubmitEventListener(mEventSub6);
//  .setBorderColor(ButtonState::DEFAULT_STATE, lg::Color(135, 135, 135))
//  .setBorderColor(ButtonState::HOVER_STATE, lg::Color(175, 175, 175))
//  .setBorderColor(ButtonState::PRESSED_STATE, lg::Color(230, 230, 230))
//  .setBorderColor(ButtonState::DEFAULT_STATE, lg::Black)
//  .setBorderColor(ButtonState::HOVER_STATE, lg::Black)
//  .setBorderColor(ButtonState::PRESSED_STATE, lg::Black)
//  .onClick(&MainMenu::buttonCallback);

  // Need to figure out a way of setting a camera dimensions and getting window dimensions
  mCam = std::make_shared<OrthCamera>(0, 1920, 1061, 0);
  Rect<float> testBox = mSprite->getGlobalBounds(*mCam);
  // mCam.setPosition({0.0f, 0.0f, 0.0f});
  curr_pos = mSprite->getPos();
  xMove = 0.0f;
  yMove = 0.0f;

  mpFrame = std::make_shared<Frame>();
  mpFrame->setPos({0, 0});
  mpFrame->resize({1080, 1920});
  mpFrame->addComponent(mButton);
  mpFrame->addComponent(mpCheckbox);
  mpFrame->addComponent(mScroll);
  mpFrame->addComponent(mScroll2);
  mpFrame->addComponent(mMenu);
  mpFrame->addComponent(mpTextbox);
}

void MainMenu::update(const std::shared_ptr<RenderTarget>&, const double cDeltaTime)
{
  mGifSprite->update(cDeltaTime);
}

void MainMenu::fixedUpdate(const std::shared_ptr<RenderTarget>&, const double cDeltaTime)
{
  // std::string temp = "FPS: " + std::to_string(gFps);
  // mText->updateText(temp);

  sprite_pos = mSprite->getPos();
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

void MainMenu::render(const std::shared_ptr<RenderTarget>&, const double)
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
  mpTextbox->draw();
  mGifSprite->draw();
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

void MainMenu::OnMouseMove(lre::MouseMoveEvent&)
{
  // std::cout << "We are fucking here\n";
}

void MainMenu::OnMousePress(lre::MouseButtonPressEvent&)
{
  // std::cout << "Mouse press lesgo\n";
}

void MainMenu::OnMouseRelease(lre::MouseButtonReleaseEvent&)
{
  // std::cout << "Mouse release lesgo\n";
}

void MainMenu::OnKeyboardPress(lre::KeyboardPressEvent& crEvent)
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

void MainMenu::OnKeyboardRelease(lre::KeyboardReleaseEvent& crEvent)
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

void MainMenu::OnWindowResize(lre::WindowResizeEvent& crEvent)
{
    lg::Window::WindowView view = lg::Window::getView();
    mCam->setProjection(view.x, crEvent.getWidth(), crEvent.getHeight(), view.y);
    glViewport(view.x, view.y, crEvent.getWidth(), crEvent.getHeight());
}

void MainMenu::onSubmit(SubmitEvent<Component>& rEvent)
{
  std::cout << rEvent.mValue << std::endl;
}