#ifndef GAME_H
#define GAME_H

#include "mainMenuState.h"
#include "exceptionState.h"
#include "renderWindow.h"


#define ONE_SEC 1

class Game {
  public:
    Game();
    ~Game();
    void gameLoop();
  private:
    std::stack<std::shared_ptr<State>> mStates;
    std::shared_ptr<RenderWindow> mpWindow;
    std::map<std::string, std::shared_ptr<Shader>> mShaders;
    int mGameRuntime;
    int mStartTime;
    int mEndTime;
    static int mFps;

    void initMainState();
    void initShaders();
    void deleteShaders();
    void gameEnd();
};

#endif