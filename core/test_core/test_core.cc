#include "test_core.h"
#include <memory.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

namespace SpeedTests {

clock_t SpeedTest::total_time() const {
  clock_t total = 0;
  for (size_t i = 0; i < iteration_timings_.size(); ++i) {
    total += iteration_timings_[i];
  }
  return total;
}

clock_t SpeedTest::average_time() const {
  return total_time() / iteration_timings_.size();
}

clock_t SpeedTest::minimum_time() const {
  clock_t minimum = iteration_timings_.size() > 0 ? iteration_timings_[0] : 0;
  for (size_t i = 1; i < iteration_timings_.size(); ++i) {
    if (iteration_timings_[i] < minimum) {
      minimum = iteration_timings_[i];
    }
  }
  return minimum;
}

clock_t SpeedTest::maximum_time() const {
  clock_t maximum = iteration_timings_.size() > 0 ? iteration_timings_[0] : 0;
  for (size_t i = 1; i < iteration_timings_.size(); ++i) {
    if (iteration_timings_[i] > maximum) {
      maximum = iteration_timings_[i];
    }
  }
  return maximum;
}

Runner::Runner(TestProgressInterface *monitor) {
  also_destroy_tests_on_destruction_ = true;
  monitor_ = monitor;
}

Runner::~Runner() {
  if (also_destroy_tests_on_destruction_) {
    for (size_t test_index = 0; test_index < tests_.size(); ++test_index) {
      delete tests_[test_index];
      tests_[test_index] = NULL;
    }
  }
}

void Runner::Add(SpeedTest *test) {
  tests_.push_back(test);
  if (monitor_) monitor_->TestAdded(*this, *test);
}

void Runner::Run() {
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

} // namspace SpeedTests

// void SPrintTestRun(TestRun* test_run, char *string, size_t length) {
//   assert(test_run);
//   assert(string);
//   assert(length > 0);

//   size_t valid_reading_count = 0;
//   clock_t average = 0;
//   clock_t minimum = UINT_MAX;
//   clock_t maximum = 0;
//   size_t i;
//   for (i = 0; i < test_run->runs; i++) {
//     int reading = test_run->run_durations[i];
//     if (reading >= 0) {
//       ++valid_reading_count;
//       average += reading;
//       if (reading < minimum) minimum = reading;
//       if (reading > maximum) maximum = reading;
//     }
//   }

//   if (valid_reading_count > 0) {
//     average /= valid_reading_count;
//   }

//   double average_seconds = (double)average / CLOCKS_PER_SEC;
//   double minimum_seconds = (double)minimum / CLOCKS_PER_SEC;
//   double maximum_seconds = (double)maximum / CLOCKS_PER_SEC;

//   snprintf(string, length,
//     "\n--=[  %s  ]=--\n"
//     "  Valid runs:%6zu\n"
//     "  Average   :%7zu (%fs)\n"
//     "  Minimum   :%7zu (%fs)\n"
//     "  Maximum   :%7zu (%fs)\n",
//     test_run->description,
//     valid_reading_count,
//     (size_t)average, average_seconds,
//     (size_t)minimum, minimum_seconds,
//     (size_t)maximum, maximum_seconds);
// }

// void PrintTestRun(TestRun* test_run) {
//   assert(test_run);

//   const size_t buffer_size = 1024;
//   char buffer[buffer_size];

//   SPrintTestRun(test_run, buffer, buffer_size);

//   printf("%s", buffer);
// }
