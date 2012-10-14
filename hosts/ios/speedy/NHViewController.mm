//
//  NHViewController.m
//  speedy
//
//  Created by David Wagner on 30/09/2012.
//  Copyright (c) 2012 Noise & Heat. All rights reserved.
//

#import "NHViewController.h"

#include "all_tests.h"
#include "test_core.h"
#include "LMiOSTestMonitor.h"

const size_t kBatchSize = 500;

@interface NHViewController ()
{
  LMiOSTestMonitor *monitor;
  SpeedTests::Runner *runner;
}
- (void)tick:(NSTimer *)timer;
@property (nonatomic, retain) NSTimer *timer;
@end

@implementation NHViewController

- (void)viewDidLoad
{
  [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
  
	monitor = new LMiOSTestMonitor();
	runner = new SpeedTests::Runner(&*monitor);
	SpeedTests::AddAllTests(*runner);
	
	[self.textView setContentSize:CGSizeMake(4096, 2048)];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)tick:(NSTimer *)theTimer
{
	runner->Run(kBatchSize);
  
  self.test.text = [NSString stringWithCString:monitor->running() encoding:NSUTF8StringEncoding];
  self.progress.progress = monitor->progress();
  
  if (!runner->session_has_tests_remaining()) {
    [self.timer invalidate];
    self.timer = nil;
    
    [self.activity stopAnimating];
    self.button.hidden = NO;

    self.textView.text = [NSString stringWithUTF8String:monitor->results()];
    self.textView.hidden = NO;
    
    self.test.hidden = YES;
    self.progress.hidden = YES;
  }
}

- (IBAction)test:(id)sender
{
  self.button.hidden = YES;
  self.textView.hidden = YES;
  
  self.test.text = @"";
  self.test.hidden = NO;
  self.progress.progress = 0.0f;
  self.progress.hidden = NO;

  runner->ResetSession();
	
  [self.activity startAnimating];
  
  self.timer = [NSTimer scheduledTimerWithTimeInterval:0.1
                                       target:self
                                     selector:@selector(tick:)
                                     userInfo:nil
                                      repeats:YES];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)orientation
{
	return UIInterfaceOrientationIsLandscape(orientation);
}
@end
