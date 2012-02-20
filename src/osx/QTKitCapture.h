#import <Cocoa/Cocoa.h>
#import <QTKit/QTCaptureSession.h>
#import <QTKit/QTCaptureDevice.h>
#import <QTKit/QTCaptureDeviceInput.h>
#import <QTKit/QTMedia.h>
#import <opencapture.h>

@interface QTKitCapture : NSObject {
    QTCaptureSession *mCaptureSession;
    QTCaptureDeviceInput *mCaptureDeviceInput;
}

- (void)startCapture;

@end

typedef struct {
	NSAutoreleasePool *pool;
} oc_osx_context_t;

oc_device_list_t* oc_device_list_all(oc_context_t *_context, int type);