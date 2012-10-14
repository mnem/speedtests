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


@interface NHViewController ()

@end

@implementation NHViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
	
	[self.textView setContentSize:CGSizeMake(4096, 2048)];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)test:(id)sender
{
	LMiOSTestMonitor monitor;
	SpeedTests::Runner runner(&monitor);
	SpeedTests::AddAllTests(runner);
	runner.Run();
	
	self.textView.text = [NSString stringWithUTF8String:monitor.results()];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)orientation
{
	return UIInterfaceOrientationIsLandscape(orientation);
}
@end
