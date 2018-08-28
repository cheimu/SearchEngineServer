/*
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu

 * This C program accepts a user input integer n, estimates π by adding 
 * n terms of the Nilakantha series together and prints out this estimate 
 * to 20 decimal places.
 */
#include <stdio.h>
#include <stdlib.h>

#define PRECISION 20  // set the precision to 20 decimal places
int main(int argc, char** argv) {
  // check the number of arguments is 2
  if (argc != 2) {
    printf("Incorrect number of arguments.\n");
    return 1;  // failure
  }

  // set the character pointer to the start of user input string
  char* itr = argv[1];

  // loop through each character and check it is a number between 0 and 9
  while (*itr != '\0') {
    if (*itr < '0' || *itr > '9') {
      printf("Invalid argument.\n");
      return 1;  // failure
    }
    itr++;  // move the pointer to the next character
  }

  // convert string to integer
  int n =atoi(argv[1]);
  double pi = 3;

  for (int i = 1; i <= n; i++) {
    double temp = 4.0 / (2 * i * (2 * i + 1) * (2 * i + 2));
    if ((i + 1) % 2 == 0) {
      pi += temp;
    } else {
      pi += temp * -1.0;
    }
  }
  printf("Our estimate of Pi is %.*lf\n", PRECISION, pi);
  return 0;  // success
}
