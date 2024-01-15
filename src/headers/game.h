#ifndef GAME_H
#define GAME_H

#include <memory>
#include <stack>
#include <chrono>

#include "states/state.h"
#include "renderEngine/renderEngine.h"
#include "window/renderWindow.h"
#include "lestTtf.h"
#include "renderEngine/frameBuffer.h"

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
    std::shared_ptr<RenderEngine> mpRenderEngine;
    LestTrueType ttf;
    int mGameRuntime;
    std::chrono::time_point<std::chrono::steady_clock> mStartTime;
    std::chrono::time_point<std::chrono::steady_clock> mFrameTime;
    std::chrono::time_point<std::chrono::steady_clock> mEndTime;
    int mFps;

    void initMainState();
    void initTextureSampler();
    void gameEnd();
    GLFWwindow* wind;
        // std::shared_ptr<FrameBuffer> mFbo;

};

#endif