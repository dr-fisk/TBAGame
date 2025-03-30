#ifndef MAINMENU_STATE_HPP
#define MAINMENU_STATE_HPP

#include <memory>
#include <vector>
#include <stack>
#include <chrono>

#include "state.hpp"
#include "lestTtf.hpp"
#include "resource/font.hpp"
#include "drawable/text.hpp"
#include "drawable/sprite.hpp"
#include "graphics/button.hpp"
#include "graphics/menu.hpp"
#include "graphics/label.hpp"
#include "graphics/scrollbar.hpp"
#include "renderEngine/frameBuffer.hpp"
#include "glm/vec2.hpp"
#include "renderer/camera.hpp"
#include "drawable/nineSlicedSprite.hpp"
#include "graphics/toggleButton.hpp"
#include "input/keyboardEvent.hpp"
#include "event/eventSubscriber.hpp"
#include "input/mouseEvent.hpp"
#include "input/keyboardEvent.hpp"
#include "input/windowEvent.hpp"
#include "graphics/frame.hpp"

class MainMenu : public State
{
  public:
    MainMenu(const std::stack<std::shared_ptr<State>>& crStates);
    ~MainMenu();
    void fixedUpdate(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime);
    void render(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime);
    bool shouldStateExit();

  private:
    static void buttonCallback();
    void OnMouseMove(lre::MouseMoveEvent& crEvent);
    void OnMousePress(lre::MouseButtonPressEvent& crEvent);
    void OnMouseRelease(lre::MouseButtonReleaseEvent& crEvent);
    void OnKeyboardPress(lre::KeyboardPressEvent& crEvent);
    void OnKeyboardRelease(lre::KeyboardReleaseEvent& crEvent);
    void OnWindowResize(lre::WindowResizeEvent& crEvent);

    // static void dropdownCallbacK(const Button<glm::ivec2>& rVal);s
    std::shared_ptr<Frame> mpFrame;
    LestTrueType ttf;
    Font mNewFont;
    std::shared_ptr<Text> mText;
    std::shared_ptr<Sprite> mSprite;
    std::shared_ptr<Sprite> mSprite2;
    std::shared_ptr<Sprite> mSprite3;
    std::shared_ptr<Button> mButton;
    std::shared_ptr<Scrollbar> mScroll;
    std::shared_ptr<Scrollbar> mScroll2;
    std::shared_ptr<Menu> mMenu;
    std::chrono::time_point<std::chrono::system_clock> mStartTime;
    std::shared_ptr<FrameBuffer> mFbo;
    std::shared_ptr<Sprite> mView;
    std::shared_ptr<OrthCamera> mCam;
    std::shared_ptr<Label> mLabel;
    std::unique_ptr<SlicedSprite> mNineSliced;
    std::shared_ptr<ToggleButton> mpCheckbox;
    glm::vec2 sprite_pos;
    glm::vec2 curr_pos;
    float xMove;
    float yMove;
    Texture2D spriteTexture;
    Texture2D sprite2Texture;
    Texture2D borderedImgTest;
    EventSubscriber<lre::MouseMoveEvent> mEventSub;
    EventSubscriber<lre::MouseButtonPressEvent> mEventSub1;
    EventSubscriber<lre::MouseButtonReleaseEvent> mEventSub2;
    EventSubscriber<lre::KeyboardPressEvent> mEventSub3;
    EventSubscriber<lre::KeyboardReleaseEvent> mEventSub4;
    EventSubscriber<lre::WindowResizeEvent> mEventSub5;
};

#endif