/*
 * Copyright ©2018 Gaohong Liu.  All rights reserved.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C program reads the file, copies the contents of the file to 
 * stdout in reverse order. It takes the address of the given file 
 * or the file name which is in the same directory with this c program as input
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

// declaration of function to exit when meet an error
void Usage(char* reason);

int main(int argc, char** argv) {
  // if number of input arguments is not two, then print error and exit
  if (argc != 2) {
    Usage("Input");
  }
  // open file and read it in unit of byte
  FILE* fin = fopen(argv[1], "rb");
  // if file open failed, then print error and exit
  if (fin == NULL) {
    Usage("Open File");
  }
  // set cursor to the end to get the file size
  // if failed, then print error and exit
  if (fseek(fin, 0, SEEK_END) != 0) {
    Usage("Set Cursor");
  }
  uint64_t size = ftell(fin);
  // if ftell failed to work and did not get size back,
  // then print error and exit
  if (size == -1) {
    Usage("Get File Size");
  }
  // read file byte by byte and print it reversely
  int64_t i;
  char ReadChar;
  for (i = size - 1; i >= 0; i--) {
    // set cursor to current reading position and if failed to set,
    // then print error and exit
    if (fseek(fin, i, SEEK_SET) != 0) {
      Usage("Set Cursor");
    }
    // read file byte by byte and if failed to set, then print error and exit
    if (fread(&ReadChar, 1, sizeof(ReadChar), fin) != 1) {
      Usage("Read File");
    }
    printf("%c", ReadChar);
  }
  // close the file
  fclose(fin);
  return EXIT_SUCCESS;  // return success
}

// print out the usage of the program and exit when meet an error
void Usage(char* reason) {
  fprintf(stderr, "Usage: %s failed! ./ex6 filename\n", reason);
  exit(EXIT_FAILURE);  // exit failure
}
