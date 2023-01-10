// The interface for the resize-string module
//   Includes string adt, a resizable array of characters

// All pointer arguments must be valid pointers
// All non-const pointer arguments must be pointers to heap

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

struct string;

// string_create() initializes a new string structure and returns a pointer to the structure.
// effects: allocates heap memory for string structure and its data
// time: O(1)
struct string *string_create();

// string_destroy(str) destroy string str
// effects: frees str and its data
// time: O(1)
void string_destroy(struct string *str);

// string_length(str) returns length of str
// time: O(1)
int string_length(const struct string *str);

// string_char_at(str, index) returns the ith character in str.
// requires: 0 <= index < str's length
// time: O(1)
char string_char_at(const struct string *str, int index);

// string_to_arr(str) returns a copy of str's data
// effects: allocates memory for a char array the length of str + 1
// time: O(n) where n is the length of str
char *string_to_arr(const struct string *str);

// -------- specific string functions --------

// string_append_char(str, c) appends c to str.
// effects: modifies str
// time: O(1)
void string_append_char(struct string *str, char c);

// string_append_char_arr(str, arr, arr_len) appends first arr_len characters in arr to str. appends nothing
//   if arr_len <= 0.
// effects: modifies str
// time: O(n) where n is arr_len
void string_append_char_arr(struct string *str, const char *arr, int arr_len);

// string_append_string(str, tail) appends tail to str.
// effects: modifies str
// time: O(n) where n is length of tail
void string_append_string(struct string *str, const struct string *tail);

// string_slice(str, start, end) returns a new string that is the slice of str with starting index of start
//   and ending index of end - includes the element at start and discludes the element at end
// requires: 0 <= start < string length
//           0 <= end <= string length
// effects: allocates memory for the slice
// time: O(n) where is n is difference between end and start
struct string *string_slice(const struct string *str, int start, int end);

// string_read(str, ws) reads a string to str and one trailing whitespace character. 
//   returns 1 if a string was read to a whitespace, EOF if EOF was reached. ws determines if initial
//   whitespace should be read.
// requires: str is a valid pointer
// effects: reads input
//          modifies str
// time: O(n) where n is the length of the string read. (amortized)
int string_read(struct string *str, bool whitespace);

// string_print(str) prints the string.
// effects: produces output
// time: O(n) where n is the length of the string
void string_print(struct string *str);
