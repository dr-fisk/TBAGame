#include "game.h"

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
  window = std::make_shared<RenderWindow>(800, 800, "Test");
  initMainState();
  
  /* vbo holds vertex data (cooridnates and RGB color)
     You can combine both in one vbo or separate vbo, if
     combining you must specify which are coords and which
     are rgb, vao is like a file descriptor table but for a vertex
     and holds vbo's */

    /* I probably need a class to handle texture data for VBO's and stuff*/

  this->gameRuntime = clock();
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
  std::vector<RectVertices> vertexes;
  VertexBufferLayout layout;
  Rect test(0, 0, 100, 100);
  /* Need to update code to handle multiple renders */
  Rect test2(800, 800, 100, 100);
  Rect test3(800, 0, 100, 100);
  Rect test4(0, 800, 100, 100);
  Rect test5(100, 100, 10, 10);
  Rect test6(100, 200, 10, 10);
  Rect test7(400, 300, 5, 5);
  vertexes.push_back(target->createRectVertices(test));
  vertexes.push_back(target->createRectVertices(test2));
  vertexes.push_back(target->createRectVertices(test3));
  vertexes.push_back(target->createRectVertices(test4));
  vertexes.push_back(target->createRectVertices(test5));
  vertexes.push_back(target->createRectVertices(test6));
  vertexes.push_back(target->createRectVertices(test7));
  BatchBuffer testBB(vertexes, RECTANGLE);

 // All these calls will eventually be abstracted
  target->clear();
  testBB.render(target);
  //target->draw(vbo, layout);
  //target->draw(test);
  //target->draw(test2);
  //target->draw(test3);
  //target->draw(test4);
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