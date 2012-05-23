#include <stdio.h>
#include <stdlib.h>
#include <opencapture.h>
#include <jpeglib.h>

#define CAMERA_BUILTIN_ISIGHT "Built-in iSight"

int count = 0;

int write_jpeg_file( char *filename, int width, int height, unsigned char *raw_image )
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    FILE *outfile = fopen( filename, "wb" );
    if ( !outfile )
    {
        printf("Error opening output jpeg file %s\n!", filename );
        return -1;
    }
    cinfo.err = jpeg_std_error( &jerr );
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = width;  
    cinfo.image_height = height;
    cinfo.input_components = 3;

    //cinfo.in_color_space = JCS_YCbCr;
	cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults( &cinfo );
    jpeg_start_compress( &cinfo, TRUE );
    while( cinfo.next_scanline < cinfo.image_height )
    {
        row_pointer[0] = (unsigned char*) &raw_image[ cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
        jpeg_write_scanlines( &cinfo, row_pointer, 1 );
    }
    jpeg_finish_compress( &cinfo );
    jpeg_destroy_compress( &cinfo );
   	fclose( outfile );
    return 1;
}

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
	char *fileName = malloc(sizeof(char)*256);
	sprintf(fileName, "frames/frame_%d.jpg", count);

/*
	FILE *fp = fopen(fileName, "w");
	fwrite(data, 4, width*height, fp);
	fclose(fp);
*/
	unsigned char *data2 = malloc(width*height*3);
	convert_yuv442_2_rgb24((const unsigned char*) data, data2, width, height);
	write_jpeg_file(fileName, width, height, data2);
	//free(data2);
	//free(fileName);
	++count;
}

int main() 
{
	printf("OpenCapture Test\n");
	oc_context_t *oc_context = oc_context_create();
	oc_device_list_t *deviceList = oc_device_list_video(oc_context);
	oc_device_t *device = NULL;
	for(int i=0;i<deviceList->count;i++)
	{
		device = deviceList->list[i];
		if (device->name == CAMERA_BUILTIN_ISIGHT) break;
	}
	if (device == NULL) 
	{
		printf("Can't find %s", CAMERA_BUILTIN_ISIGHT);
		return -1;
	}
	oc_start(oc_context, device, video_callback, NULL);
	oc_context_destroy(oc_context);
	return 0;
}