#ifndef SPEEDTESTS_CORE_TESTCORE_H_
#define SPEEDTESTS_CORE_TESTCORE_H_

#include <stddef.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct TestRun;

typedef void (*TestRunFn)(void);
typedef void (*TestRunPrepFn)(struct TestRun*, size_t run);

typedef struct TestRun {
  size_t runs;
  clock_t *run_durations;
  char *description;
  TestRunFn Test;

  // Optional
  void *user_data;
  TestRunPrepFn BeforeRun;
  TestRunPrepFn AfterRun;
  TestRunPrepFn BeforeTest;
  TestRunPrepFn AfterTest;
} TestRun;

TestRun* NewTestRun(
    const char *description,
    const size_t runs,
    TestRunFn test,
    TestRunPrepFn before_test,
    TestRunPrepFn after_test,
    TestRunPrepFn before_run,
    TestRunPrepFn after_run);
void DeleteTestRun(TestRun *test_run);

void RunTest(TestRun* test_run,
    TestRunPrepFn before_test,
    TestRunPrepFn after_test,
    TestRunPrepFn before_run,
    TestRunPrepFn after_run);

void SPrintTestRun(TestRun* test_run, char *string, size_t length);
void PrintTestRun(TestRun* test_run);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SPEEDTESTS_CORE_TESTCORE_H_
