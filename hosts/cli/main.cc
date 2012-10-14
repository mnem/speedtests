#include "cli_test_monitor.h"
#include "all_tests.h"

int main(int argc, char const *argv[])
{
  CLITestMonitor monitor;

  if (argc > 1) {
    int arg = 1;
    for (int arg = 1; arg < argc; ++arg) {
      if (strcmp("--tabbed", argv[arg]) == 0) {
        monitor.output_tabbed = true;
      }
    }
  }

  SpeedTests::Runner runner(&monitor);

  SpeedTests::AddAllTests(runner);

  runner.Run();

  return 0;
}
