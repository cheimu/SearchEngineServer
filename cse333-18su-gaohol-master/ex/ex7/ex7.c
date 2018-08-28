/*
 * Copyright ©2018 Gaohong Liu and cse333-staff.  All rights reserved.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C program accepts a directory name as a command-line argument  
 * scans through the directory looking for filenames that end in .txt
 * and reads the contents of those files to stdout
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

#define SIZE 1024
// declaration of function to exit when meet an error
void Usage(char* reason);
// declaration of function to create full file address
char* getFullAddr(char* directory, char* file);
// declaration of function to print the file contents out to stdout
void print(char* directory);

int main(int argc, char** argv) {
  // if number of input arguments is not two, then print error and exit
  if (argc != 2) {
    Usage("Input");
  }
  char* dir = argv[1];
  // open given directory
  DIR* addr = opendir(dir);
  // if file open failed, then print error and exit
  if (addr == NULL) {
    Usage("Open Given Directory");
  }
  struct dirent* CurDirEntry;
  // get the first file in current directory
  CurDirEntry = readdir(addr);
  while (CurDirEntry) {
    // get file name length
    int64_t len = strlen(CurDirEntry->d_name);
    // if file name ends with .txt, get the full address and print contents out
    if ((len >= 4) && (strcmp(CurDirEntry->d_name + (len - 4), ".txt") == 0)) {
      char* fileInfo = getFullAddr(dir, CurDirEntry->d_name);
      print(fileInfo);
      // free
      free(fileInfo);
    }
    // get next file in current directory
    CurDirEntry = readdir(addr);
  }
  // close the directory
  closedir(addr);
  return EXIT_SUCCESS;  // return success
}

// get current directory and file name and combine them to full address
// which could be use by open() function
char* getFullAddr(char *directory, char *file) {
  int64_t totalLength = strlen(directory) + strlen(file) + 2;
  char* fileInfo = (char *) malloc(sizeof(char) * totalLength);
  // test if succeed to allocate memory
  if (fileInfo == NULL) {
    Usage("Memory Allocation");
  }
  // create string containing full address
  snprintf(fileInfo, totalLength, "%s/%s", directory, file);
  return fileInfo;
}

// credit to cse333-staff
// use open to read the whole file and print to stdout
void print(char* fileInfo) {
  int fd = open(fileInfo, O_RDONLY);
  // test if succeed to open the file
  if (fd == -1) {
    Usage("Open File");
  }
  char buf[SIZE];
  ssize_t len;
  // continue reading file
  do {
    len = read(fd, buf, SIZE);
    if (len == -1) {
      if (errno != EINTR) {
        close(fd);
        Usage("Read File");
      }
      continue;
    }
    size_t total = 0;
    ssize_t wlen;
    while (total < len) {
      wlen = write(1, buf + total, len - total);
      if (wlen == -1) {
        if (errno != EINTR) {
          close(fd);
          Usage("Write File");
        }
        continue;
      }
      total += wlen;
    }
  } while (len > 0);
  // close the file
  close(fd);
}
// print out the usage of the program and exit when meet an error
void Usage(char* reason) {
  fprintf(stderr, "Usage: %s failed! ./ex6 filename\n", reason);
  exit(EXIT_FAILURE);  // exit failure
}
