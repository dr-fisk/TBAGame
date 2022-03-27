#ifndef GAME_H
#define GAME_H

#include "mainMenuState.h"
#include "renderTarget.h"
#include "renderWindow.h"

class Game {
  public:
    Game();
    ~Game();
    void gameLoop();
  private:
    std::stack<State *> states;
    RenderWindow *window;
    clock_t gameRuntime;

    void initMainState();
    void gameEnd(); 
    void render(RenderTarget *target);
};

#endif