#include "LMiOSTestMonitor.h"
#include <stdio.h>

const bool kUsePrintf = false;

namespace st = SpeedTests;

void LMiOSTestMonitor::BeforeTestIterations(const st::Runner &runner, const st::SpeedTest &test) {
  if (kUsePrintf) printf("Running: %s\n         ", test.description());
  
  delete [] running_;
  size_t description_length = strlen(test.description());
  running_ = new char[description_length + 1];
  strcpy(running_, test.description());
  
  progress_ = 0;
}

void LMiOSTestMonitor::AfterTestIterations(const st::Runner &runner, const st::SpeedTest &test) {
	if (kUsePrintf) printf("\n");
  
  delete [] running_;
  running_ = new char[1];
  running_[0] = '\0';
}

void LMiOSTestMonitor::BeforeTest(const st::Runner &runner, const st::SpeedTest &test, const size_t iteration) {
  if (kUsePrintf) {
    if ((iteration % (10000 / 40)) == 0) {
      printf("#");
    }
  }
  
  progress_ = (float)iteration / (float)test.iterations();
}

void LMiOSTestMonitor::AfterTest(const st::Runner &runner, const st::SpeedTest &test, const size_t iteration) {
}

void LMiOSTestMonitor::TestAdded(const st::Runner &runner, const st::SpeedTest &test) {
	if (kUsePrintf) printf("Test added: %s\n", test.description());
}

void LMiOSTestMonitor::BeforeEverything(const st::Runner &runner) {
	if (kUsePrintf) printf("\nRunning %zu tests.\n\n", runner.tests().size());
}

void LMiOSTestMonitor::AfterEverything(const st::Runner &runner) {
	const int kStringMax = 4096;
	results_ = new char[kStringMax];
	results_[0] = '\0';
	
	const int kLineMax = 100;
	char line[kLineMax+1] = {0};
	
	strncat(results_, "---------------------+-----+----------------+----------------+----------------\n", kStringMax);
	snprintf(line, kLineMax, "%-21s|%5s|%16s|%16s|%16s\n", "Test", "Loops", "Average:seconds", "Minimum:seconds", "Maximum:seconds");
	strncat(results_, line, kStringMax);
	strncat(results_, "---------------------+-----+----------------+----------------+----------------\n", kStringMax);
	
	const int kDescriptionMax = 16;
	char snipped[kDescriptionMax+1] = {'\0'};
	const st::SpeedTestVector &tests = runner.tests();
	for (size_t i = 0; i < tests.size(); ++i) {
		strncpy(snipped, tests[i]->description(), kDescriptionMax + 1);
		snipped[kDescriptionMax] = '\0';
		
		snprintf(line, kLineMax, "%-21s|%5zu|%6zu:%9f|%6zu:%9f|%6zu:%9f\n",
			   snipped,
			   tests[i]->iterations(),
			   (size_t)tests[i]->average_time(), tests[i]->average_time_seconds(),
			   (size_t)tests[i]->minimum_time(), tests[i]->minimum_time_seconds(),
			   (size_t)tests[i]->maximum_time(), tests[i]->maximum_time_seconds());
		
		strncat(results_, line, kStringMax);
	}
	
	results_[kStringMax-1] = '\0';
}
