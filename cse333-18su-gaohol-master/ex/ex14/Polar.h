/*
 * Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ header file declares a subclas of Coordinate
 * called Polar that represents a 2D Polar coordinate 
 * which has two fields r_ and theta_ and two virtual functions 
 * Distance and toStrings.
 */

#ifndef _POLAR_H_
#define _POLAR_H_

#include <string>
#include "Coordinate.h"
using namespace std;
class Polar : public Coordinate {
 public:
  Polar(double r, double theta);

  // get distance between two points using Cartesian form
  virtual double Distance(const Polar &other);

  // get object in printable string form
  virtual string ToString() const override;

  // destructor
  virtual ~Polar() {}

 private:
  // private fields: radius and angle
  double r_, theta_;
};

#endif  // _POLAR_H_
