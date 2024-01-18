#ifndef MAINMENU_STATE_H
#define MAINMENU_STATE_H

#include <memory>
#include <vector>
#include <stack>
#include <chrono>

#include "state.h"
#include "lestTtf.h"
#include "resource/font.h"
#include "drawable/text.h"
#include "drawable/sprite.h"
#include "graphics/button.h"
#include "graphics/dropdownmenu.h"
#include "graphics/scrollbar.h"
#include "renderEngine/frameBuffer.h"
#include "glm/vec2.hpp"

class MainMenu : public State
{
  public:
    MainMenu(const std::stack<std::shared_ptr<State>>& crStates, std::shared_ptr<RenderEngine>& crpRenderEngine);
    ~MainMenu();
    void update(const std::shared_ptr<RenderTarget>& crpTarget, const float cDeltaTime);
    bool shouldStateExit();

  private:
    static void buttonCallback(const Button<>& rVal);
    static void dropdownCallbacK(const Button<glm::ivec2>& rVal);
    LestTrueType ttf;
    std::shared_ptr<Font> mNewFont;
    std::shared_ptr<Text> mText;
    std::shared_ptr<Sprite> mSprite;
    std::shared_ptr<Sprite> mSprite2;
    std::shared_ptr<Sprite> mSprite3;
    std::shared_ptr<Button<>> mButton;
    std::shared_ptr<Scrollbar> mScroll;
    std::shared_ptr<DropDownMenu<glm::ivec2>> mMenu;
    std::chrono::time_point<std::chrono::system_clock> mStartTime;
    std::shared_ptr<FrameBuffer> mFbo;
    std::shared_ptr<Sprite> mView;
};

#endif