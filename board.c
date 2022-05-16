// The implementation for the board module
// See interface for documentation

#include "board.h"
#include "vector.h"
#include "resize-string.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const char VERT_SEPARATOR = '|';
const char HORIZ_SEPARATOR = '-';
const char INTER_SEPARATOR = '+';

// requires: data is a valid pointer
//           len >= 0
//           dimension >= 0
//           width >= 0
struct board {
  char *data;
  struct string *str;
  bool str_updated;
  int len;
  int dimension;
  int width;
};

// int_pow(base, exp) raises base to the expth exponent for nonnegative base. 
//   uses convention of 0^0 = 1.
// requires: base >= 0
// time: O(n) where n is exp
static int int_pow(int base, int exp) {
  assert(base >= 0);
  int prod = 1;
  for (int i = 0; i < exp; ++i) {
    prod *= base;
  } 
  return prod;
}

void board_wrap_vector_add(const struct board *b, struct vector *square, const struct vector *direction) {
  assert(b);
  assert(square);
  assert(direction);
  
  int dimension = b->dimension;
  assert(dimension == vector_dimension(square));
  assert(dimension == vector_dimension(direction));

  int width = b->width;

  vector_add(square, direction);

  for (int i = 0; i < dimension; ++i) {
    vector_set_component(square, i, (vector_component(square, i) + width) % width);
  }
}

