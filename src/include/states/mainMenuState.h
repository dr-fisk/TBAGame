#ifndef MAINMENU_STATE_H
#define MAINMENU_STATE_H

#include <memory>
#include <vector>
#include <stack>
#include <chrono>

#include "state.h"
#include "lestTtf.h"
#include "resource/font.h"
#include "renderEngine/texture.h"

class MainMenu : public State {
  public:
    MainMenu(const std::stack<std::shared_ptr<State>>& crStates, const std::shared_ptr<RenderEngine>& crpRenderEngine,
             const std::shared_ptr<BatchBuffer>& crpBatchBuffer);
    ~MainMenu();
    void render(const std::shared_ptr<RenderTarget> &crpTarget);
    void update(const std::shared_ptr<RenderTarget> &crpTarget);
    bool shouldStateExit();

  private:
    Texture mTexture;
    LestTrueType ttf;
    std::vector<std::shared_ptr<Rect>> final;
    std::shared_ptr<Rect> temprect;
    std::shared_ptr<Font> mNewFont;
    std::shared_ptr<Drawable> mText;
    std::chrono::time_point<std::chrono::system_clock> mStartTime;
};

#endif