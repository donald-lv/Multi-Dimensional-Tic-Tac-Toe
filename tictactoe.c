// The implementation for the tictactoe module

#include "board.h"
#include "vector.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

/*
terminology: a direction is a vector whose components are each one of 1, 0 or 1
             consider a board of width w and any dimension
             an extreme component for this board is either 0 or width - 1

             consider a direction d. suppose d has at least n >= 1 nonzero components.
             let s be a square which has extreme components where d has nonzero components
             ex.
             n = 1
             d = (1, 0, -1)
             then an example s is
             s = (4, 0, 0)

             a diagonal is a series of squares in a direction d that pass through any such s for d
*/

bool board_check_line(const struct board *b, const struct vector *square, const struct vector *direction) {
  assert(b);
  assert(square);
  assert(direction);
  const int dimension = board_dimension(b);
  assert(dimension == vector_dimension(square));
  assert(dimension == vector_dimension(direction));
  
  int width = board_width(b);
  char c = board_at_coord(b, square);

  struct vector *check_sqr = vector_create(dimension);
  vector_copy(check_sqr, square);
  board_wrap_vector_add(b, check_sqr, direction);

  for (int i = 1; i < width; ++i) {
    if (board_at_coord(b, check_sqr) != c) {
      vector_destroy(check_sqr);
      return false;
    }
    board_wrap_vector_add(b, check_sqr, direction);
  }

  vector_destroy(check_sqr);
  return true;
}

// board_points_diagonal(b, square, direction) verifys that a direction points on a diagonal 
//   that the square lies on.
// ex. for vector (0, 2, 1) in a 3x3x3 board, components 0 and 1 are 1 unit away from the edge.
//       if direction is either (1, -1, 0) or (1, 0, 0) they are valid
// requires: the dimension of b, square and direction are same
// time: O(n) where n is the dimension
static bool board_points_diagonal(const struct board *b, const struct vector *square, const struct vector *direction) {
  assert(b);
  assert(square);
  assert(direction);

  const int dimension = board_dimension(b);
  assert(dimension == vector_dimension(square));
  assert(dimension == vector_dimension(direction));

  int width = board_width(b);
  int edge_distance = -1;

  for (int i = 0; i < dimension; ++i) {
    int direction_comp = vector_component(direction, i);
    int square_comp = vector_component(square, i);
    
    if (direction_comp != 0) {
      // set current_edge_distance
      int current_edge_distance = 0;

      // if direction_comp negative, pick distance from width, else pick distance to 0
      if (direction_comp < 0) {
        current_edge_distance = width - 1 - square_comp;
      } else {
        current_edge_distance = square_comp;
      }

      // set edge_distance or check if the current distance is the same
      if (edge_distance == -1) {
        edge_distance = current_edge_distance;
      } else if (edge_distance != current_edge_distance) {
        return false;
      }
    }
  }

  // if edge_distance was never set, no nonzero component of direction found - direction is zero
  if (edge_distance == -1) {
    return false;
  }

  return true;
}

// board_check_square_dir_perms(b, square, direction, comp) checks if a square has won tictactoe - if it is part of a
//   unbroken diagonal of same characters. checks the permutations of directions involving 1 or 0 unit steps in either direction.
//   checks these permutations involving components preceding comp
// ex. for 2d, the dir permutations are:
//   (1 1)  (1 0)  (1 -1)
//   (0 1)  (0 0)  (1 -1)
//   (-1 1) (-1 0) (-1 -1)
// effects: modifies direction
// time: unknown
static bool board_check_square_dir_perms(const struct board *b, const struct vector *square, struct vector *direction, int comp) {
  assert(b);
  assert(square);
  assert(direction);

  const int dimension = board_dimension(b);
  assert(dimension == vector_dimension(square));
  assert(dimension == vector_dimension(direction));

  int width = board_width(b);

  if (comp < 0) {
    if (!board_points_diagonal(b, square, direction)) {
      return false;
    }

    // when direction is valid, check the diagonal it points in
    return board_check_line(b, square, direction);
  } else {
    // for all permutations of a component being -1, 0 or 1
    for (int c = -1; c < 2; ++c) {
      vector_set_component(direction, comp, c);
      if (board_check_square_dir_perms(b, square, direction, comp - 1)) {
        return true;
      }
    }

    return false;
  }
}

char board_check_square(const struct board *b, const struct vector *square) {
  assert(b);
  assert(square);
  const int dimension = board_dimension(b);
  assert(dimension == vector_dimension(square));

  char c = board_at_coord(b, square);

  struct vector *direction = vector_create(dimension);
  bool result = board_check_square_dir_perms(b, square, direction, board_dimension(b) - 1);
  
  vector_destroy(direction);

  if (!result) {
    return '\0';
  }

  return c;
}