// A game of n dimensional tic-tac-toe of any board width

#include "vector.h"
#include "board.h"
#include "tictactoe.h"
#include "text-commands.h"

#include <stdio.h>
#include <assert.h>

static const int DEFAULT_WIDTH = 4;
static const int DEFAULT_DIM = 3;
static const int DEFAULT_PLAYER_COUNT = 2;
static const char EMPTY_SQUARE = ' ';
static const char PLAYER_TOKENS[] = {'X', 'O', 'M', 'N', 'V', 'A', '#', '8'};
static const int MAX_PLAYER_COUNT = 8;
static const int MIN_PLAYER_COUNT = 2;

// setup(width, dimension, player_count) sets width, dimension, player_count to prompted, input numbers.
//   ends with 2 traling new lines
// effects: produces output
//          takes input
// time: O(1)
static int setup_cmd(int *width, int *dimension, int *player_count);

// help() gives a list of commands in the pregame stage
//   ends with 2 traling new lines
// effects: produces output
// time: O(1)
static void help_cmd(void);

// tutorial() prints instructions on how to play the game
// effects: produces output
// time: O(1)
static void tutorial_cmd(void);

// run_turn(b, player_token) runs a player's turn given their char, returns the status of the turn
//   0 if the player did not win on this turn
//   1 if the player won
//   -1 if the player entered invalid input
// effects: takes input
// time: O(1)
static int run_turn(struct board *b, int player);

int main(int argc, char *argv[]) {
  long tutorial = command_to_long("tutorial");
  long play = command_to_long("play");
  long setup = command_to_long("setup");
  long help  = command_to_long("help");
  long quit = command_to_long("quit");

  long commands[] = {tutorial, play, setup, help, quit};
  int command_count = 5;
  
  int width = DEFAULT_WIDTH;
  int dimension = DEFAULT_DIM;
  int player_count = 2;

  struct board *b = board_create(width, dimension);
  long command = INVALID_COMMAND;

  help_cmd();

  while (true) {
    bool exit = false;
    
    do {
      printf("Enter a command: ");
      command = command_read();
      printf("\n");

      int command_index = command_long_find(command, commands, command_count);
      
      if (command_index == -1) {
        if (command == QUIT_SYMBOL) {
          exit = true;
          break;
        }

        printf("Invalid command. Type 'help' for a list of valid commands.\n\n");  
      } else {
        if (command == tutorial) {
          tutorial_cmd();
        } else if (command == play) {
          break;
        } else if (command == setup) {
          int result = setup_cmd(&width, &dimension, &player_count);

          if (result == -1) {
            exit = true;
            break;
          }

        } else if (command == help) {
          help_cmd();
        } else if (command == quit) {
          exit = true;
          break;
        }
      }
      
    } while (true);

    if (exit) {
      break;
    }

    board_change(b, width, dimension);
    board_overwrite(b, ' ');
    int b_len = board_length(b);
    
    int game_winner = -1;
    
    for (int i = 0; i < b_len; ++i) {
      int player = i % player_count;

      int turn_result = run_turn(b, player);

      if (turn_result == -1) {
        exit = true;
        break;
      } else if (turn_result == 1) {
        game_winner = player;
        break;
      }
    }

    if (exit) {
      break;
    }

    if (game_winner == -1) {
      printf("Tie. Noone won.\n");
    } else if (game_winner >= 0) {
      printf("Player %d (%c) won!\n", game_winner + 1, PLAYER_TOKENS[game_winner]);
      board_print(b);
      printf("\n");
    }
  }

  printf("Thanks for playing \n");
}

// read_until(c) reads characters until c or EOF is encountered. reads c.
//   returns -1 if EOF was reached, 0 otherwise
// effects: reads input
// time: O(n) where n is the amount of characters until c is encountered
static int read_until(char c) {
  int scan_result;
  char in = '\0';

  do {
    scan_result = scanf(" %c", &in);
  } while (scan_result != EOF && in != c);

  if (scan_result == EOF) {
    return -1;
  }

  return 0;
}

static int setup_cmd(int *width, int *dimension, int *player_count) {
  assert(width);
  assert(dimension);

  int result = 0;
  bool valid_in = false;
  
  // read width
  do {
    printf("Enter the width of the board: ");
    result = scanf("%d", width); 
    printf("\n");

    if (result == EOF) {
      return -1;
    } else if (result != 1) {
      // read an useless word
      result = scanf("%*s");

      if (result == EOF) {
        return -1;
      }
      
      printf("That is not an integer.\n");
    } else if (*width >= MIN_WIDTH) {
      valid_in = true;
    } else {
      printf("Invalid width: must be greater than or equal to %d\n", MIN_WIDTH);
    }


  } while (!valid_in);
  
  // read dimension
  valid_in = false;

  do {
    printf("Enter the number of dimensions: ");
    result = scanf("%d", dimension);
    printf("\n");
    
    if (result == EOF) {
      return -1;
    } else if (result != 1) {
      // read an useless word
      result = scanf("%*s");

      if (result == EOF) {
        return -1;
      }
      
      printf("That is not an integer.\n");
    } else if (*dimension >= MIN_DIMENSION) {
      valid_in = true;
    } else {
      printf("Invalid dimension: must be greater than or equal to %d\n", MIN_DIMENSION);
    }

  } while (!valid_in);

  // read player count
  valid_in = false;

  do {
    printf("Enter the number of players: ");
    result = scanf("%d", player_count);
    printf("\n");

    if (result == EOF) {
      return -1;
    } else if (result != 1) {
      // read an useless word
      result = scanf("%*s");

      if (result == EOF) {
        return -1;
      }
      
      printf("That is not an integer.\n");
    } else if (*player_count >= MIN_PLAYER_COUNT && 
        *player_count <= MAX_PLAYER_COUNT) {
      valid_in = true;
    } else {
      printf("Invalid player count: must be between %d and %d players.\n", MIN_PLAYER_COUNT, MAX_PLAYER_COUNT);
    }

  } while (!valid_in);

  printf("The board will now be %d wide in %d dimensions. There will be %d players playing. \n", *width, *dimension, *player_count);

  printf("\n");
  return 0;
}

