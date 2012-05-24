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
	
//- (void)drawRect:(NSRect)rect {}
@end

OCDisplay *display;


float clamp(float value, float min, float max) 
{
	if (value > max) return max;
	else if (value < min) return min;
	else return value;
}

void convert_yuv442_2_rgb24(const unsigned char* source, unsigned char* destination, unsigned long width, unsigned long height)
{
    for(unsigned long i = 0, c = 0; i < width * height * 2; i += 4, c += 6)
    {
		int y1 = source[i];
		int y2 = source[i+2];
		int u = source[i+1];
		int v = source[i+3];

		destination[c+0] = y1 + (1.370705 * (v-128));
		destination[c+1] = y1 - (0.698001 * (v-128)) - (0.337633 * (u-128));
		destination[c+2] = y1 + (1.732446 * (u-128));

		destination[c+3] = y2 + (1.370705 * (v-128));
		destination[c+4] = y2 - (0.698001 * (v-128)) - (0.337633 * (u-128));
		destination[c+5] = y2 + (1.732446 * (u-128));
    }
}


void video_callback(oc_context_t *context, int width, int height, char *data) 
{
	printf("test: frame %dx%d captured\n", width, height);

	unsigned char *data2 = malloc(width*height*3);
	convert_yuv442_2_rgb24((const unsigned char*) data, data2, width, height);

	NSImage *image = [[NSImage alloc] initWithSize:NSMakeSize(width,height)];
	NSBitmapImageRep *imageRep;
	unsigned char *planes;
	int i;

	// prepare memory for image rep:
	planes = malloc (width * height * 3);
	for (i=0; i<width*height; i+=3) {
		planes[i+0] = data2[i+0];
		planes[i+width*height] = data2[i+width*height];
		planes[i+width*height*2] = data2[i+width*height*2];
	}

	imageRep = [[NSBitmapImageRep alloc]
		initWithBitmapDataPlanes:&planes
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
	[image lockFocusOnRepresentation:imageRep];
	[image unlockFocus];
	[[display image] release];
	free(planes);
	[display setImage: image];
//	[display drawRect: NSMakeRect(0, 0, width, height) ];
}

void oc_cli_montior_video(const char *device_id)
{
	printf("start monitoring device: '%s'\n", device_id);
	oc_context_t *context = oc_context_create();
	oc_device_t *device = NULL;
	if (oc_device_find_by_id(context, device_id, &device) != 0)
	{
		printf("can't find device: '%s'\n", device_id);
		return;
	}
	printf("device: %s\n", device->name);


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

	oc_start(context, device, video_callback, NULL);
    //[NSApp run];
}
