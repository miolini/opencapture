//
//  opencapture_ios.m
//  opencapture_ios
//
//  Created by Artem Miolini (miolini@gmail.com) on 19.05.12.
//  Copyright (c) 2012 Artem Miolini (miolini@gmail.com). All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <QTKit/QTKit.h>
#import <opencapture.h>
#import "../core/core.h"

@interface OpenCapture : NSObject {
	QTCaptureSession            *captureSession;
	QTCaptureMovieFileOutput    *movieOutput;
	QTCaptureDeviceInput        *videoInput;
	QTCaptureDevice 			*videoDevice;
	QTCaptureDeviceInput        *audioInput;
	oc_context_t				*context;
	CVImageBufferRef			frameBuffer;
	OC_CALLBACK(videoCallback);
}

@property(retain, nonatomic) QTCaptureDevice	*videoDevice;
@property(nonatomic) oc_context_t				*context;
@property(nonatomic) OC_CALLBACK(videoCallback);

- (void)startCapture;
- (void)captureOutput:(QTCaptureOutput *)captureOutput 
	didOutputVideoFrame:(CVImageBufferRef)videoFrame 
	withSampleBuffer:(QTSampleBuffer *)sampleBuffer 
	fromConnection:(QTCaptureConnection *)connection;

@end

typedef struct {
	NSAutoreleasePool *pool;
	OpenCapture *openCapture;
} oc_osx_context_t;