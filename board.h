// The interface for the board module
//   Prodivdes board ADT, a rectilinear grid with sides of same length in n dimensions
//   ex. width 3 dimension 2 is 3 x 3
//       width 2 dimension 5 is 5 x 5 x 5 x 5 x 5
//       width 10 dimension 10 is 10 x 10 x 10 x 10 x 10 x 10 x 10 x 10 x 10 x 10 

// All pointer arguments must be valid pointers
// All non-const pointer arguments must be pointers to heap

#include "vector.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct board;

// board_create() creates a board and returns its address
// effects: allocates memory for a board and its data
// time: O(1)
struct board *board_create(void);

// board_destroy(b) frees the memory for b and its data
// requires: b is a valid pointer
// effects: frees b and its data
// time: O(1)
void board_destroy(struct board* b);

// board_set_square(b, coords) changes the value at the coords to 
// requires: b is a valid pointer
//           dimension of board = dimension of coords
//           all coords' values are between 0 and size - 1
// effects: changes board's data at the coords square to c
// time: O(1)
bool board_set_square(struct board *b, struct vector *coords, char c);

// board_change(b, width, dimensions) resizes a board b to have sides of length width in dimension dimensions
// requires: b is a pointer to heap
//           dimension >= 0
//           width >= 0
// effects: reallocates memory to fit new board dimensions and size
// time: O(m) where m = size^m
void board_change(struct board *b, int width, int dimension);

// overwrite_board(b, c) writes over board to contain only the character c
// requires: b is a valid pointer
// effects: mutates b to only contain c
// time: O(n) where n is the total number of squares of the board
void board_overwrite(struct board *b, char c);

// board_to_string(b) prints the board
// requries: b is a valid pointer to a board on heap
//           str is a valid pointer to a char array on heap
// effects: prints the board
// time: O(n) where n is the total number of squares of the board
char *board_to_string(const struct board *b);