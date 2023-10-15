#ifndef MAINMENU_STATE_H
#define MAINMENU_STATE_H

#include <memory>
#include <vector>
#include <stack>

#include "state.h"
#include "lestTtf.h"
#include "font.h"
#include "drawable/texture.h"

class MainMenu : public State {
  public:
    MainMenu(const std::stack<std::shared_ptr<State>> &crStates, const std::shared_ptr<BatchBuffer> &crpBatchBuffer);
    ~MainMenu();
    void render(const std::shared_ptr<RenderTarget> &crpTarget);
    void update();
    bool shouldStateExit();

  private:
    Texture mTexture;
    LestTrueType ttf;
    std::vector<Rect> temprect;
    std::vector<std::shared_ptr<Rect>> final;
    Font mNewFont;
};

#endif