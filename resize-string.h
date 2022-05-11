// The interface for the resize-string module
//   Includes string adt, a resizable array of characters

// All pointer arguments must be valid pointers
// All non-const pointer arguments must be pointers to heap

#include <assert.h>
#include <stdlib.h>

struct string;

// string_create() initializes a new string structure and returns a pointer to the structure.
// effects: allocates heap memory for string structure and its data
struct string *string_create();

// string_destroy(str) destroy string str
// effects: frees str and its data
void string_destroy(struct string *str);

// string_length(str) returns length of str
int string_length(const struct string *str);

// -------- specific string functions --------

// string_append_char(str, c) appends c to str.
// effects: modifies str
void string_append_char(struct string *str, char c);

// string_append_char_arr(str, arr, arr_len) appends first arr_len characters in arr to str. appends nothing
//   if arr_len <= 0.
// effects: modifies str
void string_append_char_arr(struct string *str, const char *arr, int arr_len);

// string_append_string(str, tail) appends tail to str.
// effects: modifies str
void string_append_string(struct string *str, const struct string *tail);

// string_slice(str, start, end) returns a new string that is the slice of str with starting index of start
//   and ending index of end - includes the element at start and discludes the element at end
// requires: 0 <= start < string length
//           0 <= end <= string length
// effects: allocates memory for the slice
struct string *string_slice(const struct string *str, int start, int end);

// string_print(str) prints the string.
// effects: produces output
void string_print(struct string *str);