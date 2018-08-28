/*
 * Copyright ©2018 Gaohong Liu.  All rights reserved.
 * Name: Gaohong Liu
 * Student#: 15612268
 * Email: gaohol@uw.edu
 *
 * This C program prints the values of the bytes allocated 
 * to some variables in hex.  
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

// declaration of print byteLeng and pData and its address
void DumpHex(void* pData, int byteLen);

int main(int argc, char **argv) {
  char     charVal = '0';
  int32_t  intVal = 1;
  float    floatVal = 1.0;
  double   doubleVal  = 1.0;

  typedef struct {
    char     charVal;
    int32_t  intVal;
    float    floatVal;
    double   doubleVal;
  } Ex2Struct;
  Ex2Struct structVal = { '0', 1, 1.0, 1.0 };

  DumpHex(&charVal, sizeof(char));
  DumpHex(&intVal, sizeof(int32_t));
  DumpHex(&floatVal, sizeof(float));
  DumpHex(&doubleVal, sizeof(double));
  DumpHex(&structVal, sizeof(structVal));

  return EXIT_SUCCESS;
}

// print byteLen in decimal and pData and its address in hex
void DumpHex(void* pData, int byteLen) {
  uint8_t* addr = (uint8_t*)pData;
  printf("The %d bytes startint at %p are: ", byteLen, addr);
  for (uint32_t i = 0; i < byteLen; i++) {
    printf("%02" PRIx8 " ", *(addr+i));
  }
  printf("\n");
}
