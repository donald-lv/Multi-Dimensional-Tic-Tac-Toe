// a test client for board.c: use CLAs to print an empty board of that size
//   usage ./file.out width dimension

#include "board.h"
#include "vector.h"
#include "tictactoe.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// str_int_val(str) gives a unique number for string str
// time: O(n) where n is length of str
int str_int_val(const char *str) {
  int sum = 0;
  for (const char *c = str; *c != '\0'; ++c) {
    sum += *c;
  }
  return sum;
}

// board_squares_test_recurse(b, v, comp, c) sets the square in b at all permutations of components of place greater 
//   than comp to cycling characters
static void board_squares_test_recurse(struct board *b, struct vector *v, int comp, char *c) {
  int dim = board_dimension(b);
  assert(dim == vector_dimension(v));
  
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
  const int enter = str_int_val("enter");
  const int result = str_int_val("result");
  const int test = str_int_val("test");
  const int line = str_int_val("line");
  const int print = str_int_val("print");
  
  int width = 0;
  int dimension = 0;

  scanf("%d", &width);
  scanf("%d", &dimension);

  char command_buffer[1000] = {'\0'};

  struct board *b = board_create(width, dimension);
  board_overwrite(b, ' ');

  struct vector *v = vector_create(dimension);
  struct vector *dir = vector_create(dimension);

  int scan_result = 0;
  char c = '\0';
  bool cont = true;

  while (cont) {
    // vector_print(dir);

    int command = 0;
    scan_result = scanf("%s", command_buffer);
    
    if (scan_result == 1) {
      command = str_int_val(command_buffer);
    } else {
      command = -1;
      cont = false;
    }

    if (command == -1) {
      cont = false;
    } else if (command == enter) {
      scan_result = vector_read(v);
      if (scan_result == 1) {
        board_set_square(b, v, 'X');
      } else {
        cont = false;
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
        cont = false;
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

    } else {
      cont = false;
    }

    if (scan_result != 1) {
      cont = false;
    }
  }



  vector_destroy(v);
  board_destroy(b);

  return 0;
}