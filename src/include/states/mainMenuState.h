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


class MainMenu : public State
{
  public:
    MainMenu(const std::stack<std::shared_ptr<State>>& crStates, std::shared_ptr<RenderEngine>& crpRenderEngine);
    ~MainMenu();
    void update(const std::shared_ptr<RenderTarget>& crpTarget, const float cDeltaTime);
    bool shouldStateExit();

  private:
    static void buttonCallback(const Button<>& rVal);
    static void dropdownCallbacK(const Button<Vector2<int32_t>>& rVal);
    LestTrueType ttf;
    std::shared_ptr<Font> mNewFont;
    std::shared_ptr<Text> mText;
    std::shared_ptr<Sprite> mSprite;
    std::shared_ptr<Sprite> mSprite2;
    std::shared_ptr<Sprite> mSprite3;
    std::shared_ptr<Button<>> mButton;
    std::shared_ptr<Scrollbar> mScroll;
    std::shared_ptr<DropDownMenu<Vector2<int32_t>>> mMenu;
    std::chrono::time_point<std::chrono::system_clock> mStartTime;
};

#endif