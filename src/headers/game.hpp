#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <stack>
// #include <chrono>

#include "states/state.hpp"
#include "renderEngine/resourceManager.hpp"
#include "window/renderWindow.hpp"
#include "lestTtf.h"
#include "renderEngine/frameBuffer.hpp"

#define ONE_SEC 1

class Game {
  public:
    Game();
    ~Game();
    void runGame();
  private:
    std::stack<std::shared_ptr<State>> mStates;
    std::shared_ptr<RenderWindow> mpWindow;
    std::shared_ptr<ResourceManager> mpResourceMngr;
    LestTrueType ttf;
    int mGameRuntime;
    // std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;
    // std::chrono::time_point<std::chrono::high_resolution_clock> mFrameTime;
    // std::chrono::time_point<std::chrono::high_resolution_clock> mEndTime;
    double mStartTime;
    double mEndTime;
    int mFps;

    void initMainState();
    void gameEnd();
    GLFWwindow* wind;
        // std::shared_ptr<FrameBuffer> mFbo;

};

#endif