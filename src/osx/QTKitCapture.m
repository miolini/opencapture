#import "QTKitCapture.h"
#import "../opencapture.h"
#import <stdio.h>

@implementation QTKitCapture

- (void)startCapture
{
	
}

@end


void oc_test()
{
	printf("oc_test() - test passed from OSX version\n");
	QTKitCapture *capture = [[QTKitCapture alloc] init];
}