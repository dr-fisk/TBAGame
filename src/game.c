#include "game.h"

void Game::initMainState() {
  states.push(new MainMenu(window, states));
}

Game::Game() {
  window = new RenderWindow(800, 800, "Test");
  initMainState();
  
  /* vbo holds vertex data (cooridnates and RGB color)
     You can combine both in one vbo or separate vbo, if
     combining you must specify which are coords and which
     are rgb, vao is like a file descriptor table but for a vertex
     and holds vbo's */

    /* I probably need a class to handle texture data for VBO's and stuff*/

  this->gameRuntime = clock();
}

Game::~Game() {
  if (window)
    delete window;

  while(!states.empty()) {
    if (states.top())
      delete states.top();

    states.pop();
  }
}

/* Temp parameters for development */
/* Remove rects, this is development testing at the moment */
void Game::render(RenderTarget *target) {
  //Rect test(0, 0, 100, 100);
  /* Need to update code to handle multiple renders */
  //Rect test2(600, 600, 100, 100);

  window->clear();
  window->render();
  //target->draw(test);
  //target->draw(test2);
  window->display();
}

/* Runs the main game loop which only exits when
either window is closed or state stack is empty */
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

void Game::gameEnd() {

}