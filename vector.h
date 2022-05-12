// Interface for the vector module
//   A module containing the vector ADT and some functions for vectors

#include <stdbool.h>

// a vector with a given dimension and integer values for each component
struct vector;

// vector_dimension(v) produces the dimension of vector v
// requires: v is a valid pointer
// time: O(1)
int vector_dimension(const struct vector *v);

// vector_component(v, comp) returns the comp component of v
// requires: 0 <= comp < dimension of v
// time: O(1)
int vector_component(const struct vector *v, int comp);

// vector_add_component(v, comp, value) adds value to the (comp)th component of v
// requires: 0 <= comp < dimension of v
// effects: modifies v
// time: O(1)
void vector_add_component(struct vector *v, int comp, int value);

// vector_set_component(v, comp, value) sets the (comp)th component of v to value
// requires: 0 <= comp < dimension of v
// effects: modifies v
// time: O(1)
void vector_set_component(struct vector *v, int comp, int value);

// vector_zero(v) zeroes v
// effects: zeroes v
// time: O(n) where n is the dimension of v
void vector_zero(struct vector *v);

// vector_is_zero(v) determines if v is a zero vector
// time: O(n) where n is dimension of v
bool vector_is_zero(const struct vector *v);

// vector_print(v) prints a vector. no newline at end
// effects: produces output
// time: O(1)
void vector_print(const struct vector *v);

// vector_create(n) creates a vector with n components and returns its address
// requires: n >= 0
// effects: allocates memory for a vector with n components
// time: O(1)
struct vector *vector_create(int n);

// vector_destroy(v) frees the memory for v and its data
// requires: v is a valid pointer and its contents are valid
// effects: invalidates v
// time: O(1)
void vector_destroy(struct vector* v);