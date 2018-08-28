/*
 * Copyright ©2018 Gaohong Liu and cse333-staff.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ program instantiates an instance of IntPair, calls Test(), 
 * and then determines whether IntPair was passed by value or passed by reference to Test.
 *
 */

#include <cstdlib>
#include <iostream>
#include "IntPair.h"

using namespace std;
// declaration of test function which change the value of IntPair
void Test(IntPair p);

int main(int argc, char** argv) {
  // instantiates a new IntPair
  IntPair p(351, 333);
  Test(p);
  int resultX;
  int resultY;
  // get the value of IntPair
  p.Get(&resultX, &resultY);
  // test if values are changed or not
  // if values of IntPair are not changed, then pass by value
  if (resultX == 351 && resultY == 333) {
    cout << "Is pass by value" << endl;
  } else {
    // if not, pass by reference
    cout << "Is pass by reference" << endl;
  }
  return EXIT_SUCCESS;  // return success
}

// test function which get the two integers stored in IntPair and change
// these two values by incrementing 1
void Test(IntPair p) {
  int targetX;
  int targetY;
  // get two integers
  p.Get(&targetX, &targetY);
  targetX++;
  targetY++;
  // set new IntPair values
  p.Set(targetX, targetY);
}
