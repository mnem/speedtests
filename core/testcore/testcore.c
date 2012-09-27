#include "testcore.h"
#include <memory.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

TestRun* NewTestRun(
    const char *description,
    const size_t runs,
    TestRunFn test,
    TestRunPrepFn before_test,
    TestRunPrepFn after_test,
    TestRunPrepFn before_run,
    TestRunPrepFn after_run) {
  TestRun *test_run;

  assert(description);
  assert(test);
  assert(runs > 0);

  test_run = malloc(sizeof(TestRun));
  assert(test_run);

  test_run->runs = runs;
  test_run->Test = test;
  test_run->BeforeTest = before_test;
  test_run->AfterTest = after_test;
  test_run->BeforeRun = before_run;
  test_run->AfterRun = after_run;

  test_run->run_durations = malloc(sizeof(clock_t) * runs);
  assert(test_run->run_durations);
  memset(test_run->run_durations, 0xff, sizeof(int) * runs);

  test_run->description = malloc(strlen(description) + 1);
  assert(test_run->description);
  strcpy(test_run->description, description);

  return test_run;
}

void DeleteTestRun(TestRun *test_run) {
  if (test_run) {
    free(test_run->run_durations);
    test_run->run_durations = NULL;
    free(test_run->description);
    test_run->description = NULL;

    test_run->runs = 0;

    test_run->user_data = NULL;

    test_run->Test = NULL;
    test_run->BeforeTest = NULL;
    test_run->AfterTest = NULL;
    test_run->BeforeRun = NULL;
    test_run->AfterRun = NULL;

    free(test_run);
  }
}

void RunTest(TestRun* test_run,
    TestRunPrepFn before_test,
    TestRunPrepFn after_test,
    TestRunPrepFn before_run,
    TestRunPrepFn after_run) {
  assert(test_run);
  assert(test_run->Test);
  assert(test_run->runs > 0);

  clock_t before;

  size_t i;
  if (before_run) before_run(test_run, 0);
  if (test_run->BeforeRun) test_run->BeforeRun(test_run, 0);
  for (i = 0; i < test_run->runs; i++) {
    if (before_test) before_test(test_run, i);
    if (test_run->BeforeTest) test_run->BeforeTest(test_run, i);

    before = clock();
    test_run->Test();
    test_run->run_durations[i] = clock() - before;

    if (test_run->AfterTest) test_run->AfterTest(test_run, i);
    if (after_test) after_test(test_run, i);
  }
  if (test_run->AfterRun) test_run->AfterRun(test_run, test_run->runs - 1);
  if (after_run) after_run(test_run, test_run->runs - 1);
}

void SPrintTestRun(TestRun* test_run, char *string, size_t length) {
  assert(test_run);
  assert(string);
  assert(length > 0);

  size_t valid_reading_count = 0;
  clock_t average = 0;
  clock_t minimum = UINT_MAX;
  clock_t maximum = 0;
  size_t i;
  for (i = 0; i < test_run->runs; i++) {
    int reading = test_run->run_durations[i];
    if (reading >= 0) {
      ++valid_reading_count;
      average += reading;
      if (reading < minimum) minimum = reading;
      if (reading > maximum) maximum = reading;
    }
  }

  if (valid_reading_count > 0) {
    average /= valid_reading_count;
  }

  double average_seconds = (double)average / CLOCKS_PER_SEC;
  double minimum_seconds = (double)minimum / CLOCKS_PER_SEC;
  double maximum_seconds = (double)maximum / CLOCKS_PER_SEC;

  snprintf(string, length,
    "\n--=[  %s  ]=--\n"
    "  Valid runs:%6zu\n"
    "  Average   :%6zu (%fs)\n"
    "  Minimum   :%6zu (%fs)\n"
    "  Maximum   :%6zu (%fs)\n",
    test_run->description,
    valid_reading_count,
    (size_t)average, average_seconds,
    (size_t)minimum, minimum_seconds,
    (size_t)maximum, maximum_seconds);
}

void PrintTestRun(TestRun* test_run) {
  assert(test_run);

  const size_t buffer_size = 1024;
  char buffer[buffer_size];

  SPrintTestRun(test_run, buffer, buffer_size);

  printf("%s", buffer);
}
