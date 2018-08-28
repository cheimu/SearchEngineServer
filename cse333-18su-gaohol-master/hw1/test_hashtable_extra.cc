extern "C" {
  #include "./CSE333.h"
  #include "./HashTable.h"
  #include "./HashTable_priv.h"
  #include "./LinkedList.h"
  #include "./LinkedList_priv.h"
}
#include "./test_suite.h"
#include "./test_hashtable_extra.h"
#include <stdio.h>
#include <stdlib.h>
namespace hw1 {
// our payload structure
// our payload structure
typedef struct payload_st {
  int magic_num;
  int payload_num;
} Payload;

TEST_F(Test_HashTable_Extra, TestFNVHash64) {
  for (uint64_t i = 0; i < 100; i++) {
     ASSERT_TRUE(FNVHashInt64((HTValue_t)100) < UINT64_MAX);
  }
}

TEST_F(Test_HashTable_Extra, TestAllocZero) {
  // simple create / delete test
  HashTable ht = AllocateHashTable(0);
  ASSERT_EQ(NULL, ht);
}



}
