#import "QTKitCapture.h"
#import <stdio.h>

@implementation QTKitCapture

- (void)startCapture
{
	// Create a new Capture Session
    mCaptureSession = [[QTCaptureSession alloc] init]; 

    //Connect inputs and outputs to the session
    BOOL success = NO;
    NSError *error;

    // Find a video device
    QTCaptureDevice *device = [QTCaptureDevice defaultInputDeviceWithMediaType:@"QTMediaTypeVideo"];
    if(device) {
        success = [device open:&error];
        if(!success) {
            // Handle Error!
        }
        // Add the video device to the session as device input
        mCaptureDeviceInput = [[QTCaptureDeviceInput alloc] initWithDevice:device];
        success = [mCaptureSession addInput:mCaptureDeviceInput error:&error];
        if(!success) {
            // Handle error
        }

        // Associate the capture view in the UI with the session
        //[mCaptureView setCaptureSession:mCaptureSession];

        // Start the capture session runing
        [mCaptureSession startRunning];

    } // End if device

}

@end

oc_context_t* oc_context_create()
{
	oc_osx_context_t *context = malloc(sizeof(oc_osx_context_t));
	context->pool = [[NSAutoreleasePool alloc] init];
	return context;
}

void oc_context_destroy(oc_context_t *_context)
{
	oc_osx_context_t *context = (oc_osx_context_t*) _context;
	NSAutoreleasePool *pool = context->pool;
	[pool release];
	free(context);
}

oc_device_list_t* oc_device_list_all(oc_context_t *_context, int type)
{
	oc_osx_context_t *context = (oc_osx_context_t*) _context;
	NSArray *list;

	if (type == 0)
		list = [QTCaptureDevice inputDevices];
	else if (type == 1)
		list = [QTCaptureDevice inputDevicesWithMediaType:QTMediaTypeVideo];
	else if (type == 3)
		list = [QTCaptureDevice inputDevicesWithMediaType:QTMediaTypeSound];

	oc_device_list_t *devices = malloc(sizeof(oc_device_list_t));
	devices->count = [list count];
	devices->list = malloc(sizeof(oc_device_t)*devices->count);
	for(int i=0; i < devices->count; i++)
	{
		QTCaptureDevice *captureDevice = [list objectAtIndex:i];
		oc_device_t *device = malloc(sizeof(oc_device_t));
		device->id = [[captureDevice uniqueID] UTF8String];
		device->name = [[captureDevice localizedDisplayName] UTF8String];
		devices->list[i] = device;
	}
	return devices;
}

oc_device_list_t* oc_device_list(oc_context_t *_context)
{
	return oc_device_list_all(_context, 0);
}

oc_device_list_t* oc_device_list_video(oc_context_t *_context)
{
	return oc_device_list_all(_context, 1);
}

oc_device_list_t* oc_device_list_audio(oc_context_t *_context)
{
	return oc_device_list_all(_context, 2);
}

void oc_device_list_destroy(oc_device_list_t *devices)
{
	for(int i=0;i<devices->count;i++)
	{
		oc_device_t *device = devices->list[i];
		free(device);
	}
	free(devices->list);
	free(devices);
}