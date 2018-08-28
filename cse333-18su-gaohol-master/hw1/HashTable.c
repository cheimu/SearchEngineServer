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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "CSE333.h"
#include "HashTable.h"
#include "HashTable_priv.h"

// A private utility function to grow the hashtable (increase
// the number of buckets) if its load factor has become too high.
static void ResizeHashtable(HashTable ht);

// a free function that does nothing
static void LLNullFree(LLPayload_t freeme) { }
static void HTNullFree(HTValue_t freeme) { }

// local helper function to detect if current hashtable contains given key
static bool HasKey(LLIter ll, HTKey_t key, HTKeyValuePtr* payload);
HashTable AllocateHashTable(HWSize_t num_buckets) {
  HashTable ht;
  HWSize_t  i;

  // defensive programming
  if (num_buckets == 0) {
    return NULL;
  }

  // allocate the hash table record
  ht = (HashTable) malloc(sizeof(HashTableRecord));
  if (ht == NULL) {
    return NULL;
  }

  // initialize the record
  ht->num_buckets = num_buckets;
  ht->num_elements = 0;
  ht->buckets =
    (LinkedList *) malloc(num_buckets * sizeof(LinkedList));
  if (ht->buckets == NULL) {
    // make sure we don't leak!
    free(ht);
    return NULL;
  }
  for (i = 0; i < num_buckets; i++) {
    ht->buckets[i] = AllocateLinkedList();
    if (ht->buckets[i] == NULL) {
      // allocating one of our bucket chain lists failed,
      // so we need to free everything we allocated so far
      // before returning NULL to indicate failure.  Since
      // we know the chains are empty, we'll pass in a
      // free function pointer that does nothing; it should
      // never be called.
      HWSize_t j;
      for (j = 0; j < i; j++) {
        FreeLinkedList(ht->buckets[j], LLNullFree);
      }
      free(ht->buckets);
      free(ht);
      return NULL;
    }
  }

  return (HashTable) ht;
}

void FreeHashTable(HashTable table,
                   ValueFreeFnPtr value_free_function) {
  HWSize_t i;

  Verify333(table != NULL);  // be defensive

  // loop through and free the chains on each bucket
  for (i = 0; i < table->num_buckets; i++) {
    LinkedList  bl = table->buckets[i];
    HTKeyValue *nextKV;

    // pop elements off the the chain list, then free the list
    while (NumElementsInLinkedList(bl) > 0) {
      Verify333(PopLinkedList(bl, (LLPayload_t*)&nextKV));
      value_free_function(nextKV->value);
      free(nextKV);
    }
    // the chain list is empty, so we can pass in the
    // null free function to FreeLinkedList.
    FreeLinkedList(bl, LLNullFree);
  }

  // free the bucket array within the table record,
  // then free the table record itself.
  free(table->buckets);
  free(table);
}

HWSize_t NumElementsInHashTable(HashTable table) {
  Verify333(table != NULL);
  return table->num_elements;
}

HTKey_t FNVHash64(unsigned char *buffer, HWSize_t len) {
  // This code is adapted from code by Landon Curt Noll
  // and Bonelli Nicola:
  //
  // http://code.google.com/p/nicola-bonelli-repo/
  static const uint64_t FNV1_64_INIT = 0xcbf29ce484222325ULL;
  static const uint64_t FNV_64_PRIME = 0x100000001b3ULL;
  unsigned char *bp = (unsigned char *) buffer;
  unsigned char *be = bp + len;
  uint64_t hval = FNV1_64_INIT;

  /*
   * FNV-1a hash each octet of the buffer
   */
  while (bp < be) {
    /* xor the bottom with the current octet */
    hval ^= (uint64_t) * bp++;
    /* multiply by the 64 bit FNV magic prime mod 2^64 */
    hval *= FNV_64_PRIME;
  }
  /* return our new hash value */
  return hval;
}

