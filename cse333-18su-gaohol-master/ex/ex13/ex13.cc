/*
 * Revised Version Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ program originally had 5 memory leaks and use normal pointer,
 * and now it has been fixed using unique_ptr instead.
 *
 * Copyright ©2018 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Summer Quarter 2018 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <algorithm>  // for sort
#include <cstdlib>    // for EXIT_SUCCESS and EXIT_FAILURE
#include <iostream>   // for cout
#include <vector>     // for vector type
#include <memory>     // for unique_ptr

using std::unique_ptr;  // unique pointer

int main(int argc, char **argv) {
  // Allocate an integer on the heap, initialize to value 5.
  // leak #1, using unique_ptr instead
  unique_ptr<int> x(new int(5));
  std::cout << "*x is: " << *x << std::endl;

  // Allocate a vector of integers on the heap, add some values to
  // that vector, sort the vector, print the values.
  // leak #2, using nuique_ptr instead
  unique_ptr<std::vector<int>> v(new std::vector<int>);
  v->push_back(13);
  v->push_back(42);
  v->push_back(17);
  std::sort(v->begin(), v->end());
  std::cout << "sorted v: ";
  for (int &el : *v) {
    std::cout << el << " ";
  }
  std::cout << std::endl;

  // Allocate a vector of (integer pointers) on the stack, add some
  // values to the vector from the heap, print the values.
  // leak #3, 4, and 5, using nuique_ptr instead
  std::vector<unique_ptr<int>> v2;
  v2.push_back(unique_ptr<int>(new int(13)));
  v2.push_back(unique_ptr<int>(new int(42)));
  v2.push_back(unique_ptr<int>(new int(17)));
  std::cout << "unsorted v2: ";
  // because v2 is unique_ptr now, using auto to simply complicated return type.
  for (auto &el : v2) {
    std::cout << *el << " ";
  }
  std::cout << std::endl;
  return EXIT_SUCCESS;  // return success
}
