// Update to chrono
#include <ctime>

#include "game.h"
#include "states/mainMenuState.h"
#include "states/exceptionState.h"

GLfloat gWindowWidth = 0;
GLfloat gWindowHeight = 0;
uint16_t gFrames = 0;
uint16_t gFps = 0;

//! @brief Initializes Main State
//!
//! @return None
void Game::initMainState()
{
  //mStates.push(std::make_shared<ExceptionState>(mStates, "TESTING", mShaders[MAIN_SHADER], mpWindow->getGlWindow(), mpVao));
  mStates.push(std::make_shared<MainMenu>(mStates, mpRenderEngine, mpBatchBuffer));
}

//! @brief Initializes Texture Sampler via the max number of Texture Units allowed by hardware
//!
//! @return None
void Game::initTextureSampler()
{
  const int32_t NUM_TEXTURE_UNITS = mpBatchBuffer->getMaxTextureUnits();
  auto uni = mpBatchBuffer->getUniform(0, "u_Textures");
  int sampler[NUM_TEXTURE_UNITS];

  for(int i = 0; i < NUM_TEXTURE_UNITS; i ++)
  {
    sampler[i] = i;
  }

  GLCall(glUniform1iv(uni, NUM_TEXTURE_UNITS, sampler));
}

//! @brief Default Constructor
//!
//! @return Game Object
Game::Game()
{
  mpWindow = std::make_shared<RenderWindow>(1920, 1080, "Lest Window");   
  /* NOTE: BEFORE ANY GL CALL, THAT IS NOT GLFW but GL, SET ACTIVE MUST BE CALLED OR ELSE OPENGL FAILS */
  mpWindow->setActive();

  // //init GL attributes for window
  mpWindow->initWindow();
  mpWindow->enableBlend();

  int32_t view[4] = {};
  glGetIntegerv(GL_VIEWPORT, view);
  std::cout << view[0] << " " << view[1] << " " << view[2] << " " << view[3] << std::endl;
  VertexBufferLayout temp;
  // First set of Float are quad position
  temp.push(TWO_D_COORDS, GL_FLOAT, false);
  // Next 4 bytes are RGBA
  temp.push(RGBA, GL_UNSIGNED_BYTE, true);
  // Next 2 floats are Texture Coords
  temp.push(TWO_D_COORDS, GL_FLOAT, false);
  temp.push(1, GL_FLOAT, false);
  mpBatchBuffer = std::make_shared<BatchBuffer>(1, 1, 1, 1);
  mpBatchBuffer->bindVbo(0);
  mpBatchBuffer->bindVao(0);
  mpBatchBuffer->bindIbo(0);
  mpBatchBuffer->genVboBuffer(0, 300, GL_DYNAMIC_DRAW);
  mpBatchBuffer->genIboBuffer(0, 300, GL_STATIC_DRAW);
  mpBatchBuffer->initShader(0,  "./shaders/shader1.txt");
  // mpBatchBuffer->initShader(1,  "./shaders/fragShader.txt");
  mpBatchBuffer->bindShader(0);
  initTextureSampler();
  mpBatchBuffer->setVaoAttributes(0, temp);
  mpRenderEngine = std::make_shared<RenderEngine>();
  //temp
  gWindowWidth = 1920;
  gWindowHeight = 1080;
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
  mStartTime = std::chrono::steady_clock::now();

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
  mpBatchBuffer.reset();
  mpWindow->destroyWindow();
  glfwTerminate();
}

//! @brief Runs gameloop until window has been closed or states popped
//!
//! @return None
void Game::gameLoop()
{
  float deltaTime = 0.0f;
  float smoothDeltaTime = 0.0f;
  int64_t smoothUpdate = 1;
  mFrameTime = std::chrono::steady_clock::now();
  // mFbo->invalidate(Vector2<uint32_t>(gWindowWidth, gWindowHeight));
  while(!mStates.empty() && mpWindow->isOpen())
  {
    deltaTime = std::chrono::duration<float>(std::chrono::steady_clock::now() - mFrameTime).count();
    mFrameTime = std::chrono::steady_clock::now();
    smoothDeltaTime -= smoothDeltaTime / static_cast<float>(smoothUpdate);
    smoothDeltaTime += deltaTime / static_cast<float>(smoothUpdate);
    // std::cout << smoothDeltaTime << std::endl;

    if (mStates.top()->shouldStateExit())
    {
      mStates.pop();
    }
    
    
    mStates.top()->update(mpWindow, deltaTime);
    // mFbo->bind();
    mStates.top()->render(mpWindow);
    gFrames ++;
    mEndTime = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds>(mEndTime - mStartTime).count() >= 1.0f)
    {
      gFps = gFrames / std::chrono::duration_cast<std::chrono::seconds>(mEndTime - mStartTime).count();
      // std::cout << "FPS: " <<  << std::endl;
      gFrames = 0;
      mStartTime = std::chrono::steady_clock::now();
    }

    // std::cout << "Delta: " << deltaTime << std::endl;

    smoothUpdate ++;
    if (smoothUpdate == 0)
    {
      smoothUpdate = 1;
    }
  }

  gameEnd();
}

//! @brief Handles how application should act when game is closed
//!
//! @return None
void Game::gameEnd()
{
}