HTKey_t FNVHashInt64(HTValue_t hashval) {
  unsigned char buf[8];
  int i;
  uint64_t hashme = (uint64_t)hashval;

  for (i = 0; i < 8; i++) {
    buf[i] = (unsigned char) (hashme & 0x00000000000000FFULL);
    hashme >>= 8;
  }
  return FNVHash64(buf, 8);
}

HWSize_t HashKeyToBucketNum(HashTable ht, HTKey_t key) {
  return key % ht->num_buckets;
}


int InsertHashTable(HashTable table,
                    HTKeyValue newkeyvalue,
                    HTKeyValue *oldkeyvalue) {
  HWSize_t insertbucket;
  LinkedList insertchain;

  Verify333(table != NULL);
  ResizeHashtable(table);

  // calculate which bucket we're inserting into,
  // grab its linked list chain
  insertbucket = HashKeyToBucketNum(table, newkeyvalue.key);
  insertchain = table->buckets[insertbucket];

  // Step 1 -- finish the implementation of InsertHashTable.
  // This is a fairly complex task, so you might decide you want
  // to define/implement a helper function that helps you find
  // and optionally remove a key within a chain, rather than putting
  // all that logic inside here.  You might also find that your helper
  // can be reused in steps 2 and 3.
  // allocate memory for new payload to be stored
  HTKeyValuePtr newpayload = (HTKeyValuePtr) malloc(sizeof(HTKeyValue));
  // if allocate failed, return false;
  if (newpayload == NULL) {
    return 0;
  }
  newpayload->key = newkeyvalue.key;
  newpayload->value = newkeyvalue.value;
  // check if current buckect has 0 payload, if so, then directly
  // push new payload into current bucket
  if (NumElementsInLinkedList(insertchain) == 0) {
    if (!PushLinkedList(insertchain, (LLPayload_t)newpayload)) {
      free(newpayload);
      return 0;
    }
    table->num_elements++;
    return 1;  // return success
  }
  LLIter lliter = LLMakeIterator(insertchain, 0UL);
  // check if iterator is null
  if (lliter == NULL) {
    free(newpayload);
    return 0;
  }
  HTKeyValuePtr oldpayload;
  HWSize_t result;
  // check if current bucket has given key, if it has given key, then get
  // the old key value, detele it, and return 2
  if (HasKey(lliter, newkeyvalue.key, &oldpayload)) {
    oldkeyvalue->key = oldpayload->key;
    oldkeyvalue->value = oldpayload->value;
    free(oldpayload);
    LLIteratorDelete(lliter, &LLNullFree);
    result = 2;
  } else {
    // if not return 1
    table->num_elements++;
    result = 1;
  }
  // append this payload into bucket and if failed, return 0
  if (!AppendLinkedList(insertchain, (LLPayload_t)newpayload)) {
    free(newpayload);
    LLIteratorFree(lliter);
    return 0;
  }
  // free the iterator
  LLIteratorFree(lliter);
  return result;
}

int LookupHashTable(HashTable table,
                    HTKey_t key,
                    HTKeyValue *keyvalue) {
  Verify333(table != NULL);
  HWSize_t lookupbucket;
  LinkedList lookupchain;
  // Step 2 -- implement LookupHashTable.
  lookupbucket = HashKeyToBucketNum(table, key);
  lookupchain = table->buckets[lookupbucket];
  // check if current buckect has 0 payload, if so, then directly return 0
  if (NumElementsInLinkedList(lookupchain) == 0) {
    return 0;
  }
  HTKeyValuePtr oldpayload;
  LLIter lliter = LLMakeIterator(lookupchain, 0UL);
  // check if failed to create iterator
  if (lliter == NULL) {
    return -1;  // return false
  }
  // if current bukecet has given then, return get corresponding key and value
  if (HasKey(lliter, key, &oldpayload)) {
    keyvalue->key = oldpayload->key;
    keyvalue->value = oldpayload->value;
    LLIteratorFree(lliter);
    return 1;  // return 1 if key is found
  }
  LLIteratorFree(lliter);
  // return 0 if key is not found
  return 0;
}

