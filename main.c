// A game of n dimensional tic-tac-toe of any board width

#include "vector.h"
#include "board.h"

#include <stdio.h>

const int DEFAULT_WIDTH = 4;
const int DEFAULT_DIM = 3;
const char PLAYER_TOKENS[] = {'X', 'O', 'H', '8'};

// tutorial() prints instructions on how to play the game
// effects: outputs instructions
// time: O(1)
static void tutorial();

int main(int argc, char *argv[]) {
  tutorial();
}

static void tutorial() {
  // create a test board
  const int tutorial_width = 3;
  const int tutorial_dimension = 3;

  struct board *tut_board = board_create(tutorial_width, tutorial_dimension);
  struct vector *square = vector_create(tutorial_dimension);

  board_overwrite(tut_board, ' ');

  // intro
  printf("\nTUTORIAL\n");
  printf("This is tic-tac-toe in varying dimensions, of varying size.\n");
  printf("Here is an empty %dd board of width %d: \n\n", tutorial_dimension, tutorial_width);
  board_print(tut_board);

  // coord tut
  printf("\n---------\n");
  printf("Coordinates start at 0 and end at width - 1. \n");
  printf("For example, this X is the point with coordinates 1 2 0 for the same board: \n\n");
  
  vector_set(square, (int[3]){1, 2, 0});
  board_set_square(tut_board, square, 'X');
  board_print(tut_board);

  printf("and this O is the point with coordinates 1 2 2: \n\n");

  vector_set(square, (int[3]){1, 2, 2});
  board_set_square(tut_board, square, 'O');
  board_print(tut_board);

  // victory tut
  board_overwrite(tut_board, ' ');
  
  printf("\n---------\n");
  printf("A player wins by filling a straight diagonal in any dimension. \n");
  printf("For example, here are some ways to win: \n\n");
  
  vector_set(square, (int[3]){0, 2, 1});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){1, 2, 1});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){2, 2, 1});
  board_set_square(tut_board, square, 'X');

  board_print(tut_board);
  printf("A diagonal across 1 dimension \n\n");

  board_overwrite(tut_board, ' ');

  vector_set(square, (int[3]){0, 2, 2});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){1, 1, 2});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){2, 0, 2});
  board_set_square(tut_board, square, 'X');

  board_print(tut_board);
  printf("A diagonal across 2 dimensions \n\n");

  board_overwrite(tut_board, ' ');

  vector_set(square, (int[3]){0, 2, 0});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){1, 2, 1});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){2, 2, 2});
  board_set_square(tut_board, square, 'X');

  board_print(tut_board);
  printf("A diagonal across 2 dimensions \n\n");

  board_overwrite(tut_board, ' ');

  vector_set(square, (int[3]){0, 2, 0});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){1, 1, 1});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){2, 0, 2});
  board_set_square(tut_board, square, 'X');

  board_print(tut_board);
  printf("A diagonal across 3 dimensions \n\n");

  printf("Have Fun!");
}

// run_turn(b, player_token) runs a player's turn given their char, returns the status of the turn
// 0 if the player did not win on this turn
// 1 if the player won
// -1 if the player entered invalid input
static bool run_turn(struct board *b, char player_token) {
  const int dimension = board_dimension(b);
  struct vector *v = vector_create(b);
  int scan_result = vector_read(v);

  if (scan_result == 1) {
    board_set_square(b, v, player_token);
  } else {
    return -1;
  }

  if () {

  }
}