// a test client for board.c: use CLAs to print an empty board of that size
//   usage ./file.out width dimension

#include "board.h"
#include "resize-string.h"
#include <stdlib.h>

#include <stdio.h>

int main(int argc, char *argv[]) {
  // input is width, dimension
  if (argc != 3) {
    printf("usage is: %s width dimension", argv[0]);
    return 1;
  }
  
  int width = atoi(argv[1]);
  int dimension = atoi(argv[2]);

  printf("w, d: %d, %d \n", width, dimension);

  struct board *b = board_create(width, dimension);
  board_print(b);

  return 0;
}