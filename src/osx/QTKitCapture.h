#import <Cocoa/Cocoa.h>
#import <QTKit/QTCaptureSession.h>
#import <QTKit/QTCaptureDevice.h>
#import <QTKit/QTCaptureDeviceInput.h>

@interface QTKitCapture : NSObject {
    QTCaptureSession *mCaptureSession;
    QTCaptureDeviceInput *mCaptureDeviceInput;
}

- (void)startCapture;

@end
