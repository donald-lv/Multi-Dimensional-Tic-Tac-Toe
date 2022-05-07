// Interface for the vector module
//   A module containing the vector ADT and some functions for vectors

// a vector with a given dimension and coordinates
struct vector;

// vector_dimension(v) produces the dimension of vector v
// requires: v is a valid pointer
// time: O(1)
int vector_dimension(const struct vector *v);

// vector_component(v, i) returns 
// requires: 0 <= i < dimension of v
// time: O(1)
int vector_component(const struct vector *v, int i);

// vector_dot(v, u) produces the real inner product (dot product) of v and u
// requires: v and u have the same dimensions
// effects: allocates space for a vector of same dimension of v and u
// time: O(n)
struct vector *vector_dot(const struct vector *v, const struct vector *u);

// vector_create(n) creates a vector with n components and returns its address
// requires: n > 0
// effects: allocates memory for a vector with n components
// time: O(1)
struct vector *vector_create(int n);

// vector_destroy(v) frees the memory for v and its data
// requires: v is a valid pointer and its contents are valid
// effects: invalidates v
// time: O(1)
void vector_destroy(struct vector* v);