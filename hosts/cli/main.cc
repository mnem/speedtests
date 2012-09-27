#include "hashtest/hashtest.h"

#include "testcore/testcore.h"

#include <stdio.h>

const size_t kRuns = 10000;
const size_t kRunsPerProgressBlip = kRuns / 40;

extern "C" {
void PrintProgress(TestRun *test_run, size_t run) {
  if (run % kRunsPerProgressBlip == 0) printf("#");
}

void PrintTitle(TestRun *test_run, size_t run) {
  printf("\nRunning: %s\n", test_run->description);
}
}

int main(int argc, char **argv)
{
  setbuf(stdout, NULL);

  printf("Generating tests.\n");

  TestRun* tests[] = {
    NewTestRun("UTHash test", kRuns, hashtest_c, NULL, NULL, NULL, NULL),
    NewTestRun("Boost hash test", kRuns, hashtest_cc, NULL, NULL, NULL, NULL)
  };
  const size_t kNumTests = sizeof(tests) / sizeof(TestRun*);

  printf("Running each test %zu times.\n", kRuns);
  for (size_t i = 0; i < kNumTests; i++) {
    RunTest(tests[i], PrintProgress, NULL, PrintTitle, NULL);
  }

  printf("\n\nResults:");

  for (size_t i = 0; i < kNumTests; i++) {
    PrintTestRun(tests[i]);
  }

  printf("\nTidying up.\n\n");

  for (size_t i = 0; i < kNumTests; i++) {
    DeleteTestRun(tests[i]);
  }

  return 0;
}