#ifndef SPEEDTESTS_CORE_HASHTEST_H_
#define SPEEDTESTS_CORE_HASHTEST_H_

#include "../test_core/test_core.h"
#include "uthash.h"

////////////////////////////////////////
struct SimpleHashable;
class TestItemStore {
 public:
  TestItemStore();
  ~TestItemStore();

  struct SimpleHashable *items;
};

////////////////////////////////////////
class HashTestUTHashAdd : public SpeedTests::SpeedTest {
 public:
  virtual void Test();
  virtual void BeforeTest();
  virtual void AfterTest();
  virtual const char* description() const { return "UTHash: Add items test."; };

 private:
  TestItemStore test_items;
  SimpleHashable *hash_;
};

////////////////////////////////////////
#include <boost/unordered_map.hpp>
typedef boost::unordered_map<char *, int> BoostMap;

class HashTestBoostAdd : public SpeedTests::SpeedTest {
 public:
  virtual void Test();
  virtual void BeforeTest();
  virtual void AfterTest();
  virtual const char* description() const { return "Boost: Add items test."; };

 private:
  TestItemStore test_items;
  BoostMap *hash_;
};

////////////////////////////////////////
#include <map>
typedef std::map<char *, int> StdMap;

class HashTestStdAdd : public SpeedTests::SpeedTest {
 public:
  virtual void Test();
  virtual void BeforeTest();
  virtual void AfterTest();
  virtual const char* description() const { return "Std: Add items test."; };

 private:
  TestItemStore test_items;
  StdMap *hash_;
};

#endif // SPEEDTESTS_CORE_HASHTEST_H_
