#include "game.h"

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

/* Function:    initShaders
   Description: Helper function which initializes and caches shaders
                CALL AFTER SETTING GL WINDOW CONTEXT AND BEFORE SETTING WINDOW SHADER
   Parameters:  None
   Returns:     None
 */
void Game::initShaders()
{
  //TODO: Add more shaders if necessary
  // mShaders[MAIN_SHADER] = std::make_shared<Shader>(MAIN_SHADER);
}

/* Function:    Game
   Description: Initializes core components for the game
   Parameters:  None
   Returns:     None
 */
Game::Game()
{
  if(!glfwInit()) {
    std::cout << "Failed to open window" << std::endl;
    exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  mpWindow = std::make_shared<RenderWindow>(1920, 1080, "Lest Window");
   
  /* NOTE: BEFORE ANY GL CALL, THAT IS NOT GLFW but GL, SET ACTIVE MUST BE CALLED OR ELSE OPENGL FAILS */
  mpWindow->setActive();

  /* initShaders comes after set Active as it contains GL calls*/
  // initShaders();

  // Set the shader to be attached to the window
  // mpWindow->setShader(mShaders[MAIN_SHADER]);

  //TODO: update to be more dynamic
 // mpWindow->setVao(mpVao);

  //init GL attributes for window
  mpWindow->initWindow();

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
  mpBatchBuffer = std::make_shared<BatchBuffer>(1, 1, 1, 1);
  // TODO Cleanup
  std::cout << "Binding vbo" << std::endl;
  mpBatchBuffer->bindVbo(0);
  std::cout << "Done. Binding vao" << std::endl;

  mpBatchBuffer->bindVao(0);
  std::cout << "Done. Binding ibo" << std::endl;

  mpBatchBuffer->bindIbo(0);
  std::cout << "Done. Generating Vbo Buff" << std::endl;

  mpBatchBuffer->genVboBuffer(0, BYTES_IN_MB * 300, GL_DYNAMIC_DRAW);
  std::cout << "Done. Generating Ibo Buff." << std::endl;

  mpBatchBuffer->genIboBuffer(0, BYTES_IN_MB * 300 / sizeof(RenderData) * 6, GL_DYNAMIC_DRAW);
  std::cout << "Done. InitShader." << std::endl;

  mpBatchBuffer->initShader(0, "lol");
  std::cout << "Done. Binding Shader" << std::endl;

  mpBatchBuffer->bindShader(0);
  std::cout << "Done. Setting Vao Attrib" << std::endl;

  mpBatchBuffer->setVaoAttributes(0, temp);
  std::cout << "Done" << std::endl;


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

  deleteShaders();
  mpBatchBuffer.reset();
  mpWindow->destroyWindow();
  glfwTerminate();
}

/* Function:    deleteShaders
   Description: Helper function which deletes the cached shaders
   Parameters:  None
   Returns:     None
 */
void Game::deleteShaders()
{
  for(std::map<std::string, std::shared_ptr<Shader>>::iterator it = mShaders.begin(); it != mShaders.end(); it++) {
    it->second.reset();
  }
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
    mStates.top()->update();
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