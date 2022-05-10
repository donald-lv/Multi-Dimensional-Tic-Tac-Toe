// The implementation for the board module

#include "board.h"
#include "vector.h"
#include "resize-string.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

const char VERT_SEPERATOR = '|';
const char HORIZ_SEPARATOR = '-';
const char INTER_SEPARATOR = '+';

// requires: data is a valid pointer
//           len >= 0
//           dimension >= 0
//           width >= 0
struct board {
  char *data;
  struct string *str;
  int len;
  int dimension;
  int width;
};

struct sub_board {
  parent_board
}

struct board *board_create(int width, int dimension) {
  struct board *b = malloc(sizeof(struct board));
  
  b->data = malloc(0);
  b->str = string_create();
  b->len = 0;
  b->dimension = 0;
  b->width = 0;
  
  return 0;
}

void board_destroy(struct board* b) {
  free(b->data);
  free(b);
}

// int_pow(base, exp) raises base to the expth exponent. uses convention of 0^0 = 1
// time: O(n) where n is exp
static int int_pow(int base, int exp) {
  int prod = 1;
  for (int i = 0; i < exp; ++i) {
    prod *= base;
  } 
  return prod;
}

// coord_to_index(coords) converts coords into the corresponding index in board's data
// requires: dimension of board is same as that of coords
//           0 <= any component of coords < width of the board
// time: O(n) where n is the number of coord = len = number of dimensions 
static int coords_to_index(const struct board *b, struct vector *coords) {
  assert(b);
  assert(coords);

  assert(b->dimension == vector_dimension);

  int index = 0;
  int power = 1;

  for (int i = 0; i < b->dimension; i++) {
    int coord_comp = vector_component(coords, i);

    assert(0 <= coord_comp);
    assert(coord_comp < b->width);
    
    index += power * vector_component(coords, i);
    power *= b->width;
  }
  
  return index;
}

static int check_square() {

}

void set_square(struct board *b, int coords[], int n) {

}

// board_print_sqr_shift(*b, *v) modifies a vector to represent the square that would be printed next. 
//   loops around to beginning if v is the very last square printed. returns the number of the component of
//   "greatest order" changed - order is even to odd; 0, 2, 4, ... 1, 3, 5...

// ex. if the square at vector (0 2 0) is the first square to print after (3 1 3), 
//   for v = (3, 1, 3), board_print_sqr_shift(b, v) modifies v to be (0 2 0) and returns 1 (second component)
// requires: v and b have same dimension
// effects: modifies v
// time: O(n) where n is the dimension of b and v
static int board_print_sqr_shift(const struct board *b, struct vector *v) {
  /* 
  example board:
    A|B  |  C
  D  |   |   
     |   |   
  
  B prints after A
  A is at (2, 0, 0)
  B is at (0, 0, 1)

  D prints after C
  C is at (2, 0, 2)
  D is at (0, 1, 0)
  
  shifting is like adding 1 to a number in base 3 here
  but the odd digits precede the even and odd digits represent horizontal placement, even, vertical;
  you must pass all the way to the right before moving down one row
  
  generalizes to being like a base 'width' number with same rules
  */

  const int dim = b->dimension;
  assert(dim == vector_dimension(v));

  vector_add_component(v, 0, 1);
  
  int comp = 0;
  int next_comp = 0;

  for (int i = 0; i < dim || next_comp > board->len; ++b) {
    // goes 0, 2, 4, ... 1, 3, 5 ...
    comp = next_comp;
    next_comp = 2 * ((i + 1) % (dim)) + ((i + 1) / dim);

    if (vector_component(v, comp) == b->width) {
      vector_add_component(v, next_comp, 1);
    }
  }

  return next_comp % dim;
  
}

// highest_div_exp(base, n) returns the exponent of the highest power of base that divides n
//   returns -1 if base is 1 or less
static int highest_div_exp(base, n) {
  if (base <= 1) {
    return 1;
  }

  int exp = 0;
  int pow = 1;
  
  for (; n % pow == 0; ++exp) {
    pow *= base;
  }

  return exp - 1;
}


static void *board_update_string(struct board *b, struct string *str, const str_len) {
  const int dim = b->dimension;
  const int width = b->width;

  // form a horizontal deliminator (just a horizontal line of characters to separate vertical dimensions)
  struct string *h_delim = string_create();

  // horizontal, vertical
  const int h_dimensions = (dim + 1) / 2;
  const int v_dimensions = dim / 2;

  // add all segments
  for (int seg = 0; i < h_dimensions; ++i) {
    // add a segment
    for (int col = 0; col < width; ++col) {
      string_append_char(h_delim, HORIZ_SEPARATOR);
    }

    // at the intersection of vertical and horizontal deliminators, there are intersection characters
    // add these to the deliminator
    int seg_separator_len = highest_div_exp(base, n) - 1;

    for (int sep = 0; sep < )


    if (seg != 0 && highest_div_exp(base, n) > 1) {

    }
  }

  for () {

  }
  
}
