/*
 * Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ program instantiates instances of Vector tests all three ways
 * constructor and test all arithmetics operation of vector "+" "-" "+="
 * "-=" "*" and "<<"
 */
#include <iostream>
#include "Vector.h"
using namespace std;
using namespace vector333;

int main(int argc, char** argv) {
  // test constructor
  Vector vDefault;
  cout << "Default should be (0,0,0), and now is " << vDefault << endl;
  Vector vNormal(3.33, 33.3, 333);
  cout << "vector should be (3,33,33,3,333), and now is " << vNormal << endl;
  Vector vCopy(vNormal);
  cout << "vector should be (3,33,33,3,333), and now is " << vCopy << endl;
  // test assignment
  Vector vAssign(1, 2, 3);
  vAssign = vNormal;
  cout << "vector should be (3,33,33,3,333), and now is " << vAssign << endl;
  Vector vChain(4, 5, 6);
  vNormal = vDefault = vChain;
  cout << "vector chain should be (4,5,6), (4,5,6), (4,5,6) and now are "
                        << vNormal << " " << vDefault << " " << vChain << endl;
  // test arithmetics
  Vector a(1, 2, 3);
  Vector b(4, 5, 6);
  Vector c(7, 8, 9);
  Vector d(10, 11, 12);
  float coe = 2;
  Vector testAdd = a + b;
  Vector testSub = a - b;
  a += b;
  c -= b;
  Vector coeVector = d * coe;
  Vector vectorCoe = coe * d;
  float testDotProduct = d * b;
  cout << "(1,2,3) + (4,5,6) = " << testAdd << endl;
  cout << "(1,2,3) - (4,5,6) = " << testSub << endl;
  cout << "(1,2,3) += (4,5,6) = " << a << endl;
  cout << "(7,8,9) -= (4,5,6) = " << c << endl;
  cout << "(10,11,12) * 2 = " << coeVector << endl;
  cout << "2 * (10,11,12) = " << vectorCoe << endl;
  cout << "(10,11,12) * (4,5,6) = " << testDotProduct << endl;
  return EXIT_SUCCESS;
}
