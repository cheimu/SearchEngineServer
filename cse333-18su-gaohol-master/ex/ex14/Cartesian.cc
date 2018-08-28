/*
 * Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ program Implements class Cartesian including ToString, and also
 * Distance which calculates the distance between two Cartesian points
 * passed by reference as an argument.
 */

#include <cmath>
#include <string>
#include <sstream>
#include "Cartesian.h"

using namespace std;

Cartesian::Cartesian(double x, double y) {
  x_ = x;
  y_ = y;
}

double Cartesian::Distance(const Cartesian &other) {
  // sqrt( (x1-x2)^2 + (y1-y2)^2 )
  return sqrt(pow((x_- other.x_), 2) + pow((y_- other.y_), 2));
}

string Cartesian::ToString() const {
  stringstream s;
  // (x, y)
  s << "The point in Cartesian Coordinate is : (" << x_ << ", " << y_ << ")";
  return s.str();
}
