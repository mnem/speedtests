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
@property (strong, nonatomic) IBOutlet UIProgressView *progressView;
- (IBAction)test:(id)sender;

@end
