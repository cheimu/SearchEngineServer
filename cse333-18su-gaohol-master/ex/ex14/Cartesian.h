/*
 * Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ header file declares a subclas of Coordinate
 * called Cartesian that represents a 2D cartesian coordinate 
 * which has two fields x_ and y_ and two virtual functions 
 * Distance and toStrings.
 */

#ifndef _CARTESIAN_H_
#define _CARTESIAN_H_

#include <string>
#include "Coordinate.h"
using namespace std;
class Cartesian : public Coordinate {
 public:
  Cartesian(double x, double y);

  // get distance between two points using Cartesian form
  double Distance(const Cartesian &other);

  // get object in printable string form
  virtual string ToString() const override;

  // destructor
  virtual ~Cartesian() {}

 private:
  // private fields: x and y
  double x_, y_;
};
#endif  // _CARTESIAN_H_
