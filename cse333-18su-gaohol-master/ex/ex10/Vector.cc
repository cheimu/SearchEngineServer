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
Vector::Vector()
  : x_(0), y_(0), z_(0) {}

Vector::Vector(const float x, const float y, const float z)
  : x_(x), y_(y), z_(z) {}

Vector::Vector(const Vector& copyme)
  : x_(copyme.x_), y_(copyme.y_), z_(copyme.z_) {}

Vector::~Vector() {}

Vector& Vector::operator=(const Vector &rhs) {
  // check if input Vector is as same as the object
  if (this != &rhs) {
    // ux = vx
    this->x_ = rhs.x_;
    // uy = vy
    this->y_ = rhs.y_;
    // uz = vz
    this->z_ = rhs.z_;
  }
  return *this;
}

Vector Vector::operator+(const Vector &other) {
  Vector temp;
  // ux + vx
  temp.x_ = this->x_ + other.x_;
  // uy + vy
  temp.y_ = this->y_ + other.y_;
  // uz + vz
  temp.z_ = this->z_ + other.z_;
  return temp;
}

Vector Vector::operator-(const Vector &other) {
  Vector temp;
  // ux - vx
  temp.x_ = this->x_ - other.x_;
  // uy - vy
  temp.y_ = this->y_ - other.y_;
  // uz - vz
  temp.z_ = this->z_ - other.z_;
  return temp;
}

Vector& Vector::operator+=(const Vector &rhs) {
  // ux += vx
  this->x_ += rhs.x_;
  // uy += vy
  this->y_ += rhs.y_;
  // uz += vz
  this->z_ += rhs.z_;
  return *this;
}

Vector& Vector::operator-=(const Vector &rhs) {
  // ux -= vx
  this->x_ -= rhs.x_;
  // uy -= vy
  this->y_ -= rhs.y_;
  // uz -= vz
  this->z_ -= rhs.z_;
  return *this;
}

float Vector::operator*(const Vector &other) {
  // ux * vx + uy * vy + uz * vz
  return this->x_ * other.x_ + this->y_ * other.y_ + this->z_ * other.z_;
}

Vector Vector::operator*(const double coe) {
  Vector temp;
  // ux * coefficient
  temp.x_ = this->x_ * coe;
  // uy * coefficient
  temp.y_ = this->y_ * coe;
  // uz * coefficient
  temp.z_ = this->z_ * coe;
  return temp;
}

Vector operator*(const double coe, const Vector &rhs) {
  Vector temp;
  // coefficient * ux
  temp.x_ = rhs.x_ * coe;
  // coefficient * uy
  temp.y_ = rhs.y_ * coe;
  // coefficient * uz
  temp.z_ = rhs.z_ * coe;
  return temp;
}

ostream& operator<<(ostream &out, const Vector &rhs) {
  // (x,y,z)
  out << "(" << rhs.x_ << "," << rhs.y_ << "," << rhs.z_ << ")";
  return out;
}

}  // namespace vector333
