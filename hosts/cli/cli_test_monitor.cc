#include "cli_test_monitor.h"
#include <stdio.h>

namespace st = SpeedTests;

CLITestMonitor::CLITestMonitor() {
  setbuf(stdout, NULL);
}

CLITestMonitor::~CLITestMonitor() {
}

void CLITestMonitor::BeforeTestIterations(const st::Runner &runner, const st::SpeedTest &test) {
  printf("Running: %s\n         ", test.description());
}

void CLITestMonitor::AfterTestIterations(const st::Runner &runner, const st::SpeedTest &test) {
  printf("\n");
}

void CLITestMonitor::BeforeTest(const st::Runner &runner, const st::SpeedTest &test, const size_t iteration) {
  if ((iteration % (10000 / 40)) == 0) {
    printf("#");
  }
}

void CLITestMonitor::AfterTest(const st::Runner &runner, const st::SpeedTest &test, const size_t iteration) {
}

void CLITestMonitor::TestAdded(const st::Runner &runner, const st::SpeedTest &test) {
  printf("Test added: %s\n", test.description());
}

void CLITestMonitor::BeforeEverything(const st::Runner &runner) {
  printf("\nRunning %zu tests.\n\n", runner.tests().size());
}

void CLITestMonitor::AfterEverything(const st::Runner &runner) {
  printf("\n\nTesting finished!.\n\n          Results\n          =======\n");

  const st::SpeedTestVector &tests = runner.tests();
  for (size_t i = 0; i < tests.size(); ++i) {
    printf(
        "\n--=[  %s  ]=--\n"
        "  Iterations :%7zu\n"
        "  Average    :%7zu (%fs)\n"
        "  Minimum    :%7zu (%fs)\n"
        "  Maximum    :%7zu (%fs)\n",
        tests[i]->description(),
        tests[i]->iterations(),
        (size_t)tests[i]->average_time(), tests[i]->average_time_seconds(),
        (size_t)tests[i]->minimum_time(), tests[i]->minimum_time_seconds(),
        (size_t)tests[i]->maximum_time(), tests[i]->maximum_time_seconds());
  }
}
