#ifndef MAINMENU_STATE_H
#define MAINMENU_STATE_H

#include "state.h"

class MainMenu : public State {
  public:
    MainMenu(std::shared_ptr<RenderWindow> wind, std::stack<std::shared_ptr<State>> s);
    ~MainMenu();
};

#endif