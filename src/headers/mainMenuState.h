#ifndef MAINMENU_STATE_H
#define MAINMENU_STATE_H

#include "state.h"

class MainMenu : public State {
  public:
    MainMenu(RenderWindow *wind, std::stack<State *> s);
    ~MainMenu();
};

#endif