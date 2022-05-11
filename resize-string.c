// Implementation of the resize-string module
//   See interface for documentation

// All pointer arguments must be valid pointers
// All non-const pointer arguments must be pointers to heap

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

// -------- specific string functions --------

void string_append_char(struct string *str, char c) {
  assert(str);

  // guarantee space for a terminator
  if (str->len == str->maxlen) {
    str->maxlen *= 2;
  }

  *(str->data + str->len) = c;
  ++(str->len);
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

void string_print(const struct string *str) {
  assert(str);
  assert(str->data);

  str->data[str->len] = '\0';
  printf("%s", str->data);
}