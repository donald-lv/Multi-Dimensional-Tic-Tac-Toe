// The implementation for the board module

#include "board.h"
#include "vector.h"
#include "resize-string.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

struct board *board_create(int width, int dimension) {
  struct board *b = malloc(sizeof(struct board));
  
  b->data = malloc(0);
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

// 
static void board_data_to_string(const int *data, int data_len, char *str, int * const str_len) {
  
}

char *board_to_string(struct board *b, char *str, int * const str_len) {
  
}