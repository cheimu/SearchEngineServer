/*
 * Copyright ©2018 Gaohong Liu.  All rights reserved.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 *
 * This C header file creates declaration of Nth prime number which 
 * takes an unint16_t n as parameter and return an nth uint64_t prime 
 * number.
 */

#ifndef _NTH_PRIME_
#define _NTH_PRIME_

#include <stdint.h>

// declaration of function which can find the nth prime number
// which takes an uint16_t n as parameter and n > 0 and returns
// an uint64_t nth prime number and it is less than UINT64_T_MAX
// Example:
// NthPrime(1) -> 2
// Nthprime(2) -> 3
// NthPrime(3) -> 5
// Nthprime(4) -> 7
uint64_t NthPrime(uint16_t n);

#endif
