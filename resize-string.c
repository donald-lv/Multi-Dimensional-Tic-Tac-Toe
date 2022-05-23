// Implementation of the resize-string module
//   See interface for documentation

// All pointer arguments must be valid pointers
// All non-const pointer arguments must be pointers to heap

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct string {
  char *data;
  int len;
  int maxlen;
};

struct string *string_create() {
  struct string *ret = malloc(sizeof(struct string));
  
  ret->data = malloc(sizeof(char));
  ret->len = 0;
  ret->maxlen = 1;

  return ret;
}

void string_destroy(struct string *str) {
  free(str->data);
  free(str);
}

int string_length(const struct string *str) {
  return str->len;
}

char string_char_at(const struct string *str, int index) {
  assert(str);
  assert(0 <= index);
  assert(index < str->len);

  return str->data[index];
}

char *string_to_arr(const struct string *str) {
  assert(str);

  char *ret = malloc((str->len + 1) * sizeof(char));
  strcpy(ret, str->data);
  return ret;
}

void string_append_char(struct string *str, char c) {
  assert(str);

  str->data[str->len] = c;
  ++(str->len);

  // guarantee space for a terminator
  if (str->len == str->maxlen) {
    str->maxlen *= 2;
    str->data = realloc(str->data, str->maxlen);
  }
  
  str->data[str->len] = '\0';
}

void string_append_char_arr(struct string *str, const char *arr, int arr_len) {
  assert(str);
  assert(arr);

  for (const char *c = arr; c < arr + arr_len; ++c) {
    string_append_char(str, *c);
  }
}

void string_append_string(struct string *str, const struct string *tail) {
  assert(str);
  assert(tail);

  string_append_char_arr(str, tail->data, tail->len);
}

struct string *string_slice(const struct string *str, int start, int end) {
  int str_len = string_length(str);

  assert(0 <= start);
  assert(start < str_len);
  assert(0 <= end);
  assert(end <= str_len);

  struct string *ret = string_create();
  string_append_char_arr(ret, str -> data + start, end - start);

  return ret;
}

int string_read(struct string *str, bool ws) {
  // read leading whitespace
  char in = '\0';
  bool loop = false;
  int result = 0;

  if (ws) {
    do {
      loop = false;
      result = scanf("%c", &in);
      
      if (result == 1) {
        if (in == ' ' || in == '\n') {
          loop = true;
        }
      }
    } while (loop);
  } else {
    result = scanf("%c", &in);
  }

  if (result != 1) {
    return result;
  }

  string_destroy(str);
  str = string_create();
  
  loop = true;

  while (loop) {
    string_append_char(str, in);

    // check input
    loop = false;
    result = scanf("%c", &in);
    if ((result == 1) && (in != ' ' && in != '\n')) {
      loop = true;
    }
  }

  return result;
}

void string_print(const struct string *str) {
  assert(str);
  assert(str->data);
  printf("%s", str->data);
}