#import "osx.h"
#import <stdio.h>
#import <Cocoa/Cocoa.h>
#import <Quartz/Quartz.h>

@implementation OpenCapture

@synthesize videoDevice;
@synthesize context;
@synthesize videoCallback;

- (void)startCapture
{
	BOOL success = NO;
    NSError *error;
	NSLog(@"start capture");
    captureSession = [[QTCaptureSession alloc] init]; 
    if(videoDevice) {
        success = [videoDevice open:&error];
        if(!success) {
			NSLog(@"can't open video device");
			return;
        }
        videoInput = [[QTCaptureDeviceInput alloc] initWithDevice:videoDevice];
        success = [captureSession addInput:videoInput error:&error];
        if(!success) {
			NSLog(@"can't add input tot capture session");
			return;
        }
		QTCaptureDecompressedVideoOutput *videoOutput = [[QTCaptureDecompressedVideoOutput alloc] init];
		[videoOutput setDelegate: self];
		success = [captureSession addOutput:videoOutput error:&error];
        if(!success) {
			NSLog(@"can't add output for capture session");
			return;
        }
    } 
	[captureSession startRunning];
	printf("capture session runned\n");
}

- (void)captureOutput:(QTCaptureOutput *)captureOutput 
	didOutputVideoFrame:(CVImageBufferRef)videoFrame 
	withSampleBuffer:(QTSampleBuffer *)sampleBuffer 
	fromConnection:(QTCaptureConnection *)connection
{
	if (self->videoCallback == NULL) return;
	int w = CVPixelBufferGetWidth(videoFrame);
	int h = CVPixelBufferGetHeight(videoFrame);
	CVImageBufferRef imageBufferToRelease;
	CVBufferRetain(videoFrame);
	@synchronized (self) {
		imageBufferToRelease = frameBuffer;
		frameBuffer = videoFrame;
	}
	//CVBufferRelease(imageBufferToRelease);
	char *data = (char *) [sampleBuffer bytesForAllSamples];
	printf("buffer length: %lu\n", [sampleBuffer lengthForAllSamples]); 
	self->videoCallback(context, w, h, data);
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

oc_device_list_t* oc_device_list_by_type(oc_context_t *_context, int type)
{
	oc_osx_context_t *context = (oc_osx_context_t*) _context;
	NSArray *list;

	if (type == 0)
		list = [QTCaptureDevice inputDevices];
	else if (type == 1)
		list = [QTCaptureDevice inputDevicesWithMediaType:QTMediaTypeVideo];
	else if (type == 2)
		list = [QTCaptureDevice inputDevicesWithMediaType:QTMediaTypeSound];

	oc_device_list_t *devices = malloc(sizeof(oc_device_list_t));
	devices->count = [list count];
	devices->list = malloc(sizeof(oc_device_t)*devices->count);
	int i;
	for(i=0; i < devices->count; i++)
	{
		QTCaptureDevice *captureDevice = [list objectAtIndex:i];
		oc_device_t *device = malloc(sizeof(oc_device_t));
		device->id = [[captureDevice uniqueID] UTF8String];
		device->name = [[captureDevice localizedDisplayName] UTF8String];
		device->native = captureDevice;
		devices->list[i] = device;
	}
	return devices;
}

void oc_device_list_destroy(oc_device_list_t *devices)
{
	int i;
	for(i=0;i<devices->count;i++)
	{
		oc_device_t *device = devices->list[i];
		free(device);
	}
	free(devices->list);
	free(devices);
}

void oc_start(oc_context_t *_context, oc_device_t *video, OC_CALLBACK(videoCallback), oc_device_t *audio) 
{
	printf("starting capturing session\n");
	[NSAutoreleasePool new];
	[NSApplication sharedApplication];

	oc_osx_context_t *context = (oc_osx_context_t*) _context;
	context->openCapture = [[OpenCapture alloc] init];
	if (video != NULL)
	{
		QTCaptureDevice *videoDevice = video->native;
		[context->openCapture setVideoDevice:videoDevice];
		[context->openCapture setVideoCallback: videoCallback];
		[context->openCapture setContext:context];
		[context->openCapture startCapture];
	}
	//[NSApp run];
	
	while (1)
	{
		[[NSRunLoop currentRunLoop] runUntilDate: [NSDate dateWithTimeIntervalSinceNow: 1]];
	}
	
}