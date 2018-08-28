/*
 * Copyright ©2018 Gaohong Liu and cse333-staff.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ program prompts the user for a positive integer 
 * and prints out all integers that are factors of given integer
 */


#include <cstdlib>
#include <cinttypes>
#include <iostream>

using namespace std;
// declaration of function which can find out factors and print out
void printFactor(int64_t num);

int main(int argc, char** argv) {
  cout << "Which positive integer would you like me to factorize? ";
  int64_t num;
  // test if cin is successful
  if (!(cin >> num)) {
    cerr << "Scan input failed ";
    return EXIT_FAILURE;  // exit failed
  }
  // test if input number is <= 0
  if (num <= 0) {
    cerr << "Input is less or eqaul to zero " << endl;
    return EXIT_FAILURE;  // exit failed
  }
  // print all of factors
  printFactor(num);
  // print out to stdout
  cout << endl;
  return EXIT_SUCCESS;  // return success
}

// find all of factors and print out
void printFactor(int64_t num) {
  // test if given number is <= 0
  if (num <= 0) {
    cerr << "Invalid Argument " << endl;
    exit(EXIT_FAILURE);
  }
  for (int64_t i = 1; i <= num; i++) {
    if (num % i == 0) {
      if (i == 1) {
        cout << "1";
      } else {
        cout << " " << i;
      }
    }
  }
}

