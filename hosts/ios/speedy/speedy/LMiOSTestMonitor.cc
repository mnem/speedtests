#include "LMiOSTestMonitor.h"
#include <stdio.h>

namespace st = SpeedTests;

void LMiOSTestMonitor::BeforeTestIterations(const st::Runner &runner, const st::SpeedTest &test) {
	printf("Running: %s\n         ", test.description());
}

void LMiOSTestMonitor::AfterTestIterations(const st::Runner &runner, const st::SpeedTest &test) {
	printf("\n");
}

void LMiOSTestMonitor::BeforeTest(const st::Runner &runner, const st::SpeedTest &test, const size_t iteration) {
	if ((iteration % (10000 / 40)) == 0) {
		printf("#");
	}
}

void LMiOSTestMonitor::AfterTest(const st::Runner &runner, const st::SpeedTest &test, const size_t iteration) {
}

void LMiOSTestMonitor::TestAdded(const st::Runner &runner, const st::SpeedTest &test) {
	printf("Test added: %s\n", test.description());
}

void LMiOSTestMonitor::BeforeEverything(const st::Runner &runner) {
	printf("\nRunning %zu tests.\n\n", runner.tests().size());
}

void LMiOSTestMonitor::AfterEverything(const st::Runner &runner) {
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
