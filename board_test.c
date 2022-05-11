// a test client for board.c

#include "board.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  // input is width, dimension
  if (argc != 3) {
    printf("usage is: %s width dimension", argv[0]);
    return 1;
  }
  
  int width = atoi(argv[0]);
  int dimension = atoi(argv[1]);

  struct board *b = board_create(width, dimension);
  board_print(b);

  return 0;
}