static void help_cmd(void) {
  printf("Multidimensional Tic Tac Toe\n\n");
  printf("-Type 'tutorial' for the tutorial\n");
  printf("-Type 'play' to play\n");
  printf("-Type 'setup' to customize the board\n");
  printf("-Type 'help' for commands\n");
  printf("-Type 'quit' to quit \n");
  
  printf("\n");
}

static void tutorial_cmd(void) {
  // create a test board
  const int tutorial_width = 3;
  const int tutorial_dimension = 3;

  struct board *tut_board = board_create(tutorial_width, tutorial_dimension);
  struct vector *square = vector_create(tutorial_dimension);

  board_overwrite(tut_board, ' ');

  // intro
  printf("\nTUTORIAL\n");
  printf("This is tic-tac-toe in varying dimensions, of varying size.\n");
  printf("Here is an empty %dd board of width %d: \n\n", tutorial_dimension, tutorial_width);
  board_print(tut_board);

  // coord tut
  printf("\n---------\n\n");
  printf("Coordinates start at 0 and end at (width - 1). \n");
  printf("For example, this X is the point with coordinates (1 2 0) for the same board: \n\n");
  
  vector_set(square, (int[3]){1, 2, 0});
  board_set_square(tut_board, square, 'X');
  board_print(tut_board);

  printf("and this O is the point with coordinates (1 2 2): \n\n");

  vector_set(square, (int[3]){1, 2, 2});
  board_set_square(tut_board, square, 'O');
  board_print(tut_board);

  // victory tut
  board_overwrite(tut_board, ' ');
  
  printf("A player wins by filling a straight diagonal in any dimension. \n");
  printf("For example, here are some ways to win: \n\n");
  
  vector_set(square, (int[3]){0, 2, 1});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){1, 2, 1});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){2, 2, 1});
  board_set_square(tut_board, square, 'X');

  printf("A diagonal across 1 dimension \n");
  board_print(tut_board);
  printf("\n");

  board_overwrite(tut_board, ' ');

  vector_set(square, (int[3]){0, 2, 2});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){1, 1, 2});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){2, 0, 2});
  board_set_square(tut_board, square, 'X');

  printf("A diagonal across 2 dimensions \n");
  board_print(tut_board);
  printf("\n");
  

  board_overwrite(tut_board, ' ');

  vector_set(square, (int[3]){0, 2, 0});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){1, 2, 1});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){2, 2, 2});
  board_set_square(tut_board, square, 'X');

  printf("Another diagonal across 2 dimensions \n");
  board_print(tut_board);
  printf("\n");

  board_overwrite(tut_board, ' ');

  vector_set(square, (int[3]){0, 2, 0});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){1, 1, 1});
  board_set_square(tut_board, square, 'X');
  vector_set(square, (int[3]){2, 0, 2});
  board_set_square(tut_board, square, 'X');

  
  printf("A diagonal across 3 dimensions \n");
  board_print(tut_board);
  printf("\n");

  printf("Beware: diagonals can go through all N dimensions of the board. \n");
  printf("Here, they can step through all 3 dimensions\n");
  printf("In a 4d board, they can step through all 4.\n");
  printf("\n");
  
  printf("Have Fun!\n");
  printf("\n");
}

static int run_turn(struct board *b, int player) {
  const int dimension = board_dimension(b);
  const int width = board_dimension(b);
  const char player_token = PLAYER_TOKENS[player];

  assert(player_token != EMPTY_SQUARE);
  assert(b);

  struct vector *v = vector_create(dimension);
  
  board_print(b);
  printf("\n");
  
  printf("Player %d's turn [ %c ]\n", player + 1, player_token);
  printf("The board width is %d and dimension is %d.\n", width, dimension);
  printf("Enter a vector by surrounding the coordinates with brackets ().\n");

  do {
    int scan_result = 0;
    printf("Enter a vector: ");

    scan_result = read_until('(');
    if (scan_result == EOF) {
      return -1;
    }

    scan_result = vector_read(v);
    if (scan_result == EOF) {
      return -1;
    } 
    
    bool valid_vector_read = true;
    
    char c = '\0';
    do {
      scan_result = scanf("%c", &c);
    } while (scan_result == 1 && (c == ' ' || c == '\n'));
    
    if (scan_result == EOF) {
      return -1;
    } else if (c != ')') {
      valid_vector_read = false;
    }

    printf("\n");

    if (scan_result != 1 || !vector_in_board(b, v)) {
      valid_vector_read = false;  
    }

    if (!valid_vector_read) {
      printf("Invalid vector. There should be %d coordinates wrapped by brackets (). The vector's components must be between 0 and %d\n", dimension, width);
      printf("ex. (4 1 3 2) for 4 dimensions. \n\n");
    } else if (board_at_coord(b, v) != EMPTY_SQUARE) {
      printf("That square is occupied.\n");
    } else {
      board_set_square(b, v, player_token);
      break;
    }

  } while (true);

  if (board_check_square(b, v) == player_token) {
    return 1;
  } else {
    return 0;
  }
}
