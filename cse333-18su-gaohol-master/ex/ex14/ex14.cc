/*
 * Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ program tests classes of Cartesian and Polar
 * including test of constructor and Distance
 * 
 */
#include <iostream>
#include <cstdlib>
#include "Coordinate.h"
#include "Cartesian.h"
#include "Polar.h"
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307

using namespace std;

int main() {
  // declare two poins in Cartesian Coordinate
  Cartesian pCart1(3, 4);
  Cartesian pCart2(6, 8);

  // testing toString in Cardesian Coordinates
  cout << "======= Testing points in Cardesian Coordinates =======" << endl;
  cout << pCart1.ToString() << endl;
  cout << pCart2.ToString() << endl;
  // testing Distance in Cardesian Coordinates
  cout << "Expected Distance between point1 and point2 is: 5" << endl;
  cout << "Actual Distance between point1 and point2 is: "
                                   << pCart1.Distance(pCart2) << endl;
  cout << "===================== End Testing =====================" << "\n"
                                                                       << endl;
  cout << "======= Testing points in Polar Coordinates =======" << endl;

  // Declare two points in Polar Coordinate
  Polar pPol1(1, PI/3);
  Polar pPol2(2, PI/4);

  // Testing toString in Polar Coordinates
  cout << pPol1.ToString() << endl;
  cout << pPol2.ToString() << endl;
  // testing Distance in Polar Coordinates
  cout << "Expected Distance between point1 and point2 is: 1.06597..." << endl;
  cout << "Actual Distance between point1 and point2 is: "
                                     << pPol2.Distance(pPol1) << "..." << endl;
  cout << "===================== End Testing =====================" << "\n"
                                                                       << endl;
  cout << "All Test Passed!" << endl;
  // return success
  return EXIT_SUCCESS;
}
