// implementation of the vector module

#include "vector.h"
#include <stdlib.h>
#include <assert.h>


struct vector {
  int *data;
  int dimension;
};

// see interface for documentation
int vector_dimension(const struct vector *v) {
  assert(v);
  return v->dimension;
}

// see interface for documentation
int vector_component(const struct vector *v, int comp) {
  assert(v);
  assert(0 <= comp);
  assert(comp <= vector_dimension(v));

  return (v->data)[comp];
}

// see interface for documentation
void vector_add_component(struct vector *v, int comp, int value) {
  assert(v);
  assert(0 <= comp);
  assert(comp <= vector_dimension(v));

  v->data[comp] = value;
}

// see interface for documentation
struct vector *vector_create(int n) {
  assert(n > 0);

  struct vector *vect = malloc(sizeof(struct vector));
  
  vect->dimension = n;
  vect->data = malloc(n * sizeof(int));

}

// see interface for documentation
void vector_destroy(struct vector* v) {
  assert(v);
  assert(v->data);

  free(v->data);
  free(v);
}