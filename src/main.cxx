#include "game.h"

/* Function:    main
   Description: Starts application and calls main loop
   Parameters:  None
   Returns:     None 
 */
int main() {
  Game game = Game();

  game.gameLoop();
  
  return 0;
}