#import <stdio.h>
#import <stdlib.h>
#import <opencapture.h>
#import <Cocoa/Cocoa.h>

@interface OCDisplay : NSImageView
{
}

- (float)randVar;

@end

@implementation OCDisplay

- (float)randVar; { return ( (float)(rand() % 10000 ) / 10000.0); } // end randVar

int count = 0;
	
@end

OCDisplay *display;

void video_callback(oc_context_t *context, int width, int height, char *data) 
{
	unsigned char *data2 = malloc(width*height*3);
	oc_convrert_yuv442_to_rgb24((const unsigned char*) data, data2, width, height);

	NSImage *image = [[NSImage alloc] initWithSize:NSMakeSize(width,height)];
	NSBitmapImageRep *imageRep;
	imageRep = [[NSBitmapImageRep alloc]
		initWithBitmapDataPlanes:&data2
		pixelsWide:width
		pixelsHigh:height
		bitsPerSample:8
		samplesPerPixel:3
		hasAlpha:NO
		isPlanar:NO
		colorSpaceName:NSDeviceRGBColorSpace
		bytesPerRow:width * 3
		bitsPerPixel:24];

	[image addRepresentation:imageRep];
	[[display image] release];
	[display setImage: image];
	free(data2);
}

void oc_cli_monitor_video(const char *device_id)
{
	printf("start monitoring device: '%s'\n", device_id);

	[NSAutoreleasePool new];
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    id menubar = [[NSMenu new] autorelease];
    id appMenuItem = [[NSMenuItem new] autorelease];
    [menubar addItem:appMenuItem];
    [NSApp setMainMenu:menubar];
    id appMenu = [[NSMenu new] autorelease];
    id appName = @"OpenCapture - Monitor Video";
    id quitTitle = @"Quit OpenCapture";
    id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle
        action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
    [appMenu addItem:quitMenuItem];
    [appMenuItem setSubmenu:appMenu];
    id window = [[[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 640, 480)
        styleMask:NSTitledWindowMask|NSClosableWindowMask backing:NSBackingStoreBuffered defer:NO]
            autorelease];
    [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
	[window setReleasedWhenClosed: YES];
    [window setTitle:appName];
	
	display = [[OCDisplay alloc] init];

	[window setContentView: display];
    [window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
    
    oc_context_t *context = oc_context_create();
	oc_device_t *device = NULL;
	if (oc_device_find_by_id(context, device_id, &device) != 0)
	{
		printf("can't find device: '%s'\n", device_id);
		return;
	}
	printf("device: %s\n", device->name);
	oc_start(context, device, video_callback, NULL);
    //[NSApp run];
}
