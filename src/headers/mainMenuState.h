#ifndef MAINMENU_STATE_H
#define MAINMENU_STATE_H

#include "state.h"

class MainMenu : public State {
  public:
    MainMenu(const std::stack<std::shared_ptr<State>> &crStates);
    ~MainMenu();
    void render(const std::shared_ptr<RenderTarget> &crpTarget);
    void update();
    bool shouldStateExit();

  private:
    Mesh mMesh;
    Mesh mMesh2;
    BatchBuffer mTestBB;
    Font mFont;
    Text mText;
};

#endif