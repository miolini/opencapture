//
//  opencapture_ios.m
//  opencapture_ios
//
//  Created by Artem Miolini (miolini@gmail.com) on 29.05.12.
//  Copyright (c) 2012 Artem Miolini (miolini@gmail.com. All rights reserved.
//

#import "opencapture_ios_lib.h"
#import <stdlib.h>

@implementation OpenCapture

@synthesize videoDevice;
@synthesize context;
@synthesize videoCallback;


- (void)startCapture
{
    NSError *error;
	NSLog(@"start capture");
    captureSession = [[AVCaptureSession alloc] init]; 
    if(videoDevice) {
        videoInput = [[AVCaptureDeviceInput alloc] initWithDevice:videoDevice error:&error];
        if (videoInput == nil) {
            NSLog(@"Error to create camera capture:%@",error);
            return;
        }
		AVCaptureVideoDataOutput *videoOutput = [[AVCaptureVideoDataOutput alloc] init];
        dispatch_queue_t captureQueue=dispatch_queue_create("catpureQueue", NULL);
        [videoOutput setSampleBufferDelegate:self queue:captureQueue];
        videoOutput.videoSettings = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithUnsignedInt:kCVPixelFormatType_32BGRA], (id)kCVPixelBufferPixelFormatTypeKey,
                                     nil];
        [captureSession setSessionPreset:AVCaptureSessionPresetHigh];
        [captureSession addInput:videoInput];
        [captureSession addOutput:videoOutput];
    } 
	[captureSession startRunning];
	printf("capture session runned\n");
}



- (void)captureOutput:(AVCaptureOutput *)captureOutput 
didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
       fromConnection:(AVCaptureConnection *)connection;
{
	if (self->videoCallback == NULL) return;

    
    CVImageBufferRef cvimgRef = CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress(cvimgRef,0);
    int width=CVPixelBufferGetWidth(cvimgRef);
    int height=CVPixelBufferGetHeight(cvimgRef);
    char *buf = (char *) CVPixelBufferGetBaseAddress(cvimgRef);
    NSLog(@"new frame %dx%d", width, height);
    self->videoCallback(context, width, height, buf);
}


@end

oc_context_t* oc_context_create()
{
	oc_ios_context_t *context = malloc(sizeof(oc_ios_context_t));
	return context;
}

void oc_context_destroy(oc_context_t *_context)
{
	oc_ios_context_t *context = (oc_ios_context_t*) _context;
	free(context);
}

oc_device_list_t* oc_device_list_by_type(oc_context_t *_context, int type)
{
	NSArray *list;

	if (type == 0)
		list = [AVCaptureDevice devices];
	else if (type == 1)
		list = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
	else if (type == 2)
		list = [AVCaptureDevice devicesWithMediaType:AVMediaTypeAudio];
    
	oc_device_list_t *devices = malloc(sizeof(oc_device_list_t));
	devices->count = [list count];
	devices->list = malloc(sizeof(oc_device_t)*devices->count);
	int i;
	for(i=0; i < devices->count; i++)
	{
		AVCaptureDevice *captureDevice = [list objectAtIndex:i];
		oc_device_t *device = malloc(sizeof(oc_device_t));
		device->id = [[captureDevice uniqueID] UTF8String];
		device->name = [[captureDevice localizedName] UTF8String];
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
    
	oc_ios_context_t *context = (oc_ios_context_t*) _context;
	context->openCapture = [[OpenCapture alloc] init];
	if (video != NULL)
	{
		AVCaptureDevice *videoDevice = video->native;
		[context->openCapture setVideoDevice:videoDevice];
		[context->openCapture setVideoCallback: videoCallback];
		[context->openCapture setContext:context];
		[context->openCapture startCapture];
	}	
}
