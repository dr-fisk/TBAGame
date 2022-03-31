#ifndef GAME_H
#define GAME_H

#include "mainMenuState.h"
#include "batchBuffer.h"
#include "renderWindow.h"

class Game {
  public:
    Game();
    ~Game();
    void gameLoop();
  private:
    std::stack<std::shared_ptr<State>> states;
    std::shared_ptr<RenderWindow> window;
    clock_t gameRuntime;

    void initMainState();
    void gameEnd(); 
    void render(const std::shared_ptr<RenderTarget> &target);
};

#endif