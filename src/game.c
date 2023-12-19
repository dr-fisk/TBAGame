// Update to chrono
#include <ctime>

#include "game.h"
#include "mainMenuState.h"
#include "exceptionState.h"

int Game::mFps = 0;

GLfloat gWindowWidth = 0;
GLfloat gWindowHeight = 0;

/* Function:    initMainState
   Description: Helper function which starts our stack of states
                Always start on main menu state
   Parameters:  None
   Returns:     None
 */
void Game::initMainState()
{
  //mStates.push(std::make_shared<ExceptionState>(mStates, "TESTING", mShaders[MAIN_SHADER], mpWindow->getGlWindow(), mpVao));
  mStates.push(std::make_shared<MainMenu>(mStates, mpBatchBuffer));
}

/* Function:    Game
   Description: Initializes core components for the game
   Parameters:  None
   Returns:     None
 */
Game::Game()
{
  mpWindow = std::make_shared<RenderWindow>(1920, 1080, "Lest Window");   
  /* NOTE: BEFORE ANY GL CALL, THAT IS NOT GLFW but GL, SET ACTIVE MUST BE CALLED OR ELSE OPENGL FAILS */
  mpWindow->setActive();

  //init GL attributes for window
  mpWindow->initWindow();
  mpWindow->enableBlend();

  int32_t view[4] = {};
  glGetIntegerv(GL_VIEWPORT, view);
  std::cout << view[0] << " " << view[1] << " " << view[2] << " " << view[3] << std::endl;
  VertexBufferLayout temp;
  // First set of Float are quad position
  temp.push(TWO_D_COORDS, GL_FLOAT, true);
  // Next 4 bytes are RGBA
  temp.push(RGBA, GL_UNSIGNED_BYTE, true);
  // Next 2 floats are Texture Coords
  temp.push(TWO_D_COORDS, GL_FLOAT, false);
  temp.push(1, GL_FLOAT, false);
  mpBatchBuffer = std::make_shared<BatchBuffer>(1, 1, 1, 1, 32);
  mpBatchBuffer->bindVbo(0);
  mpBatchBuffer->bindVao(0);
  mpBatchBuffer->bindIbo(0);
  mpBatchBuffer->genVboBuffer(0, 300, GL_DYNAMIC_DRAW);
  mpBatchBuffer->genIboBuffer(0, 300, GL_STATIC_DRAW);
  mpBatchBuffer->initShader(0, "lol");
  mpBatchBuffer->bindShader(0);
  mpBatchBuffer->setVaoAttributes(0, temp);
  //init textures


  //temp
  gWindowWidth = 1920;
  gWindowHeight = 1080;
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
  mStartTime = time(nullptr);

}

/* Function:    ~Game
   Description: Cleans up all allocated memory
   Parameters:  None
   Returns:     None
 */
Game::~Game()
{
  while(!mStates.empty()) {
    mStates.pop();
  }

  mpBatchBuffer.reset();
  mpWindow->destroyWindow();
  glfwTerminate();
}

/* Function:    gameLoop
   Description: Runs gameloop until window has been closed
   Parameters:  None
   Returns:     None
 */
void Game::gameLoop() {
  while(!mStates.empty() && mpWindow->isOpen()) {
    if (mStates.top()->shouldStateExit()) {
      mStates.pop();
    }
    
    GLCall(glfwPollEvents());
    mStates.top()->update(mpWindow);
    mStates.top()->render(mpWindow);
    Game::mFps ++;
    mEndTime = time(nullptr);
    if ((mEndTime - mStartTime) > 0) {
      std::cout << "FPS: " << Game::mFps / (mEndTime - mStartTime) << std::endl;
      mFps = 0;
      mStartTime = mEndTime;
    }
  }

  gameEnd();
}

/* Function:    gameEnd
   Description: Handles how application should act when game is closed
   Parameters:  None
   Returns:     None
 */
void Game::gameEnd()
{
}