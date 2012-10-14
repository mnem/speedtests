#ifndef SPEEDTESTS_CORE_HASHTEST_H_
#define SPEEDTESTS_CORE_HASHTEST_H_

#include "test_core.h"
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
class HashTestUTHashBase : public SpeedTests::SpeedTest {
 public:
  virtual void BeforeTest();
  virtual void AfterTest();
 protected:
  TestItemStore test_items;
  SimpleHashable *hash_;
};

class HashTestUTHashAdd : public HashTestUTHashBase {
 public:
  virtual void Test();
  virtual const char* description() const { return "UTHash: Add"; };
};

class HashTestUTHashFind : public HashTestUTHashBase {
 public:
  virtual void Test();
  virtual void BeforeTest() {};
  virtual void AfterTest() {};
  virtual void BeforeTestIterations();
  virtual void AfterTestIterations();
  virtual const char* description() const { return "UTHash: Find"; };
};

////////////////////////////////////////
#include <boost/unordered_map.hpp>
typedef boost::unordered_map<char *, int> BoostMap;
class HashTestBoostBase : public SpeedTests::SpeedTest {
 public:
  virtual void BeforeTest();
  virtual void AfterTest();
 protected:
  TestItemStore test_items;
  BoostMap *hash_;
};

class HashTestBoostAdd : public HashTestBoostBase {
 public:
  virtual void Test();
  virtual const char* description() const { return "Boost: Add"; };
};

class HashTestBoostFind : public HashTestBoostBase {
 public:
  virtual void Test();
  virtual void BeforeTest() {};
  virtual void AfterTest() {};
  virtual void BeforeTestIterations();
  virtual void AfterTestIterations();
  virtual const char* description() const { return "Boost: Find"; };
};

////////////////////////////////////////
#include <map>
typedef std::map<char *, int> StdMap;
class HashTestStdBase : public SpeedTests::SpeedTest {
 public:
  virtual void BeforeTest();
  virtual void AfterTest();
 protected:
  TestItemStore test_items;
  StdMap *hash_;
};

class HashTestStdAdd : public HashTestStdBase {
 public:
  virtual void Test();
  virtual const char* description() const { return "Std: Add"; };
};

class HashTestStdFind : public HashTestStdBase {
 public:
  virtual void Test();
  virtual void BeforeTest() {};
  virtual void AfterTest() {};
  virtual void BeforeTestIterations();
  virtual void AfterTestIterations();
  virtual const char* description() const { return "Std: Find"; };
};

#endif // SPEEDTESTS_CORE_HASHTEST_H_
