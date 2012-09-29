#ifndef SPEEDTESTS_HOST_CLI_TEST_MONITOR_H_
#define SPEEDTESTS_HOST_CLI_TEST_MONITOR_H_

#include "test_core/test_core.h"

class CLITestMonitor : public SpeedTests::TestProgressInterface
{
public:
  CLITestMonitor();
  virtual ~CLITestMonitor();

  virtual void BeforeTestIterations(const SpeedTests::Runner &runner, const SpeedTests::SpeedTest &test);
  virtual void AfterTestIterations(const SpeedTests::Runner &runner, const SpeedTests::SpeedTest &test);
  virtual void BeforeTest(const SpeedTests::Runner &runner, const SpeedTests::SpeedTest &test, const size_t iteration);
  virtual void AfterTest(const SpeedTests::Runner &runner, const SpeedTests::SpeedTest &test, const size_t iteration);
  virtual void TestAdded(const SpeedTests::Runner &runner, const SpeedTests::SpeedTest &test);
  virtual void BeforeEverything(const SpeedTests::Runner &runner);
  virtual void AfterEverything(const SpeedTests::Runner &runner);
};

#endif // SPEEDTESTS_HOST_CLI_TEST_MONITOR_H_
