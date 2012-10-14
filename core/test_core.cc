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
Runner::Runner(TestProgressInterface *monitor) :
  also_destroy_tests_on_destruction_(true),
  monitor_(monitor),
  current_test(0),
  current_test_run(0)
{
}


void Runner::ResetSession()
{
  current_test = 0;
  current_test_run = 0;
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

// ## session_has_tests_remaining
//
// If you batch the test runs, this boolean
// indicates if there are any tests left to
// run after the last batch completed
bool Runner::session_has_tests_remaining() const
{
  return current_test < tests_.size();
}


// ## Run
//
// If run_batch_size is 0, runs all added tests, reporting progress to the test
// monitor as appropriate (and if a test monitor was
// set during creation).
//
// If run_batch_size > 0, run that many tests and then return. The function
// may then be called again to run another batch of tests, carrying on from
// the previous batch.
//
// Each test is timed and may be queried afterwards for
// run time statistics.
void Runner::Run(size_t run_batch_size)
{
  // Exit early if we know there are no tests to run
  if (!session_has_tests_remaining()) {
    return;
  }

  // If this is the first test of this session
  // and there is a monitor, tell it we're about
  // to run
  if (first_session_test() && monitor_) {
    monitor_->BeforeEverything(*this);
  };

  // Loop through all the tests
  while (current_test < tests_.size()) {
    SpeedTest *test = tests_[current_test];

    // If this is the first run of this test
    // let the monitor and the test know
    if (current_test_run == 0) {
      if (monitor_) monitor_->BeforeTestIterations(*this, *test);
      test->BeforeTestIterations();
    }

    // While there are test iterations left, run
    // the test and record the results
    while (current_test_run < test->iterations()) {
      if (monitor_) monitor_->BeforeTest(*this, *test, current_test_run);
      test->BeforeTest();

      clock_t duration = 0;
      clock_t before = clock();
      test->Test();
      duration = clock() - before;
      test->StoreTiming(duration);

      test->AfterTest();
      if (monitor_) monitor_->AfterTest(*this, *test, current_test_run);

      ++current_test_run;

      // If we've finished this batch of tests, return. Otherwise
      // on to the next run.
      if (run_batch_size == 1) {
        return;
      } else if (run_batch_size > 1) {
        --run_batch_size;
      }
    }

    // Tell the test and the monitor we've finished
    // all the iterations of this test
    test->AfterTestIterations();
    if (monitor_) monitor_->AfterTestIterations(*this, *test);

    // Move on to the next test, resetting the run counter
    ++current_test;
    current_test_run = 0;
  }

  // Tell the monitor we've finished everything
  if (monitor_) monitor_->AfterEverything(*this);
}

} // namespace SpeedTests
