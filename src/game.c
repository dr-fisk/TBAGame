#include "game.h"

int Game::fps = 0;

GLfloat gWindowWidth = 0;
GLfloat gWindowHeight = 0;

/* Function:    initMainState
   Description: Helper function which starts our stack of states
                Always start on main menu state
   Parameters:  None
   Returns:     None
 */
void Game::initMainState() {
  states.push(std::make_shared<MainMenu>(window, states));
}

/* Function:    Game
   Description: Initializes core components for the game
   Parameters:  None
   Returns:     None
 */
Game::Game() {
  window = std::make_shared<RenderWindow>(800, 800, "Lest Window");

  //temp
  gWindowWidth = 800;
  gWindowHeight = 800;
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
  std::vector<Drawable*> vertexes;
 // std::vector<Drawable *> vert;
  this->gameRuntime = time(nullptr);
  this->startTime = time(nullptr);
  // Make this mesh shit easier so that all you call is just batchbuffer constructor and give it some data
  //mesh = Mesh("../src/heart.png", 0, 0, 1);
  //mesh2 = Mesh("../src/heart.png", 16,0,1);
  font = Font("../src/fonts/Font.png");
  text = Text("TEST", font);
  vertexes.push_back(&text);
  //vertexes.push_back(&mesh);
  //vertexes.push_back(&mesh2);
 // vertexes.insert(vertexes.end(), vert.begin(), vert.end());
  testBB = BatchBuffer(vertexes, RECTANGLE);
}

/* Function:    ~Game
   Description: Cleans up all allocated memory
   Parameters:  None
   Returns:     None
 */
Game::~Game() {
  while(!states.empty()) {
    states.pop();
  }
}

/* TODO: Remove temp parameters for development */
/* TODO: Remove rects, this is development testing at the moment */
/* Function:    render
   Description: Renders window
   Parameters:  None
   Returns:     None
 */
void Game::render(const std::shared_ptr<RenderTarget> &target) {
  /*Rect test;
  test = Rect(0, 0, 100, 100);
  test.setColor(lg::Blue);
  Rect test2(800, 800, 100, 100);
  test2.setColor(lg::Pink);
  Rect test3(800, 0, 100, 100);
  test3.setColor(lg::Purple);
  Rect test4(0, 800, 100, 100);
  test4.setColor(lg::Yellow);
  Rect test5(100, 100, 10, 10);
  test5.setColor(lg::Green);
  Rect test6(100, 200, 10, 10);
  test6.setColor(lg::White);
  Rect test7(400, 300, 5, 5);
  test7.setColor(lg::Orange);
  vertexes.push_back(target->createRectVertexDataBounded(test));
  vertexes.push_back(target->createRectVertexDataBounded(test2));
  vertexes.push_back(target->createRectVertexDataBounded(test3));
  vertexes.push_back(target->createRectVertexDataBounded(test4));
  vertexes.push_back(target->createRectVertexDataBounded(test5));
  vertexes.push_back(target->createRectVertexDataBounded(test6));
  vertexes.push_back(target->createRectVertexDataBounded(test7)); */
  target->clear();
  testBB.render(target);
  //target->draw(test);
  target->display();
}

/* Function:    gameLoop
   Description: Runs gameloop until window has been closed
   Parameters:  None
   Returns:     None
 */
void Game::gameLoop() {
  while(window->isOpen()) {
    if (states.empty())
      break;

    render(window);
    //update data
    //render
    Game::fps ++;
    endTime = time(nullptr);
    if ((endTime - startTime) > 0) {
      std::cout << "FPS: " << Game::fps / (endTime - startTime) << std::endl;
      fps = 0;
      startTime = endTime;
    }
  }

  gameEnd();
}

/* Function:    gameEnd
   Description: Handles how application should act when game is closed
   Parameters:  None
   Returns:     None
 */
void Game::gameEnd() {
}