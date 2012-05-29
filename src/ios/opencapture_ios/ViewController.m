//
//  ViewController.m
//  opencapture_ios
//
//  Created by Mynumber on 29.05.12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

@synthesize captureContext;

- (void)viewDidLoad
{
    [super viewDidLoad];
    captureContext = oc_context_create();
    oc_device_list_t *deviceList = oc_device_list(captureContext);
    for(int i=0; i < deviceList->count; i++)
    {
        oc_device_t *device = deviceList->list[i];
        NSLog([NSString stringWithFormat:@"%s (%s)", device->name, device->id]);
    }
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

@end
