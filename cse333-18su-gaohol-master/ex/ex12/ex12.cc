/*
 * Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ program prompts the user to type in N doubles(10 in this case), 
 * reads those doubles into a std::vector of doubles,
 * sorts the vector using std::sort, and then prints out the sorted vector.
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define NUM 10
using namespace std;

// declaration of helper function which read the input parameters.
template <class T> T ReadValue(istream& in);

int main(int argc, char** argv) {
  cout << "Input " << NUM << " doubles: " << endl;
  vector<double> v(NUM);
  // read doubles
  for (int i = 0; i < NUM; i++) {
    v[i] = ReadValue<double>(cin);
  }
  // sort
  sort(v.begin(), v.end());
  cout << "Your sorted doubles are: " << endl;
  // print doubles out in sorted order
  for (int i = 0; i < NUM; i++) {
    cout << v[i] << endl;
  }
  return EXIT_SUCCESS;  // return success
}

template <class T> T ReadValue(istream& in) {
  T val;
  // check if input stream works correctly
  if (!in.good()) {
    cerr << "Read Failed" << endl;
    exit(EXIT_FAILURE);  // return failure
  }
  // check if conversion works correctly
  if (!(in >> val)) {
    cerr << "Conversion Failed" << endl;
    exit(EXIT_FAILURE);  // return failure
  }
  // return input value
  return val;
}
