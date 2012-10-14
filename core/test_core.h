#ifndef SPEEDTESTS_CORE_TESTCORE_H_
#define SPEEDTESTS_CORE_TESTCORE_H_

#include <stddef.h>
#include <time.h>
#include <vector>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

namespace SpeedTests {

class SpeedTest {
 public:
  SpeedTest(const size_t iterations = 10000) : iterations_(iterations) { iteration_timings_.reserve(iterations_); };
  virtual ~SpeedTest() {};

  // The test to be timed
  virtual void Test() = 0;

  // Run before and after each test
  virtual void BeforeTest() {};
  virtual void AfterTest() {};

  // Run before and after the test iterations
  virtual void BeforeTestIterations() {};
  virtual void AfterTestIterations() {};

  void StoreTiming(const clock_t timing) { iteration_timings_.push_back(timing); };

  // Accessors
  virtual const char* description() const { return "I have no description. How mysterious."; };
  size_t iterations() const { return iterations_; };

  clock_t total_time() const;
  clock_t average_time() const;
  clock_t minimum_time() const;
  clock_t maximum_time() const;

  double total_time_seconds() const   { return (double)total_time() / CLOCKS_PER_SEC; };
  double average_time_seconds() const { return (double)average_time() / CLOCKS_PER_SEC; };
  double minimum_time_seconds() const { return (double)minimum_time() / CLOCKS_PER_SEC; };
  double maximum_time_seconds() const { return (double)maximum_time() / CLOCKS_PER_SEC; };

 private:
  DISALLOW_COPY_AND_ASSIGN(SpeedTest);

  const size_t iterations_;
  std::vector<clock_t> iteration_timings_;
};

typedef std::vector<SpeedTest*> SpeedTestVector;
class Runner;

class TestProgressInterface {
 public:
  virtual ~TestProgressInterface() {};

  // Run before and after each test
  virtual void BeforeTestIterations(const Runner &runner, const SpeedTest &test) = 0;
  virtual void AfterTestIterations(const Runner &runner, const SpeedTest &test) = 0;
  virtual void BeforeTest(const Runner &runner, const SpeedTest &test, const size_t iteration) = 0;
  virtual void AfterTest(const Runner &runner, const SpeedTest &test, const size_t iteration) = 0;

  virtual void TestAdded(const Runner &runner, const SpeedTest &test) = 0;

  // Run before and after the test iterations
  virtual void BeforeEverything(const Runner &runner) = 0;
  virtual void AfterEverything(const Runner &runner) = 0;
};

class Runner
{
 public:
  Runner(TestProgressInterface *monitor);
  ~Runner();

  void Add(SpeedTest *test);
  void Run(size_t run_batch_size);
  void RunAll() { Run(0); };

  void ResetSession();

  const SpeedTestVector& tests() const { return tests_; };

  bool also_destroy_tests_on_destruction() const {return also_destroy_tests_on_destruction_; };
  void set_also_destroy_tests_on_destruction(bool value) { also_destroy_tests_on_destruction_ = value; };
  bool session_has_tests_remaining() const;

 private:
  DISALLOW_COPY_AND_ASSIGN(Runner);

  bool first_session_test() const { return current_test == 0 && current_test_run == 0; };

  TestProgressInterface *monitor_;
  SpeedTestVector tests_;
  bool also_destroy_tests_on_destruction_;

  size_t current_test;
  size_t current_test_run;
};

} // namespace SpeedTests

#endif // SPEEDTESTS_CORE_TESTCORE_H_
