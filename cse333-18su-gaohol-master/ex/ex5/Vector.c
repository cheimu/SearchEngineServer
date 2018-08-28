/*
 * Copyright ©2018 Gaohong Liu.  All rights reserved.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C program implements all vector type related functions
 * as desribed in header file including vector create, vector set
 * vector free, vector get, and vector length
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Vector.h"

// declaration of local function which is used to resize the array in vector
static element_t *ResizeArray(element_t *arry, size_t oldLen, size_t newLen);

vector_t VectorCreate(size_t n) {
  vector_t v = (vector_t)malloc(sizeof(struct vector_t));
  // test if malloc failed; if failed, return null as required in header file
  if (v == NULL) {
    printf("Out of Memory");
    return NULL;  // return null
  }
  element_t* newArray = (element_t*)malloc(n*sizeof(element_t));
  // test if malloc failed; if failed, return null as required in header file
  if (newArray == NULL) {
    printf("Out of Memory");
    return NULL;  // return null
  }
  v->arry = newArray;
  v->length = n;
  size_t i;
  // initialize everything inside of created vector
  for (i = 0; i < n; i++) {
    v->arry[i] = NULL;
  }
  return v;
}

void VectorFree(vector_t v) {
  // assert if input v is not null
  assert(v != NULL);
  free(v->arry);
  free(v);
}

bool VectorSet(vector_t v, size_t index, element_t e, element_t *prev) {
  // assert if input v is not null
  assert(v != NULL);
  if (index >= v->length) {
    size_t newLength = index+1;
    element_t* newArray = ResizeArray(v->arry, v->length, newLength);
    if (newArray == NULL) {
      printf("ERROR: Resize Failed");
      exit(EXIT_FAILURE);
    }
    // free old array
    free(v->arry);
    v->arry = newArray;
    v->length = newLength;
  }
  *prev = v->arry[index];
  v->arry[index] = e;
  return true;
}

element_t VectorGet(vector_t v, size_t index) {
  // assert if input v is not null
  assert(v != NULL);
  // assert if input index is smaller than vector length
  assert(index < v->length);
  return v->arry[index];
}

size_t VectorLength(vector_t v) {
  // assert if input v is null
  assert(v != NULL);
  return v->length;
}

// Returns a copy of arry with new length newLen.  If newLen < oldLen
// then the returned array is clipped.  If newLen > oldLen, then the
// resulting array will be padded with NULL elements.
static element_t *ResizeArray(element_t *arry, size_t oldLen, size_t newLen) {
  // assert if input v is not null
  assert(arry != NULL);
  size_t i;
  size_t copyLen = oldLen > newLen ? newLen : oldLen;
  element_t* newArry = (element_t*)malloc(newLen*sizeof(element_t));
  // test if malloc failed; if failed, return null
  if (newArry == NULL)
    return NULL;  // malloc error!!!

  // Copy elements to new array
  for (i = 0; i < copyLen; i++)
    newArry[i] = arry[i];
  // Null initialize rest of new array.
  for (i = copyLen; i < newLen; i++)
    newArry[i] = NULL;
  return newArry;
}


