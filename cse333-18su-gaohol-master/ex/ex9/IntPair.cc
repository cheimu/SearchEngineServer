/*
 * Copyright ©2018 Gaohong Liu and cse333-staff.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ program implements IntPair class which has two private
 * fields x and y, and Get and Set methods.
 */

#include "IntPair.h"
IntPair:: IntPair(const int x, const int y) {
  x_ = x;
  y_ = y;
}

void IntPair::Get(int* const x, int* const y) {
  *x = x_;
  *y = y_;
}

void IntPair::Set(const int x, const int y) {
  x_ = x;
  y_ = y;
}


