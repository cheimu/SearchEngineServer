/*
 * Copyright ©2018 Gaohong Liu and cse333-staff.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ header file declares IntPair class which contains two private 
 * fields x and y, and two methods Get and Set which can get and set two 
 * integers inside of object IntPair
 */

#ifndef _INT_PAIR_
#define _INT_PAIR_

class IntPair {
 public:
    // construct object IntPair with x and y
    IntPair(const int x, const int y);
    // return two integers of IntPair through parameter (pointer not reference)
    void Get(int* x, int* y);
    // sets the two integers of IntPair
    void Set(const int x, const int y);

 private:
    // private field of IntPair
    // integer x_
    int x_;
    // integer y_
    int y_;
};

#endif  // _INT_PAIR_
