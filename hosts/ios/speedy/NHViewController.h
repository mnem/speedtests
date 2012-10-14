//
//  NHViewController.h
//  speedy
//
//  Created by David Wagner on 30/09/2012.
//  Copyright (c) 2012 Noise & Heat. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface NHViewController : UIViewController

@property (strong, nonatomic) IBOutlet UITextView *textView;
@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *activity;
@property (strong, nonatomic) IBOutlet UIButton *button;
@property (strong, nonatomic) IBOutlet UILabel *test;
@property (strong, nonatomic) IBOutlet UIProgressView *progress;

- (IBAction)test:(id)sender;

@end
