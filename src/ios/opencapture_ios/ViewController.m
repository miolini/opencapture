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
@synthesize imageView;

void video_callback(oc_context_t *context, int width, int height, char *data) 
{
    NSLog(@"new frame");
/*
    UIImage *image = [[UIImage alloc] initWithSize:UIMakeSize(width,height)];
	NSBitmapImageRep *imageRep;
	imageRep = [[NSBitmapImageRep alloc]
                initWithBitmapDataPlanes:&data2
                pixelsWide:width
                pixelsHigh:height
                bitsPerSample:8
                samplesPerPixel:3
                hasAlpha:NO
                isPlanar:NO
                colorSpaceName:NSDeviceRGBColorSpace
                bytesPerRow:width * 3
                bitsPerPixel:24];
    
	[image addRepresentation:imageRep];
	[[display image] release];
	[display setImage: image];
	free(data2);
 */
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    captureContext = oc_context_create();
    oc_device_list_t *deviceList = oc_device_list_video(captureContext);
    for(int i=0; i < deviceList->count; i++)
    {
        oc_device_t *device = deviceList->list[i];
        NSLog([NSString stringWithFormat:@"%s (%s)", device->name, device->id]);
    }
    if (deviceList->count > 0)
        oc_start(captureContext, deviceList->list[0], video_callback, NULL);
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
