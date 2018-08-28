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
  // Override "+"
  // ux + vx, uy + vy, uz + vz
  Vector operator+(const Vector& other);
  // Override "-"
  // ux - vx, uy - vy, uz - vz
  Vector operator-(const Vector& other);
  // Override "+="
  // ux = ux + vx, uy = uy + vy, uz = uz + vz
  Vector& operator+=(const Vector &rhs);
  // Override "-="
  // ux = ux - vx, uy = uy - vy, uz = uz - vz
  Vector& operator-=(const Vector &rhs);
  // Override "*"
  // ux * vx + uy * vy + uz * vz
  float operator*(const Vector& other);
  // Override "*"
  // ux = ux * coe, uy = uy * coe, uz = uz * coe
  Vector operator*(const double coe);
  // Override "*"
  // ux = ux * coe, uy = uy * coe, uz = uz * coe
  friend Vector operator*(const double coe, const Vector &rhs);
  // Override "<<"
  // print vector as (x,y,z) to stdout
  friend ostream & operator<<(ostream &out, const Vector &rhs);

 private:
  // Member variables x_, y_, z_.
  float x_;
  float y_;
  float z_;
};  // class Vector

}  // namespace vector333

#endif  // _VECTOR_H_

