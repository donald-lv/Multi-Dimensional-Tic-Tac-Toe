// A game of n dimensional tic-tac-toe of any board width

#include <stdio.h>

#include "vector.h"
#include "board.h"

// tutorial prints instructions on how to play the game
// effects: outputs instructions
void tutorial() {
  // create a test board

  printf("this is TTT in n dimensions, of varying size\n");
  printf("a player wins by filling a straight diagonal in any dimension\n");
  printf("ex.\n");
  
  // fill the board properly, print it
  struct board *tut_board = board_create();
  

  printf("\n");
  printf("coordinates start at 0 and end at size - 1\n");
  printf("coordinates \n");
}