#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "uthash.h"
#include "hashtest.h"

const size_t kKeyMaxLength = 32;
const size_t kNumKeys = 1000;

typedef struct {
  UT_hash_handle hh;
  char key[32];
  int data;
} SimpleHashable;

void HashtestBeforeRun(TestRun *test_run, size_t run)
{
  const size_t kTestDataSize = sizeof(SimpleHashable) * kNumKeys;
  test_run->user_data = malloc(kTestDataSize);
  memset(test_run->user_data, 0, kTestDataSize);

  size_t i;
  SimpleHashable *items = (SimpleHashable *)test_run->user_data;
  for (i = 0; i < kNumKeys; i++) {
    snprintf(items[i].key, kKeyMaxLength, "k%zu:%zu", i, i * 2);
    items[i].data = i;
  }
}

void HashtestAfterRun(TestRun *test_run, size_t run)
{
  free(test_run->user_data);
  test_run->user_data = NULL;
}


void HashtestUTHashAdd(void *user_data)
{
  SimpleHashable *items = (SimpleHashable *)user_data;
  SimpleHashable *hash = NULL;

  size_t i;
  for (i = 0; i < kNumKeys; i++) {
    SimpleHashable *item = &items[i];
    HASH_ADD_STR(hash, key, item);
  }
}

#include <boost/unordered_map.hpp>
typedef boost::unordered_map<char *, int> Hash;
void HashtestBoostAdd(void *user_data)
{
  SimpleHashable *items = (SimpleHashable *)user_data;
  Hash hash;

  size_t i;
  for (i = 0; i < kNumKeys; i++) {
    hash[items[i].key] = items[i].data;
  }
}
