// Interface for text-commands module
//   Provides functions for setting up and reading text-based commands 
//   Commands must be string of lower-case alphabetical characters shorter than or as long as 13 characters

#include "resize-string.h"
#include <stdbool.h>

extern const long INVALID_COMMAND;
extern const long QUIT_SYMBOL;

// command_to_long(str) gives the unique number associated with string char array command str
// requires: the str is a command
// time: O(n) where n is length of str
long command_to_long(const char *str);

// string_command_to_long(str) gives the unique number associated with resize-string command str
// requires: str is a command
// time: O(n) where n is the length of string
long string_command_to_long(const struct string *str);

// command_read() reads a command until a whitespace character or eof is reached. removes leading whitespace.
//   returns the command read
// effects: reads input
// time: O(n) where n is the length of the command. (amortized)
long command_read(void);

// command_long_is_valid(c) determines if the int for a command represents a valid command.
// time: O(1)
bool command_long_is_valid(long c);

// command_long_find(c) finds command's index in commands, given the length, len, of commands.
//   returns -1 if no match is found.
// time: O(n) where n is len
int command_long_find(long command, long commands[], int len);
