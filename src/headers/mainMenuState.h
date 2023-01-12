#ifndef MAINMENU_STATE_H
#define MAINMENU_STATE_H

#include "state.h"

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
    Font mFont;
    Text mText;
};

#endif