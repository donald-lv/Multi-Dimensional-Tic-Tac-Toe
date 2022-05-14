
#include "board.h"
#include "vector.h"
#include "tictactoe.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  // input is width, dimension
  if (argc != 3) {
    printf("usage is: %s width dimension\n", argv[0]);
    return 1;
  }

  int width = atoi(argv[1]);
  int dimension = atoi(argv[2]);

  struct board *b = board_create(width, dimension);

  int result = 1;
  struct vector *v = vector_create(dimension);
  char c = '\0';

  while (result == 1) {
    result = vector_read(v);
    if (result == 1) {
      result = scanf(' %c', &c);
      if (result == 1) {
        
      }
    }
  }

  return 0;
}

