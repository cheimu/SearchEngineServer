/*
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C program tests whether or not the char and array of floats
 * behave as if they are passed by reference or by value 
 */
#include <stdio.h>
#include <stdlib.h>

// declaration of test function
void testChar(char test);
void testArray(float test[]);

int main(int argc, char** argv) {
  // create consponding test char and floating array
  char test_c = '0';
  float test_f[3] = {0.0, 1.0, 2.0};

  // call test char function to change char value
  testChar(test_c);
  if (test_c == '0') {
     printf("char: pass-by-value\n");
  } else {
     printf("char: pass-by-reference\n");
  }

  // call test floats array function to change floats value
  testArray(test_f);
  if (test_f[0] == 0.0) {
     printf("array of floats: pass-by-value\n");
  } else {
     printf("array of floats: pass-by-reference\n");
  }
  return 0;  // success
}

// change the value of char passed in
void testChar(char test) {
  test++;
}

// change the value of float array passed in
void testArray(float test[]) {
  test++;
}

