// implementation of the vector module
//   see interface for documentation

// All pointer arguments must be valid pointers

#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct vector {
  int *data;
  int dimension;
};

int vector_dimension(const struct vector *v) {
  assert(v);
  return v->dimension;
}

int vector_component(const struct vector *v, int comp) {
  assert(v);
  assert(0 <= comp);
  assert(comp <= v->dimension);

  return (v->data)[comp];
}

void vector_add_component(struct vector *v, int comp, int value) {
  assert(v);
  assert(0 <= comp);
  assert(comp <= v->dimension);

  v->data[comp] += value;
}

void vector_set_component(struct vector *v, int comp, int value) {
  assert(v);
  assert(0 <= comp);
  assert(comp <= v->dimension);

  v->data[comp] = value;
}

void vector_set(struct vector *v, const int *values, int len) {
  assert(v);
  assert(values);

  int dimension = v->dimension;  
  assert(len >= v->dimension);

  for (int i = 0; i < dimension; ++i) {
    v->data[i] = values[i];
  }
}

void vector_zero(struct vector *v) {
  assert(v);
  for (int *i = v->data; i < v->data + v->dimension; ++i) {
    *i = 0;
  }
}

bool vector_is_zero(const struct vector *v) {
  assert(v);

  for (const int *i = v->data; i < v->data + v->dimension; ++i) {
    if (i != 0) {
      return false;
    }
  }

  return true;
}

struct vector *vector_create(int n) {
  assert(n >= 0);

  struct vector *vect = malloc(sizeof(struct vector));
  
  vect->dimension = n;
  vect->data = malloc(n * sizeof(int));

}

void vector_destroy(struct vector *v) {
  assert(v);
  assert(v->data);

  free(v->data);
  free(v);
}

void vector_print(const struct vector *v) {
  printf("(");

  if (v->dimension > 0) {
    printf("%d", v->data[0]);
    for (int i = 1; i < v->dimension; ++i) {
      printf(", %d", v->data[i]);
    }
  }

  printf(")");
}