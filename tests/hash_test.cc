#include "hash_test.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

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
void HashTestUTHashBase::BeforeTest() {
  hash_ = NULL;
}

void HashTestUTHashBase::AfterTest() {
    SimpleHashable *current;
    SimpleHashable *temp;
    HASH_ITER(hh, hash_, current, temp) {
      HASH_DEL(hash_, current);
    }
}

void HashTestUTHashAdd::Test() {
  for (size_t i = 0; i < kNumKeys; i++) {
    HASH_ADD_STR(hash_, key, (&test_items.items[i]));
  }
}

void HashTestUTHashFind::BeforeTestIterations() {
  hash_ = NULL;
  for (size_t i = 0; i < kNumKeys; i++) {
    HASH_ADD_STR(hash_, key, (&test_items.items[(kNumKeys - 1) - i]));
  }
}

void HashTestUTHashFind::AfterTestIterations() {
    SimpleHashable *current;
    SimpleHashable *temp;
    HASH_ITER(hh, hash_, current, temp) {
      HASH_DEL(hash_, current);
    }
}

void HashTestUTHashFind::Test() {
  SimpleHashable *found = NULL;
  for (size_t i = 0; i < kNumKeys; i++) {
    HASH_FIND_STR(hash_, test_items.items[i].key, found);
    assert(found);
  }
}

////////////////////////////////////////
void HashTestBoostBase::BeforeTest() {
  hash_ = new BoostMap();
}

void HashTestBoostBase::AfterTest() {
  delete hash_;
}

typedef std::pair<char *, int> StdPair;
void HashTestBoostAdd::Test() {
  for (size_t i = 0; i < kNumKeys; i++) {
    hash_->insert(StdPair(test_items.items[i].key, test_items.items[i].data));
  }
}

void HashTestBoostFind::BeforeTestIterations() {
  hash_ = new BoostMap();
  for (size_t i = 0; i < kNumKeys; i++) {
    hash_->insert(StdPair(test_items.items[(kNumKeys - 1) - i].key, test_items.items[(kNumKeys - 1) - i].data));
  }
}

void HashTestBoostFind::AfterTestIterations() {
  delete hash_;
}

void HashTestBoostFind::Test() {
  BoostMap::iterator found;
  for (size_t i = 0; i < kNumKeys; i++) {
    found = hash_->find(test_items.items[i].key);
    assert(found != hash_->end());
  }
}

////////////////////////////////////////
void HashTestStdBase::BeforeTest() {
  hash_ = new StdMap();
}

void HashTestStdBase::AfterTest() {
  delete hash_;
}

void HashTestStdAdd::Test() {
  for (size_t i = 0; i < kNumKeys; i++) {
    hash_->insert(StdPair(test_items.items[i].key, test_items.items[i].data));
  }
}

void HashTestStdFind::BeforeTestIterations() {
  hash_ = new StdMap();
  for (size_t i = 0; i < kNumKeys; i++) {
    hash_->insert(StdPair(test_items.items[(kNumKeys - 1) - i].key, test_items.items[(kNumKeys - 1) - i].data));
  }
}

void HashTestStdFind::AfterTestIterations() {
  delete hash_;
}

void HashTestStdFind::Test() {
  StdMap::iterator found;
  for (size_t i = 0; i < kNumKeys; i++) {
    found = hash_->find(test_items.items[i].key);
    assert(found != hash_->end());
  }
}
