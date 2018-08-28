/*
 * Name: Gaohong Liu
 * Student#: 15612268
 * Email: gaohol@uw.edu
 * 
 * This C program accepts two arrays of int64_t's, and an array 
 * length, copy the source array to destination array, and sort it 
 * in non-descreasing sorted order
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

// declaration of copy and sort
void CopyAndSort(int64_t src[], int64_t dst[], uint32_t size);
// declaration of insertion sort
void insertionSort(int64_t pivot, int64_t dst[], uint32_t len);
// declaration of print all the elements in the array
void printArray(int64_t src[], int64_t dst[], uint32_t size);

int main(int argc, char** argv) {
  uint32_t size = 11;
  int64_t src[11] = {3, 2, -5, 7, 13, 4, 1, 7, 8, -8, 6};
  int64_t dst[11];
  CopyAndSort(src, dst, size);
  return EXIT_SUCCESS;  // exit success
}

// copy the src array to dst array and sort it non-decreasingly
void CopyAndSort(int64_t src[], int64_t dst[], uint32_t size) {
  // check if size is zero, if zero, do nothing
  if (size == 0) {
     return;
  }
  // if size is larger or equal to one, put first element into sort
  dst[0] = src[0];
  // To speed up, if size is equal to one, then directly return,
  // otherwise iterate all the elements
  if (size > 1) {
    // iterate all the elements in src and sort
    for (uint32_t i = 1; i < size; i++) {
       insertionSort(src[i], dst, i);
    }
  }
  printArray(src, dst, size);
}

// run insertion sort
void insertionSort(int64_t pivot, int64_t dst[], uint32_t len) {
  uint32_t cur = len;
  // compare each element from back to the front, if current
  // element is larger that pivot, then copy it to the next position
  // until current element is smaller or equal to pivot, then stop
  while (cur > 0 && dst[cur-1] > pivot) {
     dst[cur] = dst[cur-1];
     cur--;
  }
  // put pivot into dst that cursor pointed.
  dst[cur] = pivot;
}

// print array to terminal
void printArray(int64_t src[], int64_t dst[], uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
     printf("%" PRId64 " ", dst[i]);
  }
  printf("\n");
}


