#ifndef MAINMENU_STATE_HPP
#define MAINMENU_STATE_HPP

#include <memory>
#include <vector>
#include <stack>
#include <chrono>

#include "state.hpp"
#include "lestTtf.h"
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
    // static void dropdownCallbacK(const Button<glm::ivec2>& rVal);
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
    std::unique_ptr<ToggleButton> mpCheckbox;
    glm::vec2 sprite_pos;
    glm::vec2 curr_pos;
    float xMove;
    float yMove;
    Texture2D spriteTexture;
    Texture2D sprite2Texture;
    Texture2D borderedImgTest;
};

#endif