int RemoveFromHashTable(HashTable table,
                        HTKey_t key,
                        HTKeyValue *keyvalue) {
  Verify333(table != NULL);
  HWSize_t removebucket;
  LinkedList removechain;
  // Step 3 -- implement RemoveFromHashTable.
  removebucket = HashKeyToBucketNum(table, key);
  removechain = table->buckets[removebucket];
  // check if current buckect has 0 payload, if so, then directly return 0
  if (NumElementsInLinkedList(removechain) == 0) {
    return 0;
  }
  LLIter lliter = LLMakeIterator(removechain, 0UL);
  // check if failed to create iterator
  if (lliter == NULL) {
    return -1;
  }
  HTKeyValuePtr oldpayload;
  // if current bukecet has given then, return get corresponding key and value
  // delete them, free iterator and return 1
  if (HasKey(lliter, key, &oldpayload)) {
    keyvalue->key = oldpayload->key;
    keyvalue->value = oldpayload->value;
    free(oldpayload);
    table->num_elements--;
    LLIteratorDelete(lliter, &LLNullFree);
    LLIteratorFree(lliter);
    return 1;
  }
  // free iterator and return 0 if key is not found
  LLIteratorFree(lliter);
  return 0;
}


HTIter HashTableMakeIterator(HashTable table) {
  HTIterRecord *iter;
  HWSize_t      i;

  Verify333(table != NULL);  // be defensive

  // malloc the iterator
  iter = (HTIterRecord *) malloc(sizeof(HTIterRecord));
  if (iter == NULL) {
    return NULL;
  }

  // if the hash table is empty, the iterator is immediately invalid,
  // since it can't point to anything.
  if (table->num_elements == 0) {
    iter->is_valid = false;
    iter->ht = table;
    iter->bucket_it = NULL;
    return iter;
  }

  // initialize the iterator.  there is at least one element in the
  // table, so find the first element and point the iterator at it.
  iter->is_valid = true;
  iter->ht = table;
  for (i = 0; i < table->num_buckets; i++) {
    if (NumElementsInLinkedList(table->buckets[i]) > 0) {
      iter->bucket_num = i;
      break;
    }
  }
  Verify333(i < table->num_buckets);  // make sure we found it.
  iter->bucket_it = LLMakeIterator(table->buckets[iter->bucket_num], 0UL);
  if (iter->bucket_it == NULL) {
    // out of memory!
    free(iter);
    return NULL;
  }
  return iter;
}

void HTIteratorFree(HTIter iter) {
  Verify333(iter != NULL);
  if (iter->bucket_it != NULL) {
    LLIteratorFree(iter->bucket_it);
    iter->bucket_it = NULL;
  }
  iter->is_valid = false;
  free(iter);
}

int HTIteratorNext(HTIter iter) {
  Verify333(iter != NULL);
  // Step 4 -- implement HTIteratorNext.
  // check if current iterator is invalid
  if (!iter->is_valid) {
    return 0;  // return false
  }
  // check if iterator is at the end of the bucket
  if (LLIteratorHasNext(iter->bucket_it)) {
    LLIteratorNext(iter->bucket_it);
    return 1;  // return success
  } else {
    // if current bucket is the last bucket
    if (iter->bucket_num == (iter->ht->num_buckets) - 1) {
      // invalid the iterator
      iter->is_valid = false;
      return 0;  // return false
    } else {
      uint64_t bucketIndex = iter->bucket_num + 1;
      // check the bucket index of next not empty bucket
      while ((bucketIndex < iter->ht->num_buckets) && (NumElementsInLinkedList
                                      (iter->ht->buckets[bucketIndex]) <= 0)) {
        bucketIndex++;
      }
      iter->bucket_num = bucketIndex;
      // if found bucket index is current bucket
      if (bucketIndex == iter->ht->num_buckets) {
        // in valid the iterator
        iter->is_valid = false;
        return 0;  // return false
      } else {
        // if not, free current iterator and create a new one to new bucket
        LLIteratorFree(iter->bucket_it);
        iter->bucket_it = LLMakeIterator
                            (iter->ht->buckets[iter->bucket_num], 0UL);
        // if failed to create a new iterator
        if (iter->bucket_it == NULL) {
          // invalid the iterator
          iter->is_valid = false;
          return 0;  // return false;
        }
        return 1;  // return success
      }
    }
  }
}

