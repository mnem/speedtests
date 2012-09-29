#include "cli_test_monitor.h"
#include "all_tests.h"

int main(int argc, char const *argv[]) {
  CLITestMonitor monitor;
  SpeedTests::Runner runner(&monitor);

  SpeedTests::AddAllTests(runner);

  runner.Run();

  return 0;
}
