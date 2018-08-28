/*
 * Copyright ©2018 Gaohong Liu.  All rights reserved.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C program uses the vector type to test basic function related to it
 * including vector create, vector set and prints elements inside of vector.
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Vector.h"

#define INITIAL_SIZE 4  // initial vector length
#define FINAL_SIZE 10  // final test vector length.

// declaration of local function printing out elements inside of the vector
static void PrintIntVector(vector_t v);

int main(int argc, char *argv[]) {
  size_t i;
  vector_t v = VectorCreate(INITIAL_SIZE);
  // test if vector create failed; if failed, exit failure
  if (v == NULL)
    return EXIT_FAILURE;

  for (i = 0; i < FINAL_SIZE; i++) {  // Place some elements in the vector.
    int* x = (int*)malloc(sizeof(int));
    // test if malloc successfully
    if (x == NULL) {
      printf("Out Of Memory");
      return EXIT_FAILURE;  // return NULL required in header file
    }
    element_t old;
    *x = i;
    bool isSetDone = VectorSet(v, i, x, &old);
    // test if vector set successfully, if not, return failure
    if (!isSetDone) {
      printf("ERROR: Set Failed!");
      return EXIT_FAILURE;  // return failure
    }
  }
  // print out elements inside of vector
  PrintIntVector(v);
  // free everything inside of vector
  for (int i = 0; i < FINAL_SIZE; i++) {
    free(VectorGet(v, i));
  }
  VectorFree(v);
  return EXIT_SUCCESS;  // return success
}

// Print the elements in the vector on a line.
// assume v is initilized. If it contains null element
// it will print something unrelated.
static void PrintIntVector(vector_t v) {
  // assert if v is null
  assert(v != NULL);
  size_t i;
  size_t length;
  length = VectorLength(v);
  if (length > 0) {
    printf("[%d", *((int*)VectorGet(v, 0)));
    for (i = 1; i < VectorLength(v); ++i)
      printf(",%d", *((int*)VectorGet(v, i)));
    printf("]\n");
  }
}
