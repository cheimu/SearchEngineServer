/*
 * Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ header file declares Vector class inside namespace of vector333 
 * which three private fields of float x, y, z, and overide "+", "-", "*" 
 * and "<<".
 */
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
using namespace std;
namespace vector333 {

class Vector {
  // Style tip: always put your public members before private members.
 public:
  Vector();                                             // Default construction
  Vector(const float x, const float y, const float z);  // Constructor
  Vector(const Vector& copyme);                         // Copy constructor
  ~Vector();                                            // Destructor

  // Override the "+", "-", "=", "+=", "-=", "*" and "<<" operators.
  // Override "="
  // u = v
  Vector& operator=(const Vector& rhs);
  // Override "+="
  // ux = ux + vx, uy = uy + vy, uz = uz + vz
  Vector& operator+=(const Vector &rhs);
  // Override "-="
  // ux = ux - vx, uy = uy - vy, uz = uz - vz
  Vector& operator-=(const Vector &rhs);
  // Override "*"
  // ux * vx + uy * vy + uz * vz
  friend float operator*(const Vector &lhs, const Vector &rhs);
  // Override "*"
  // ux = ux * coe, uy = uy * coe, uz = uz * coe
  friend Vector operator*(const Vector &lhs, const double coe);
  // Override "*"
  // ux = ux * coe, uy = uy * coe, uz = uz * coe
  friend Vector operator*(const double coe, const Vector &rhs);
  // Override "<<"
  // print vector as (x,y,z) to stdout
  friend ostream & operator<<(ostream &out, const Vector &rhs);

 private:
  // Member variables arry_ of float.
  float* arry_;
};  // class Vector

// Override "+"
// ux + vx, uy + vy, uz + vz
Vector operator+(const Vector& a, const Vector& b);
// Override "-"
// ux - vx, uy - vy, uz - vz
Vector operator-(const Vector& a, const Vector& b);
}  // namespace vector333

#endif  // _VECTOR_H_

