/*
 * Copyright ©2018 Gaohong Liu.  All rights reserved.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This header file contains all declaration of vector type
 * related function and basic data type including element type, 
 * vector type, vector create, vector free, vector set, vector get
 * and vector length
 */
#ifndef _VECTOR_
#define _VECTOR_
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
// An arbitrary pointer to represent an element in the vector.
typedef void* element_t;

// An expandable array of element_ts.
typedef struct vector_t {
  size_t length;
  element_t *arry;
} *vector_t;

// Creates a vector_t with an initial length of n. By default, all elements
// inside of it are NULL. It failed to create a new vector_t
// returns NULL.  Assumes v != NULL.
vector_t VectorCreate(size_t n);

// Frees the memory allocated for the vector_t.  Assumes v != NULL.
void VectorFree(vector_t v);

// Sets the nth element of v to be e.
// Returns the previous nth element_t in prev.
// Freeing e is the responsibility of the user, not the vector_t.
// Returns true iff successful.  Assumes v != NULL.
bool VectorSet(vector_t v, size_t index, element_t e, element_t *prev);

// Returns the element at the given index within v.  Assumes v != NULL.
element_t VectorGet(vector_t v, size_t index);

// Returns the length of v.  Assumes v != NULL.
size_t VectorLength(vector_t v);

#endif
