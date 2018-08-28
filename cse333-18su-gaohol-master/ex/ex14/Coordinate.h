/*
 * Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ header defines a purely virtual class
 * that represents an abstract 2-dimensional coordinate.
 * It only contains a pure virtual method called ToString
 * that returns a string representation.
 */

#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include <string>
using namespace std;

class Coordinate {
 public:
  // pure virtual function toString, and default is empty
  virtual string ToString() const = 0;
};

#endif  // _COORDINATE_H_
