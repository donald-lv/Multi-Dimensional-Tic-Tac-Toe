// A game of n dimensional tic-tac-toe of any board width

#include <stdio.h>

#include "vector.h"
#include "board.h"

const int DEFAULT_WIDTH = 4;
const int DEFAULT_DIM = 3;

// tutorial prints instructions on how to play the game
// effects: outputs instructions
void tutorial() {
  // create a test board

  printf("this is TTT in n dimensions, of varying size\n");
  printf("a player wins by filling a straight diagonal in any dimension\n");
  printf("ex.\n");
  
  // fill the board properly, print it
  struct board *tut_board = board_create(4, 3);
  

  printf("\n");
  printf("coordinates start at 0 and end at width - 1\n");
  printf("For example: \n");
}