int HTIteratorPastEnd(HTIter iter) {
  Verify333(iter != NULL);
  // Step 5 -- implement HTIteratorPastEnd.
  // if current iterator is not valid or the hashtable it poitns to is null
  if (!iter->is_valid || iter->ht == NULL) {
    return 1;  // return sucess
  }
  return 0;  // return failure
}

int HTIteratorGet(HTIter iter, HTKeyValue *keyvalue) {
  Verify333(iter != NULL);
  // Step 6 -- implement HTIteratorGet.
  // if current iterator is not valid or the hashtable it poitns to is null
  if (!iter->is_valid || iter->ht == NULL) {
    return 0;  // return failure
  }
  HTKeyValuePtr oldpayload;
  // get the payload of current node
  LLIteratorGetPayload(iter->bucket_it, (LLPayload_t*)&oldpayload);
  keyvalue->key = ((HTKeyValuePtr)oldpayload)->key;
  keyvalue->value = ((HTKeyValuePtr)oldpayload)->value;
  return 1;  // return sucess
}

int HTIteratorDelete(HTIter iter, HTKeyValue *keyvalue) {
  HTKeyValue kv;
  int res, retval;

  Verify333(iter != NULL);

  // Try to get what the iterator is pointing to.
  res = HTIteratorGet(iter, &kv);
  if (res == 0)
    return 0;

  // Advance the iterator.
  res = HTIteratorNext(iter);
  if (res == 0) {
    retval = 2;
  } else {
    retval = 1;
  }
  res = RemoveFromHashTable(iter->ht, kv.key, keyvalue);
  Verify333(res == 1);
  Verify333(kv.key == keyvalue->key);
  Verify333(kv.value == keyvalue->value);

  return retval;
}

static void ResizeHashtable(HashTable ht) {
  // Resize if the load factor is > 3.
  if (ht->num_elements < 3 * ht->num_buckets)
    return;

  // This is the resize case.  Allocate a new hashtable,
  // iterate over the old hashtable, do the surgery on
  // the old hashtable record and free up the new hashtable
  // record.
  HashTable newht = AllocateHashTable(ht->num_buckets * 9);

  // Give up if out of memory.
  if (newht == NULL)
    return;

  // Loop through the old ht with an iterator,
  // inserting into the new HT.
  HTIter it = HashTableMakeIterator(ht);
  if (it == NULL) {
    // Give up if out of memory.
    FreeHashTable(newht, &HTNullFree);
    return;
  }

  while (!HTIteratorPastEnd(it)) {
    HTKeyValue item, dummy;

    Verify333(HTIteratorGet(it, &item) == 1);
    if (InsertHashTable(newht, item, &dummy) != 1) {
      // failure, free up everything, return.
      HTIteratorFree(it);
      FreeHashTable(newht, &HTNullFree);
      return;
    }
    HTIteratorNext(it);
  }

  // Worked!  Free the iterator.
  HTIteratorFree(it);

  // Sneaky: swap the structures, then free the new table,
  // and we're done.
  {
    HashTableRecord tmp;

    tmp = *ht;
    *ht = *newht;
    *newht = tmp;
    FreeHashTable(newht, &HTNullFree);
  }

  return;
}
static bool HasKey(LLIter lliter, HTKey_t key, HTKeyValuePtr* payload) {
  Verify333(lliter != NULL);

  while (LLIteratorHasNext(lliter)) {
    LLIteratorGetPayload(lliter, (LLPayload_t*) payload);
    if ((*payload)->key == key) {
      return true;
    }
    LLIteratorNext(lliter);
  }
  LLIteratorGetPayload(lliter, (LLPayload_t*) payload);
  if ((*payload)->key == key) {
      return true;
  }
  return false;
}



