// a test client for board.c: use CLAs to print an empty board of that size
//   usage ./file.out width dimension

#include "board.h"
#include "resize-string.h"
#include <stdlib.h>

#include <stdio.h>

// board_squares_test_recurse(b, v, comp, c) sets the square in b at all permutations of components of place greater 
//   than comp to cycling characters
static void board_squares_test_recurse(struct board *b, struct vector *v, int comp, char *c) {
  int dim = board_dimension(b);
  assert(dim == vector_dimension(v));
  
  int width = board_width(b);
  
  if (comp >= dim) {
    board_set_square(b, v, *c);
    *c = ((*c - 'a' + 1) % ('z' - 'a' + 1)) + 'a';
  } else {
    for (int i = 0; i < width; ++i) {
      vector_set_component(v, comp, i);
      board_squares_test_recurse(b, v, comp + 1, c);
    }
  }
}

static void board_squares_test(struct board *b) {
  struct vector *v = vector_create(board_dimension(b));
  vector_zero(v);
  char c = 'a';

  board_squares_test_recurse(b, v, 0, &c);
  vector_destroy(v);

  board_print(b);
}

int main(int argc, char *argv[]) {
  // input is width, dimension
  if (argc != 3) {
    printf("usage is: %s width dimension\n", argv[0]);
    return 1;
  }
  
  int width = atoi(argv[1]);
  int dimension = atoi(argv[2]);

  printf("w, d: %d, %d \n", width, dimension);

  struct board *b = board_create(width, dimension);
  board_print(b);

  board_squares_test(b);

  board_destroy(b);

  return 0;
}