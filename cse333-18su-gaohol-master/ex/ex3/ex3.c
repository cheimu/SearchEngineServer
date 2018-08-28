/*
 * Copyright ©2018 Gaohong Liu.  All rights reserved.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C program creates a 3D point data structure which contains
 * three int16_t x, y, z and frees it at the end of the program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

// define data structure of 3d point
typedef struct Point3d {
  int16_t x;
  int16_t y;
  int16_t z;
} Point3d;

// declaration of allocate 3d point function
Point3d* AllocatePoint3d(int16_t x, int16_t y, int16_t z);

int main(int argc, char **argv) {
  int16_t x = 100;
  int16_t y = 789;
  int16_t z = 111;
  // create a 3d point
  Point3d* point = AllocatePoint3d(x, y, z);
  // test if malloc failed
  if (point == NULL) {
    printf("Out Of Memory \n");
    return EXIT_FAILURE;  // return failure;
  }
  // test if assign of each field failed
  if (point->x != 100 || point->y != 789 || point->z != 111) {
    printf("Allocate Failed \n");
    return EXIT_FAILURE;  // return failure
  }
  printf("Test Passed \n");
  // free the allocate memory
  free(point);
  return EXIT_SUCCESS;  // return success
}

// create a 3d point which takes x, y, z as three fields and return
// created 3d point
Point3d* AllocatePoint3d(int16_t x, int16_t y, int16_t z) {
  // request memory for 3d point
  Point3d* point = (Point3d*)malloc(sizeof(Point3d));
  // test if malloc failed
  if (point == NULL) {
    exit(EXIT_FAILURE);  // return failed
  }
  point->x = x;
  point->y = y;
  point->z = z;
  // return created 3d point
  return point;
}


