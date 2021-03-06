#include "cli_test_monitor.h"
#include <stdio.h>

namespace st = SpeedTests;

CLITestMonitor::CLITestMonitor()
{
  setbuf(stdout, NULL);
}

CLITestMonitor::~CLITestMonitor()
{
}

void CLITestMonitor::BeforeTestIterations(const st::Runner &runner, const st::SpeedTest &test)
{
  printf("Running: %s\n         ", test.description());
}

void CLITestMonitor::AfterTestIterations(const st::Runner &runner, const st::SpeedTest &test)
{
  printf("\n");
}

void CLITestMonitor::BeforeTest(const st::Runner &runner, const st::SpeedTest &test, const size_t iteration)
{
  if ((iteration % (10000 / 40)) == 0) {
    printf("#");
  }
}

void CLITestMonitor::AfterTest(const st::Runner &runner, const st::SpeedTest &test, const size_t iteration)
{
}

void CLITestMonitor::TestAdded(const st::Runner &runner, const st::SpeedTest &test)
{
  printf("Test added: %s\n", test.description());
}

void CLITestMonitor::BeforeEverything(const st::Runner &runner)
{
  printf("\nRunning %zu tests.\n\n", runner.tests().size());
}

void CLITestMonitor::AfterEverything(const st::Runner &runner)
{
  if (output_tabbed) {
    PrintResultsTabbed(runner);
  } else {
    PrintResultsPretty(runner);
  }
}

void CLITestMonitor::PrintResultsPretty(const st::Runner &runner)
{
  printf("\n\nTesting finished!.\n\nResults\n");

  printf("---------------------+-----+----------------+----------------+----------------\n");
  printf("%-21s|%5s|%16s|%16s|%16s\n", "Test", "Loops", "Average:seconds", "Minimum:seconds", "Maximum:seconds" );
  printf("---------------------+-----+----------------+----------------+----------------\n");

  const int kDescriptionMax = 16;
  char snipped[kDescriptionMax+1] = {'\0'};
  const st::SpeedTestVector &tests = runner.tests();
  for (size_t i = 0; i < tests.size(); ++i) {
    strncpy(snipped, tests[i]->description(), kDescriptionMax + 1);
    snipped[kDescriptionMax] = '\0';

    printf("%-21s|%5zu|%6zu:%9f|%6zu:%9f|%6zu:%9f\n",
        snipped,
        tests[i]->iterations(),
        (size_t)tests[i]->average_time(), tests[i]->average_time_seconds(),
        (size_t)tests[i]->minimum_time(), tests[i]->minimum_time_seconds(),
        (size_t)tests[i]->maximum_time(), tests[i]->maximum_time_seconds());
  }
}

void CLITestMonitor::PrintResultsTabbed(const st::Runner &runner)
{
  printf("\n\nTesting finished!.\n\nResults:\n\n");

  printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
    "Test",
    "Loops",
    "Average clocks", "Average seconds",
    "Minimum clocks", "Minimum seconds",
    "Maximum clocks", "Minimum seconds" );

  const st::SpeedTestVector &tests = runner.tests();
  for (size_t i = 0; i < tests.size(); ++i) {
    printf("%s\t%zu\t%zu\t%f\t%zu\t%f\t%zu\t%f\n",
        tests[i]->description(),
        tests[i]->iterations(),
        (size_t)tests[i]->average_time(), tests[i]->average_time_seconds(),
        (size_t)tests[i]->minimum_time(), tests[i]->minimum_time_seconds(),
        (size_t)tests[i]->maximum_time(), tests[i]->maximum_time_seconds());
  }
}
