/*
 * Copyright ©2018 Gaohong Liu.  All rights reserved.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C program tests function of Nth prime number and check
 * the 7th, 8th and 46th prime number
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "NthPrime.h"

int main(int argc, char **argv) {
  uint64_t check_a = NthPrime(7);
  uint64_t check_b = NthPrime(8);
  uint64_t check_c = NthPrime(46);
  // check if we get 7th prime number
  if (check_a == 17) {
    printf("Correct Result, Success to find 7th prime number: %"
                                      PRIu64 " \n", check_a);
  } else {
    // if not, return failure
    printf("Wrong Result: Fail to find 7th prime number \n");
    return EXIT_FAILURE;
  }
  // check if we get 8th prime number
  if (check_b == 19) {
    printf("Correct Result, Success to find 8th prime number: %"
                                      PRIu64 " \n", check_b);
  } else {
    // if not, return failure
    printf("Wrong Result: Fail to find 8th prime number \n");
    return EXIT_FAILURE;
  }
  // check if we get 46 prime number
  if (check_c == 199) {
    printf("Correct Result, Success to find 46rd prime number: %"
                                      PRIu64 " \n", check_c);
  } else {
    // if not, return failure
    printf("Wrong Result: Fail to find 46rd prime number \n");
    return EXIT_FAILURE;
  }
  for (int i = 1; i < 20; i++) {
    uint64_t check_d = NthPrime(i);
    printf("Correct Result, Success to find 46rd prime number: %"
                                      PRIu64 " \n", check_d);
  }
  // if all tests passed, print success
  printf("All Test Passed \n");
  return EXIT_SUCCESS;  // return success
}
