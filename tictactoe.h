// The interface for the tictactoe module
//   Prodivdes tools on the board ADT to play tictactoe

#include "board.h"

// board_check_square(b, square) checks if the square in b is a winning square. returns the character at that square
//   if it is a winning square. otherwise gives '\0'
// requires: b and square are same dimension
// time: unknown
char board_check_square(const struct board *b, const struct vector *square);

// board_check_line(b, square, direction) determines if width number of squares along the direction 
//   involving square are the same characters (line will wrap around board).
bool board_check_line(const struct board *b, const struct vector *square, const struct vector *direction);