// board_coords_to_index(b, coords) converts coords into the corresponding index in board's data
// requires: dimension of board is same as that of coords
//           0 <= any component of coords < width of the board
// time: O(n) where n is the number of coord = len = number of dimensions 
static int board_coords_to_index(const struct board *b, const struct vector *coords) {
  assert(b);
  assert(coords);
  assert(b->dimension == vector_dimension(coords));

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

char board_at_coord(const struct board *b, const struct vector *coords) {
  assert(b);
  assert(coords);
  assert(b->dimension == vector_dimension(coords));
  return b->data[board_coords_to_index(b, coords)];
}

void board_set_square(struct board *b, const struct vector *coords, char c) {
  assert(b);
  assert(coords);
  assert(b->dimension == vector_dimension(coords));

  b->data[board_coords_to_index(b, coords)] = c;
  b->str_updated = false;
}

void board_size_change(struct board *b, int width, int dimension) {
  assert(b);
  assert(width >= 0);
  assert(dimension >= 0);

  b->width = width;
  b->dimension = dimension;
  b->len = int_pow(width, dimension);
  b->data = realloc(b->data, b->len * sizeof(char));
  b->str_updated = false;
}

void board_overwrite(struct board *b, char c) {
  assert(b);

  for (char *i = b->data; i < b->data + b->len; ++i) {
    *i = c;
  }

  b->str_updated = false;
}

// board_print_sqr_shift(*b, *v) modifies a vector to represent the square that would be printed next. 
//   loops around to beginning if v is the very last square printed.
//     ex. if the square at vector (0 2 0) is the first square to print after (3 1 3), for 
//         v = (3, 1, 3), board_print_sqr_shift(b, v) modifies v to be (0 2 0)
// requires: v and b have same dimension
// effects: modifies v
// time: O(n) where n is the dimension of b and v
static void board_print_sqr_shift(const struct board *b, struct vector *v) {
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
  
  assert(b);

  const int dim = b->dimension;
  assert(dim == vector_dimension(v));

  const int h_dim = (dim + 1) / 2;
  
  vector_add_component(v, 0, 1);
  
  int comp = 0;
  int next_comp = 0;

  for (int i = 0; i < dim; ++i) {
    
    comp = next_comp;
    // goes 0, 2, 4, ... 1, 3, 5 ... 0, 2, 4, ...
    if (((i + 1) % dim) < h_dim) {
      next_comp = 2 * ((i + 1) % dim);
    } else {
      next_comp = 2 * (((i + 1) % dim) - h_dim) + 1;
    }
    
    // could use % and / to do shift by n
    if (vector_component(v, comp) == b->width) {
      vector_set_component(v, comp, 0);
      
      if (next_comp != 0) {
        vector_add_component(v, next_comp, 1);
      }
    }
  }
}

// highest_div_exp(base, n) returns the exponent of the highest power of base that divides n
//   returns 0 if base is 1 or less or if n is 0
static int highest_div_exp(int base, int n) {
  if (base <= 1 || n == 0) {
    return 0;
  }

  int exp = 0;
  int pow = 1;
  
  for (; n % pow == 0; ++exp) {
    pow *= base;
  }

  return exp - 1;
}

// board_update_string(b) updates b's string to reflect its data
// effects: updates b's string
// time: i dont know
static void board_update_string(struct board *b) {
  assert(b);

  // prevent repeat updates costing more
  if (b->str_updated) {
    return;
  }

  // reset b->str
  string_destroy(b->str);
  b->str = string_create();

  const int dim = b->dimension;
  const int width = b->width;

  // case that b's width is 1 or 0; special cases
  switch (width) {
    case 0:
      string_append_char(b->str, '\n');
      return;
    case 1:
      string_append_char(b->str, b->data[0]);
      string_append_char(b->str, '\n');
      return;
  }

  // otherwise, dynamically build the board
  /*
  example 5d 2 wide board;
  X |  ||  | E
   O|  || A|  
  --+--++--+--
    |  ||  |D 
    | V||  | C

  0- 1-  2- 3-  <-- segments

  horizontal dimension means squares further along the dimension appear further left
  vertical means further squares appear further down
  segment means any section of undeliminated squares; this board is 4 horiz. segments, 2 vert. segments
  */

  // horizontal, vertical count of dimensions, count of split segments
  const int h_dimensions = (dim + 1) / 2;
  const int h_segments = int_pow(width, h_dimensions - 1);

  const int v_dimensions = dim / 2;
  const int v_segments = int_pow(width, v_dimensions - 1);


  // form a horizontal deliminator (just a horizontal line of characters to separate vertical dimensions)
  struct string *h_delim = string_create();

  for (int seg = 0; seg < h_segments;) {
    // add a segment
    for (int col = 0; col < width; ++col) {
      string_append_char(h_delim, HORIZ_SEPARATOR);
    }

    ++seg;

    if (seg < h_segments) {
      // at the intersection of vertical and horizontal deliminators, there are intersection characters
      // add these to the deliminator
      int seg_sep_len = highest_div_exp(width, seg) + 1;

      for (int sep = 0; sep < seg_sep_len; ++sep) {
        string_append_char(h_delim, INTER_SEPARATOR);
      }
    }
  }
  
  string_append_char(h_delim, '\n');
  
  // form the board
  struct vector *square = vector_create(dim);
  vector_zero(square);

  // vertical segment by vertical segment
  for (int v_seg = 0; v_seg < v_segments;) {
    // make vertical segment
    for (int row = 0; row < width; ++row) {
      
      // horizontal segment by horizontal segment
      for (int h_seg = 0; h_seg < h_segments;) {
        // make one line; similar to horiz. delim code
        // make horizontal segment
        for (int col = 0; col < width; ++col) {
          string_append_char(b->str, board_at_coord(b, square));
          board_print_sqr_shift(b, square);
        }

        ++h_seg;

        if (h_seg < h_segments) {
          // add vertical deliminators to line 
          int h_seg_sep_len = highest_div_exp(width, h_seg) + 1;

          for (int sep = 0; sep < h_seg_sep_len; ++sep) {
            string_append_char(b->str, VERT_SEPARATOR);
          }
        }
      }

      string_append_char(b->str, '\n');
    }

    ++v_seg;

    if (v_seg < v_segments) {
      // add vertical deliminators to line 
      int v_seg_sep_len = highest_div_exp(width, v_seg) + 1;

      for (int sep = 0; sep < v_seg_sep_len; ++sep) {
        string_append_string(b->str, h_delim);
      }
    }
  }

  string_destroy(h_delim);
  vector_destroy(square);

  b->str_updated = true;
}

void board_print(struct board *b) {
  board_update_string(b);
  string_print(b->str);
}

int board_dimension(const struct board *b) {
  return b->dimension;
}

int board_width(const struct board *b) {
  return b->width;
}

struct board *board_create(int width, int dimension) {
  assert(width >= 0);
  assert(dimension >= 0);

  struct board *b = malloc(sizeof(struct board));
  
  b->len = int_pow(width, dimension);
  b->dimension = dimension;
  b->width = width;
  b->data = malloc(b->len * sizeof(char));
  b->str = string_create();
  b->str_updated = false;
  
  return b;
}

void board_destroy(struct board* b) {
  string_destroy(b->str);
  free(b->data);
  free(b);
}