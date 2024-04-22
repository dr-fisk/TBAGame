// Update to chrono
#include <ctime>
#include <future>
#include <atomic>
#include <mutex>
#include <queue>

#include "game.hpp"
#include "states/mainMenuState.hpp"
#include "states/exceptionState.hpp"
#include "renderer/renderer2D.hpp"
#include "renderer/renderCommand.hpp"
#include "glm/vec2.hpp"
#include "window/window.hpp"

lg::Window::WindowView gView;
uint16_t gFrames = 0;
uint16_t gFps = 0;

//! @brief Initializes Main State
//!
//! @return None
void Game::initMainState()
{
  //mStates.push(std::make_shared<ExceptionState>(mStates, "TESTING", mShaders[MAIN_SHADER], mpWindow->getGlWindow(), mpVao));
  mStates.push(std::make_shared<MainMenu>(mStates, mpRenderEngine));
}

//! @brief Default Constructor
//!
//! @return Game Object
Game::Game()
{
  mpWindow = std::make_shared<RenderWindow>(1920, 1080, "Lest Window");   
  /* NOTE: BEFORE ANY GL CALL, THAT IS NOT GLFW but GL, SET ACTIVE MUST BE CALLED OR ELSE OPENGL FAILS */
  // mpWindow->setActive();

  // //init GL attributes for window
  mpWindow->initWindow();
  RenderCommand::enableBlend();

  int32_t view[4] = {};
  glGetIntegerv(GL_VIEWPORT, view);
  gView.x = view[0];
  gView.y = view[1];
  gView.WindowWidth = view[2];
  gView.WindowHeight = view[3];
  mpRenderEngine = std::make_shared<RenderEngine>();

  // mFbo = std::make_shared<FrameBuffer>();

  initMainState();
  /* vbo holds vertex data (cooridnates and RGB color)
     You can combine both in one vbo or separate vbo, if
     combining you must specify which are coords and which
     are rgb, vao is like a file descriptor table but for a vertex
     and holds vbo's */

/*     try {
      throw Exception("This is a test\n");
    } catch(Exception &e) {
      std::cout << e.what();
    }  */
  mGameRuntime = time(nullptr);
  mStartTime = glfwGetTime();

}

//! @brief Default Destructor
//!
//! @return None
Game::~Game()
{
  while(!mStates.empty())
  {
    mStates.pop();
  }

  // mFbo.reset();
  mpRenderEngine.reset();
  mpWindow.reset();
  glfwTerminate();
}

// std::mutex queueMutex;

// struct CtxData
// {
//   std::shared_ptr<RenderWindow> CtxWindow;
//   std::stack<std::shared_ptr<State>> CtxStates;
//   std::future<void> CtxFuture;
// };

// std::queue<uint32_t> ZombieWindows;
// std::unordered_map<uint32_t, CtxData> CtxMap;

// Plan is to create a scene graph class and allow scene graphs to be copyable
// void spawnedWindowThread(std::stack<std::shared_ptr<State>>& rState, std::shared_ptr<RenderWindow>& rWindow,
//                          const uint32_t cId)
// {
//   std::shared_ptr<RenderWindow> wdw = rWindow;
//   double deltaTime = 0;
//   double smoothDeltaTime = 0;
//   double currentTime = 0;
//   double endFrameTime = 0;
//   const double FIXED_TIMESTEP = 1.0f/50.0f;
//   wdw->setActive();
//   RenderCommand::setClearColor(0.3f, 0.0f, 0.0f, 1.0f);
//   RenderCommand::enableBlend();

//   while(!rState.empty() && wdw->isOpen())
//   {
//     endFrameTime = glfwGetTime();
//     // std::chrono::duration<float>(mEndTime - mFrameTime).count();
//     deltaTime = endFrameTime - currentTime;
//     if (deltaTime > 0.25f)
//     {
//       deltaTime = 0.25;
//     }
//     currentTime = endFrameTime;
//     // mFrameTime = mEndTime;
//     smoothDeltaTime += deltaTime;

