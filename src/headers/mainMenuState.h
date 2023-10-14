#ifndef MAINMENU_STATE_H
#define MAINMENU_STATE_H

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
    Mesh mMesh;
    Mesh mMesh2;
    PngFont mFont;
    PngText mText;
    Texture mTexture;
    LestTrueType ttf;
    std::vector<Rect> temprect;
    std::vector<std::shared_ptr<Rect>> final;
    Font mNewFont;
};

#endif