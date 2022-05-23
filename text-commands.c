// An implementation of the text-commands module
#include "resize-string.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

const long INVALID_COMMAND = LONG_MIN;
const long QUIT_SYMBOL = LONG_MIN + 1;
const int CHAR_COUNT = 'z' - 'a' + 1;

// char_is_lower_case(c) determins if c is a lowercase character
// time: O(1)
static bool char_is_lower_case(char c) {
  if ((c >= 'a') || (c <= 'z')) {
    return true;
  }

  return false;
}

long command_to_long(const char *str) {
  assert(str);

  long sum = 0;
  int str_count = 0;

  if (!*str) {
    return INVALID_COMMAND;
  }

  sum += *str - 'a';
  ++str;

  while (*str && str_count < 13) {
    if (!char_is_lower_case(*str)) {
      return INVALID_COMMAND;
    }

    sum *= CHAR_COUNT;
    sum += *str - 'a';

    ++str;
    ++str_count;
  }

  if (str_count >= 13) {
    return INVALID_COMMAND;
  }
  if (sum == 0) {
    return INVALID_COMMAND;
  }

  return sum;
}

long string_command_to_long(const struct string *str) {
  assert(str);

  char *copy = string_to_arr(str);
  long ret = command_to_long(copy);

  return ret;
}

long command_read(void) {
  int len = 0;
  struct string *str = string_create();
  int result = string_read(str, true);
  long sym = 0;
  
  if (string_length(str) == 0) {
    if (result == EOF) {
      sym = QUIT_SYMBOL;
    } else {
      sym = INVALID_COMMAND;
    }
  } else {
    sym = string_command_to_long(str);
  }

  string_destroy(str);

  return sym;
}

bool command_long_is_valid(long c) {
  if (c == QUIT_SYMBOL || c == INVALID_COMMAND) {
    return false;
  }

  return true;
}

int command_long_find(long command, long commands[], int len) {
  for (int i = 0; i < len; ++i) {
    if (command == commands[i]) {
      return i;
    }
  }

  return -1;
}