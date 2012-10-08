//
// # Test Core
//
#include "test_core.h"
#include <memory.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

namespace SpeedTests {

// ## total_time
//
// Returns the total run time for all the tests.
clock_t SpeedTest::total_time() const
{
  clock_t total = 0;
  for (size_t i = 0; i < iteration_timings_.size(); ++i) {
    total += iteration_timings_[i];
  }
  return total;
}

// ## average_time
//
// Returns the mean average time for the tests.
clock_t SpeedTest::average_time() const
{
  return total_time() / iteration_timings_.size();
}

// ## minimum_time
//
// Returns the shortest run time for a test.
clock_t SpeedTest::minimum_time() const
{
  clock_t minimum = iteration_timings_.size() > 0 ? iteration_timings_[0] : 0;
  for (size_t i = 1; i < iteration_timings_.size(); ++i) {
    if (iteration_timings_[i] < minimum) {
      minimum = iteration_timings_[i];
    }
  }
  return minimum;
}


// ## minimum_time
//
// Returns the maximum run time for a test.
clock_t SpeedTest::maximum_time() const
{
  clock_t maximum = iteration_timings_.size() > 0 ? iteration_timings_[0] : 0;
  for (size_t i = 1; i < iteration_timings_.size(); ++i) {
    if (iteration_timings_[i] > maximum) {
      maximum = iteration_timings_[i];
    }
  }
  return maximum;
}


// ## Runner
//
// Creates a test runner, optionally using the passed
// monitor to output progress and results. `monitor`
// may be null.
Runner::Runner(TestProgressInterface *monitor)
{
  also_destroy_tests_on_destruction_ = true;
  monitor_ = monitor;
}


// ## ~Runner
//
// Deletes the runner, and also calls delete
// on each added test if `also_destroy_tests_on_destruction`
// is true
Runner::~Runner()
{
  if (also_destroy_tests_on_destruction_) {
    for (size_t test_index = 0; test_index < tests_.size(); ++test_index) {
      delete tests_[test_index];
      tests_[test_index] = NULL;
    }
  }
}

// ## Add
//
// Adds a new test to be run. The test is only stored, it
// will be run when Runner::Run() is called.
//
// Will report the test being added to the monitor, if
// a monitor was set on creation of Runner.
void Runner::Add(SpeedTest *test)
{
  if (test) {
    tests_.push_back(test);
    if (monitor_) {
      monitor_->TestAdded(*this, *test);
    }
  }
}

// ## Run
//
// Runs all added test, reporting progress to the test
// monitor as appropriate (and if a test monitor was
// set during creation).
//
// Each test is timed and may be queried afterwards for
// run time statistics.
void Runner::Run()
{
  if (monitor_) monitor_->BeforeEverything(*this);

  for (size_t test_index = 0; test_index < tests_.size(); ++test_index) {
    SpeedTest *test = tests_[test_index];

    if (monitor_) monitor_->BeforeTestIterations(*this, *test);
    test->BeforeTestIterations();

    for (size_t iteration = 0; iteration < test->iterations(); ++iteration) {
      if (monitor_) monitor_->BeforeTest(*this, *test, iteration);
      test->BeforeTest();

      clock_t duration = 0;
      clock_t before = clock();
      test->Test();
      duration = clock() - before;
      test->StoreTiming(duration);

      test->AfterTest();
      if (monitor_) monitor_->AfterTest(*this, *test, iteration);
    }

    test->AfterTestIterations();
    if (monitor_) monitor_->AfterTestIterations(*this, *test);
  }

  if (monitor_) monitor_->AfterEverything(*this);
}

} // namespace SpeedTests
