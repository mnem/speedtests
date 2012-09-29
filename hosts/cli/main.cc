#include "cli_test_monitor.h"
#include "hash_test/hash_test.h"

int main(int argc, char const *argv[]) {
  CLITestMonitor monitor;
  SpeedTests::Runner runner(&monitor);

  runner.Add(new HashTestUTHashAdd());
  runner.Add(new HashTestUTHashFind());

  runner.Add(new HashTestBoostAdd());
  runner.Add(new HashTestBoostFind());

  runner.Add(new HashTestStdAdd());
  runner.Add(new HashTestStdFind());

  runner.Run();

  return 0;
}
