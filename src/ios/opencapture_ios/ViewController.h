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
}

@property(nonatomic) oc_context_t *captureContext;

@end
