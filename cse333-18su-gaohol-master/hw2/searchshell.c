/*
 * Copyright ©2018 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Summer Quarter 2018 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600

#define SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "memindex.h"
#include "filecrawler.h"

static void CrawFiles(MemIndex* memIndexPtr,
                                  DocTable* docTablePtr, char* dir);
static void Split(char** bufPtr, MemIndex* memIndexPtr,
                                  LinkedList* docListPtr);
static void Print(DocTable* docTablePtr, LinkedList* docListPtr);
static void Usage(void);


int main(int argc, char **argv) {
  if (argc != 2)
    Usage();

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - crawl from a directory provided by argv[1] to produce and index
  //  - prompt the user for a query and read the query from stdin, in a loop
  //  - split a query into words (check out strtok_r)
  //  - process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.
  DocTable docTable;
  MemIndex memIndex;
  char* buffer = (char*) malloc(sizeof(char) * SIZE);
  char* rootDir = argv[1];
  // crawl from a directory provided by argv[1] to produce and index
  CrawFiles(&memIndex, &docTable, rootDir);
  Verify333(docTable != NULL);
  Verify333(memIndex != NULL);
  // prompt the user for a query and read the query from stdin, in a loop
  printf("enter query:\n");
  while (fgets(buffer, SIZE, stdin) != NULL) {
    buffer[strlen(buffer) - 1] = '\0';
    LinkedList docList;
    // split a query into words
    Split(&buffer, &memIndex, &docList);
    if (docList != NULL) {
      // process a query against the index and print out the results
      Print(&docTable, &docList);
      FreeLinkedList(docList, &free);
    }
    printf("enter query:\n");
  }
  printf("Search finished...\n");
  printf("Good Bye...\n");
  // free the allocate space
  free(buffer);
  FreeDocTable(docTable);
  FreeMemIndex(memIndex);
  return EXIT_SUCCESS;
}

static void CrawFiles(MemIndex* memIndexPtr, DocTable* docTablePtr, char* dir) {
  printf("Indexing \'%s\'\n", dir);
  int res = CrawlFileTree(dir, docTablePtr, memIndexPtr);
  if (res == 0) {
    Usage();
  }
}

static void Split(char** bufPtr, MemIndex* memIndexPtr,
                                                    LinkedList* docListPtr) {
  char** query = (char**) malloc(sizeof(char*) * SIZE);
  Verify333(query != NULL);
  char* splitPtr;
  int queryLen = 0;
  // split the input into tokens
  char* token = strtok_r(*bufPtr, " ", &splitPtr);
  // add tokens into query
  while (token != NULL) {
    query[queryLen] = token;
    queryLen++;
    token = strtok_r(NULL, " ", &splitPtr);
  }
  // search documents that contains words inside of query
  *docListPtr = MIProcessQuery(*memIndexPtr, query, queryLen);
  free(query);
}

static void Print(DocTable* docTablePtr, LinkedList* docListPtr) {
  LLIter lliter = LLMakeIterator(*docListPtr, 0);
  Verify333(lliter != NULL);
  SearchResult* document;
  DocID_t id;
  HWSize_t rank;
  char* name;
  // iterate through all the matching documents and printo out the
  // documents' names and ranks
  while (LLIteratorHasNext(lliter)) {
    LLIteratorGetPayload(lliter, (LLPayload_t*)&document);
    id = document->docid;
    rank = document->rank;
    name = DTLookupDocID(*docTablePtr, id);
    printf("  %s (%u)\n", name, rank);
    LLIteratorNext(lliter);
  }
  // deal with the last documents inside of linkedlist
  LLIteratorGetPayload(lliter, (LLPayload_t*)&document);
  id = document->docid;
  rank = document->rank;
  name = DTLookupDocID(*docTablePtr, id);
  printf("  %s (%u)\n", name, rank);
  LLIteratorFree(lliter);
}

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}

