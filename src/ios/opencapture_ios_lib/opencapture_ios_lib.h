//
//  opencapture_ios.h
//  opencapture_ios
//
//  Created by Mynumber on 29.05.12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef opencapture_ios_lib_h
#define opencapture_ios_lib_h

#import "../../core/core.h"
#import <opencapture.h>
#import <CoreMedia/CoreMedia.h>
#import <AVFoundation/AVFoundation.h>

@interface OpenCapture : NSObject {
	AVCaptureSession            *captureSession;
	AVCaptureMovieFileOutput    *movieOutput;
	AVCaptureDeviceInput        *videoInput;
	AVCaptureDevice 			*videoDevice;
	AVCaptureDeviceInput        *audioInput;
	oc_context_t				*context;
	CVImageBufferRef			frameBuffer;
	OC_CALLBACK(videoCallback);
}

@property(retain, nonatomic) AVCaptureDevice	*videoDevice;
@property(nonatomic) oc_context_t				*context;
@property(nonatomic) OC_CALLBACK(videoCallback);

- (void)startCapture;
/*
- (void)captureOutput:(AVCaptureOutput *)captureOutput 
  didOutputVideoFrame:(CVImageBufferRef)videoFrame 
     withSampleBuffer:(AVCaptureVideoDataOutputSampleBuffer *)sampleBuffer 
       fromConnection:(AVCaptureConnection *)connection;
*/
- (void)captureOutput:(AVCaptureOutput *)captureOutput 
    didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
       fromConnection:(AVCaptureConnection *)connection;

@end

typedef struct {
	OpenCapture *openCapture;
} oc_ios_context_t;



#endif
