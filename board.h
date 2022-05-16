// The interface for the board module
//   Prodivdes board ADT, a rectilinear grid with sides of same length in n dimensions
//   ex. width 3 dimension 2 is 3 x 3
//       width 2 dimension 5 is 5 x 5 x 5 x 5 x 5
//       width 10 dimension 10 is 10 x 10 x 10 x 10 x 10 x 10 x 10 x 10 x 10 x 10 

// All pointer arguments must be valid pointers

#include "vector.h"
#include <stdbool.h>

struct board;

// board_wrap_vector_add(b, square, delta) adds delta to square. addition's components wrap around to remain in board
// requires: dimension of b, square, delta are same
// effects: modifies square
// time: O(n) where n is the dimension
void board_wrap_vector_add(const struct board *b, struct vector *square, const struct vector *delta);

// board_at_coord(b, coords) gives the value at the coords in the board
// requires: dimension of board is same as that of coords
//           0 <= any component of coords < width of board
// time: O(n) where n is the dimension of b and coords
char board_at_coord(const struct board *b, const struct vector *coords);

// board_set_square(b, coords, c) changes the value at the coords to c
// requires: dimension of board = dimension of coords
//           0 <= any component of coords < width of b
// effects: changes board's data at the coords square to c
// time: O(1)
void board_set_square(struct board *b, const struct vector *coords, char c);

// board_size_change(b, width, dimensions) resizes a board b to have sides of length width in dimension
//   dimensions and overwrites board to be all spaces
// requires: b is a pointer to heap
//           dimension > 0
//           width >= 0
// effects: reallocates memory to fit new board dimensions and size
// time: O(n) where n = the count of squares in board
void board_size_change(struct board *b, int width, int dimension);

// board_overwrite(b, c) writes over board to contain only the character c
// requires: b is a valid pointer
// effects: mutates b to only contain c
// time: O(n) where n is the total number of squares of the board
void board_overwrite(struct board *b, char c);

// board_print(b) prints b as a board. includes a trailing newline
// effects: updates b and prints it
//          produces output
// time: unknown
void board_print(struct board *b);

// board_dimension(const struct board *b) returns the dimension of board b
// time: O(1)
int board_dimension(const struct board *b);

// board_width(const struct board *b) returns the width of board b
// time: O(1)
int board_width(const struct board *b);

// board_create(width, dimension) creates a board of width width and dimension dimension 
//   and returns its address
// requires: dimension > 0
//           width >= 0
// effects: allocates memory for a board and its data
// time: O(1)
struct board *board_create(int width, int dimension);

// board_destroy(b) frees the memory for b and its data
// requires: b is a valid pointer
// effects: frees b and its data
// time: O(1)
void board_destroy(struct board* b);