//     while(smoothDeltaTime >= FIXED_TIMESTEP)
//     {
//       rState.top()->fixedUpdate(wdw, FIXED_TIMESTEP);
//       smoothDeltaTime -= FIXED_TIMESTEP;
//     }

//     rState.top()->render(wdw, 0);
//     wdw->display();
//   }
  
//   queueMutex.lock();
//   ZombieWindows.push(cId);
//   rState.pop();
//   queueMutex.unlock();
// }

//! @brief Runs gameloop until window has been closed or states popped
//!
//! @return None
void Game::runGame()
{
  double deltaTime = 0;
  double smoothDeltaTime = 0;
  double currentTime = 0;
  double endFrameTime = 0;
  const double FIXED_TIMESTEP = 1.0f/50.0f;

  // uint32_t cId = 0;

  // Definitely can be it's own function later
  // CtxMap[cId] = {
  //   mpWindow->createSharedWindow(), 
  //   std::stack<std::shared_ptr<State>>(), 
  //   std::future<void>()
  //   };
  
  // CtxMap[cId].CtxStates.push(std::make_shared<MainMenu>(CtxMap[cId].CtxStates, mpRenderEngine));

  // CtxMap[cId].CtxFuture = std::async(std::launch::async, &spawnedWindowThread,
  //   std::ref(CtxMap[cId].CtxStates),
  //   std::ref(CtxMap[cId].CtxWindow),
  //   cId);

  // cId ++;

  // CtxMap[cId] = {
  //   mpWindow->createSharedWindow(), 
  //   std::stack<std::shared_ptr<State>>(), 
  //   std::future<void>()
  //   };
  
  // CtxMap[cId].CtxStates.push(std::make_shared<MainMenu>(CtxMap[cId].CtxStates, mpRenderEngine));

  // CtxMap[cId].CtxFuture = std::async(std::launch::async, &spawnedWindowThread,
  //   std::ref(CtxMap[cId].CtxStates),
  //   std::ref(CtxMap[cId].CtxWindow),
  //   cId);
  
  // cId ++;

  RenderCommand::setClearColor(0.3f, 0.0f, 0.0f, 1.0f);
  while(!mStates.empty() && mpWindow->isOpen())
  {
    // mEndTime = std::chrono::high_resolution_clock::now();
    endFrameTime = glfwGetTime();
    // std::chrono::duration<float>(mEndTime - mFrameTime).count();
    deltaTime = endFrameTime - currentTime;
    if (deltaTime > 0.25f)
    {
      deltaTime = 0.25;
    }
    currentTime = endFrameTime;
    // mFrameTime = mEndTime;
    smoothDeltaTime += deltaTime;
    if (currentTime - mStartTime >= 1.0d)
    {
      gFps = gFrames / (currentTime - mStartTime);
      gFrames = 0;
      mpWindow->setWindowTitle(std::to_string(gFps));
      mStartTime = currentTime;
    }

    if (mStates.top()->shouldStateExit())
    {
      mStates.pop();
    }
    
    mStates.top()->update(mpWindow, deltaTime);

    while(smoothDeltaTime >= FIXED_TIMESTEP)
    {
      mStates.top()->fixedUpdate(mpWindow, FIXED_TIMESTEP);
      smoothDeltaTime -= FIXED_TIMESTEP;
    }

    // Need another delta time here
    mStates.top()->lateUpdate(mpWindow, FIXED_TIMESTEP);

    mStates.top()->render(mpWindow, smoothDeltaTime / FIXED_TIMESTEP);
    // mpWindow->display();

    RenderCommand::pollEvents();

    // queueMutex.lock();
    
    // while(!ZombieWindows.empty())
    // {
    //   CtxMap.at(ZombieWindows.front()).CtxWindow->setActive();
    //   CtxMap.erase(ZombieWindows.front());
    //   ZombieWindows.pop();
    //   mpWindow->setActive();
    // }

    // queueMutex.unlock();

    gFrames ++;
    // std::cout << "Delta: " << deltaTime << std::endl;
  }

  gameEnd();
}

//! @brief Handles how application should act when game is closed
//!
//! @return None
void Game::gameEnd()
{
}