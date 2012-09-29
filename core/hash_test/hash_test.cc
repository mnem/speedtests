#include "hash_test.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

////////////////////////////////////////
const size_t kKeyMaxLength = 32;
const size_t kNumKeys = 1000;

typedef struct SimpleHashable {
  UT_hash_handle hh;
  char key[kKeyMaxLength];
  int data;
} SimpleHashable;

TestItemStore::TestItemStore() {
  items = new SimpleHashable[kNumKeys];
  memset(items, 0, sizeof(*items) * kNumKeys);

  for (size_t i = 0; i < kNumKeys; i++) {
    snprintf(items[i].key, kKeyMaxLength, "k%zu:%zu", i, i * 2);
    items[i].data = i;
  }
}

TestItemStore::~TestItemStore() {
  delete[] items;
}

////////////////////////////////////////
void HashTestUTHashAdd::Test() {
  for (size_t i = 0; i < kNumKeys; i++) {
    HASH_ADD_STR(hash_, key, (&test_items.items[i]));
  }
}

void HashTestUTHashAdd::BeforeTest() {
  hash_ = NULL;
}

void HashTestUTHashAdd::AfterTest() {
    SimpleHashable *current;
    SimpleHashable *temp;
    HASH_ITER(hh, hash_, current, temp) {
      HASH_DEL(hash_, current);
    }
}

////////////////////////////////////////
typedef std::pair<char *, int> StdPair;
void HashTestBoostAdd::Test() {
  for (size_t i = 0; i < kNumKeys; i++) {
    hash_->insert(StdPair(test_items.items[i].key, test_items.items[i].data));
  }
}

void HashTestBoostAdd::BeforeTest() {
  hash_ = new BoostMap();
}

void HashTestBoostAdd::AfterTest() {
  delete hash_;
}

////////////////////////////////////////
void HashTestStdAdd::Test() {
  for (size_t i = 0; i < kNumKeys; i++) {
    hash_->insert(StdPair(test_items.items[i].key, test_items.items[i].data));
  }
}

void HashTestStdAdd::BeforeTest() {
  hash_ = new StdMap();
}

void HashTestStdAdd::AfterTest() {
  delete hash_;
}
