/*
 * Copyright ©2018 Gaohong Liu.  All rights reserved.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C program creates takes index n as parameter and returns
 * nth prime number.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include "NthPrime.h"

// declaration of helper function which checks whether current number is
// prime number
bool isPrime(uint64_t cur);

uint64_t NthPrime(uint16_t n) {
  // If input n is <= 0, print error and return failure
  if (n <= 0) {
      printf("Invalid Input");
      exit(EXIT_FAILURE);  // return failure
  }
  uint64_t result = 2;
  uint64_t current = 3;
  while (n > 1) {
    // If current number is larger than UINTT64_MAX, print error and
    // return failure
    if (current > UINT64_MAX) {
      printf("Number Overflow");
      exit(EXIT_FAILURE);
    }
    if (isPrime(current)) {
      n--;
      result = current;
    }
    current++;
  }
  // return nth prime number
  return result;
}

// check if current number is prime number or not. This helper function
// takes an uint64_t current number as input and return a bool
bool isPrime(uint64_t cur) {
  bool prime = true;
  uint64_t current = 2;
  while (current < cur && prime != false) {
    if (cur % current == 0) {
      prime = false;
    } else {
      prime = true;
    }
    current++;
  }
  return prime;
}

