//
//  LMiOSTestMonitor.h
//  speedy
//
//  Created by David Wagner on 30/09/2012.
//  Copyright (c) 2012 Noise & Heat. All rights reserved.
//

#ifndef __speedy__LMiOSTestMonitor__
#define __speedy__LMiOSTestMonitor__

#include "test_core.h"
#include <stdio.h>

class LMiOSTestMonitor : public SpeedTests::TestProgressInterface
{
public:
	LMiOSTestMonitor()
    : results_(NULL), running_(NULL), progress_(0.0f)
  {
    setbuf(stdout, NULL);
  };
  
	virtual ~LMiOSTestMonitor()
  {
    delete[] results_;
    delete[] running_;
  };
	
	virtual void BeforeTestIterations(const SpeedTests::Runner &runner, const SpeedTests::SpeedTest &test);
	virtual void AfterTestIterations(const SpeedTests::Runner &runner, const SpeedTests::SpeedTest &test);
	virtual void BeforeTest(const SpeedTests::Runner &runner, const SpeedTests::SpeedTest &test, const size_t iteration);
	virtual void AfterTest(const SpeedTests::Runner &runner, const SpeedTests::SpeedTest &test, const size_t iteration);
	virtual void TestAdded(const SpeedTests::Runner &runner, const SpeedTests::SpeedTest &test);
	virtual void BeforeEverything(const SpeedTests::Runner &runner);
	virtual void AfterEverything(const SpeedTests::Runner &runner);
	
	const char* results() const { return results_; };
	const char* running() const { return running_; };
	const float progress() const { return progress_; };

private:
	char *results_;
	char *running_;
  float progress_;
};

#endif /* defined(__speedy__LMiOSTestMonitor__) */
