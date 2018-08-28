/*
 * Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ program originally had 5 memory leaks and use normal pointer,
 * and now it has been fixed using unique_ptr instead
 * 
 */


#include <cmath>
#include <sstream>
#include "Polar.h"
using namespace std;

Polar::Polar(double r, double theta) {
  r_ = r;
  theta_ = theta;
}

double Polar::Distance(const Polar &other) {
  // sqrt( (r1cos(theta)-r2cos(theta))^2 + (r1sin(theta)-r2sin(theta))^2 )
  return sqrt(pow((r_ * cos(theta_)- other.r_ * cos(other. theta_)), 2)
                 + pow((r_ * sin(theta_)- other.r_ * sin(other. theta_)), 2));
}

string Polar::ToString() const {
  stringstream s;
  // (r, theta)
  s << "The point in Polar Coordinate is : (" << r_ << ", " << theta_ << ")";
  return s.str();
}
