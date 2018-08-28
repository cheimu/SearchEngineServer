/*
 * Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ program implements Vector class which has three private
 * fields x, y, z, and Override "+", "-", "*" and "<<" operator
 */

#include <iostream>
using namespace std;
#include "Vector.h"

namespace vector333 {
Vector::Vector() {
  this->arry_ = new float[3];
  if (this->arry_ == nullptr) {
    cerr << "ERROR: Out of Memory!" << endl;
    exit(EXIT_FAILURE);
  }
  this->arry_[0] = 0.0;
  this->arry_[1] = 0.0;
  this->arry_[2] = 0.0;
}

Vector::Vector(const float x, const float y, const float z) {
  this->arry_ = new float[3];
  if (this->arry_ == nullptr) {
    cerr << "ERROR: Out of Memory!" << endl;
    exit(EXIT_FAILURE);
  }
  this->arry_[0] = x;
  this->arry_[1] = y;
  this->arry_[2] = z;
}

Vector::Vector(const Vector& copyme) {
  this->arry_ = new float[3];
  if (this->arry_ == nullptr) {
    cerr << "ERROR: Out of Memory!" << endl;
    exit(EXIT_FAILURE);
  }
  this->arry_[0] = copyme.arry_[0];
  this->arry_[1] = copyme.arry_[1];
  this->arry_[2] = copyme.arry_[2];
}

Vector::~Vector() {
  delete[] this->arry_;
}

Vector& Vector::operator=(const Vector &rhs) {
  // check if input Vector is as same as the object
  if (this != &rhs) {
    // ux = vx
    this->arry_[0] = rhs.arry_[0];
    // uy = vy
    this->arry_[1] = rhs.arry_[1];
    // uz = vz
    this->arry_[2] = rhs.arry_[2];
  }
  return *this;
}

Vector operator+(const Vector& a, const Vector& b) {
  Vector temp = a;
  temp += b;
  return temp;
}

Vector operator-(const Vector& a, const Vector& b) {
  Vector temp = a;
  temp -= b;
  return temp;
}

Vector& Vector::operator+=(const Vector &rhs) {
  // ux += vx
  this->arry_[0] += rhs.arry_[0];
  // uy += vy
  this->arry_[1] += rhs.arry_[1];
  // uz += vz
  this->arry_[2] += rhs.arry_[2];
  return *this;
}

Vector& Vector::operator-=(const Vector &rhs) {
  // ux -= vx
  this->arry_[0] -= rhs.arry_[0];
  // uy -= vy
  this->arry_[1] -= rhs.arry_[1];
  // uz -= vz
  this->arry_[2] -= rhs.arry_[2];
  return *this;
}

float operator*(const Vector &lhs, const Vector &rhs) {
  // ux * vx + uy * vy + uz * vz
  return lhs.arry_[0] * rhs.arry_[0] + lhs.arry_[1] * rhs.arry_[1] +
                                                  lhs.arry_[2] * rhs.arry_[2];
}

Vector operator*(const Vector &lhs, const double coe) {
  Vector temp;
  // ux * coefficient
  temp.arry_[0] = lhs.arry_[0] * coe;
  // uy * coefficient
  temp.arry_[1] = lhs.arry_[1] * coe;
  // uz * coefficient
  temp.arry_[2] = lhs.arry_[2] * coe;
  return temp;
}

Vector operator*(const double coe, const Vector &rhs) {
  Vector temp;
  // ux * coefficient
  temp.arry_[0] = coe * rhs.arry_[0];
  // uy * coefficient
  temp.arry_[1] = coe * rhs.arry_[1];
  // uz * coefficient
  temp.arry_[2] = coe * rhs.arry_[2];
  return temp;
}

ostream& operator<<(ostream &out, const Vector &rhs) {
  // (x,y,z)
  out << "(" << rhs.arry_[0] << "," << rhs.arry_[1]
                                    << "," << rhs.arry_[2] << ")";
  return out;
}
}  // namespace vector333
