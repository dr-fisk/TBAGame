#ifndef GAME_H
#define GAME_H

#include <memory>
#include <stack>

#include "state.h"
#include "renderWindow.h"
#include "lestTtf.h"

#define ONE_SEC 1

class Game {
  public:
    Game();
    ~Game();
    void gameLoop();
  private:
    std::stack<std::shared_ptr<State>> mStates;
    std::shared_ptr<RenderWindow> mpWindow;
    std::shared_ptr<BatchBuffer> mpBatchBuffer;
    LestTrueType ttf;
    int mGameRuntime;
    int mStartTime;
    int mEndTime;
    static int mFps;

    void initMainState();
    void gameEnd();
};

#endif