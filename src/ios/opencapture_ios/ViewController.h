//
//  ViewController.h
//  opencapture_ios
//
//  Created by Mynumber on 29.05.12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <opencapture.h>

@interface ViewController : UIViewController {
    oc_context_t *captureContext;
    UIImageView *imageView;
}

@property(nonatomic) oc_context_t *captureContext;
@property(retain,nonatomic) UIImageView *imageView;

void video_callback(oc_context_t *context, int width, int height, char *data);

@end
