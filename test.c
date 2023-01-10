// a test client for board.c: use CLAs to print an empty board of that size
//   usage ./file.out width dimension

#include "board.h"
#include "vector.h"
#include "text-commands.h"
#include "tictactoe.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// board_squares_test_recurse(b, v, comp, c) sets the square in b at all permutations of components of place greater 
//   than comp to cycling characters
static void board_squares_test_recurse(struct board *b, struct vector *v, int comp, char *c) {
  const int dimension = board_dimension(b);
  assert(dimension == vector_dimension(v));
  
  int width = board_width(b);
  
  if (comp < 0) {
    board_set_square(b, v, *c);
    *c = ((*c - 'a' + 1) % ('z' - 'a' + 1)) + 'a';
  } else {
    for (int i = 0; i < width; ++i) {
      vector_set_component(v, comp, i);
      board_squares_test_recurse(b, v, comp - 1, c);
    }
  }
}

// board_squares_test(b) changes squares of b to be the alphabet in ascending and cycling order as the square number
//   increases. square number is the vector's components as digits, making a number in base baord_width(b)
static void board_squares_test(struct board *b) {
  struct vector *v = vector_create(board_dimension(b));
  vector_zero(v);
  char c = 'a';

  board_squares_test_recurse(b, v, board_dimension(b) - 1, &c);
  vector_destroy(v);

  board_print(b);
  printf("\n");
}

int main(void) {
  const long enter = command_to_long("enter");
  const long result = command_to_long("result");
  const long test = command_to_long("test");
  const long line = command_to_long("line");
  const long print = command_to_long("print");
  
  int width = 0;
  int dimension = 0;

  scanf("%d", &width);
  scanf("%d", &dimension);

  struct board *b = board_create(width, dimension);
  board_overwrite(b, ' ');

  struct vector *v = vector_create(dimension);
  struct vector *dir = vector_create(dimension);

  int scan_result = 1;
  char c = '\0';
  long command = 0;

  while (true) {
    command = command_read();

    if (command == QUIT_SYMBOL) {
      break;
    }

    if (command == enter) {
      scan_result = vector_read(v);
      if (scan_result == 1) {
        board_set_square(b, v, 'X');
      } else {
        break;
      }

    } else if (command == result) {
      scan_result = vector_read(v);
      if (scan_result == 1) {
        char r = board_check_square(b, v);
        if (r != '\0') {
          printf("win\n");
        } else {
          printf("no win\n");
        }
      } else {
        break;
      }

    } else if (command == test) {
      board_squares_test(b);
      
    } else if (command == line) {
      scan_result = vector_read(v);
      if (scan_result == 1) {
        scan_result = vector_read(dir);

        if (scan_result == 1) {
          bool r = board_check_line(b, v, dir);
          if (r) {
            printf("line\n");
          } else {
            printf("no line\n");
          }
        }
      }

    } else if (command == print) {
      board_print(b);
      printf("\n");

    }

    if (scan_result != 1) {
      break;
    }
  }

  vector_destroy(v);
  board_destroy(b);

  return 0;
}
