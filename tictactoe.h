// The interface for the tictactoe module
//   Prodivdes tools on the board ADT to play tictactoe

#include "board.h"

// check_square(b, square) checks if the square in b is a winning square. returns the character at that square
//   if it is a winning square. otherwise gives '\0'
// requires: b and square are same dimension
// time: unknown
char check_square(const struct board *b, const struct vector *square);