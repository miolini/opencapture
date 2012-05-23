#import <Cocoa/Cocoa.h>
#import <QTKit/QTKit.h>
#import <opencapture.h>

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

oc_device_list_t* oc_device_list_all(oc_context_t *_context, int type);
void oc_start(oc_context_t *context, oc_device_t *video, OC_CALLBACK(videoCallback), oc_device_t *audio);