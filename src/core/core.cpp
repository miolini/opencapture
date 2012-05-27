#include "core.h"
#include <string.h>

oc_device_list_t* oc_device_list(oc_context_t *_context)
{
	return oc_device_list_by_type(_context, 0);
}

oc_device_list_t* oc_device_list_video(oc_context_t *_context)
{
	return oc_device_list_by_type(_context, 1);
}

oc_device_list_t* oc_device_list_audio(oc_context_t *_context)
{
	return oc_device_list_by_type(_context, 2);
}

int oc_device_find_by_id(oc_context_t *context, const char *id, oc_device_t **device)
{
	oc_device_list_t *deviceList = oc_device_list_video(context);
	oc_device_t *current_device = NULL;
	int i;
	for(i=0;i<deviceList->count;i++)
	{
		current_device = deviceList->list[i];
		if (strcmp(current_device->id, id) == 0) break;
		current_device = NULL;
	}
	if (current_device == NULL) 
	{
		return 1;
	}
	*device = current_device;
	return 0;
}


void oc_convrert_yuv442_to_rgb24(const unsigned char* source, unsigned char* destination, 
                                 unsigned long width, unsigned long height)
{
	unsigned long i, c;
    int y1,y2,u,v;
    for(i = 0, c = 0; i < width * height * 2; i += 4, c += 6)
    {
		y1 = (source[i+1] - 16) * 298;
		y2 = (source[i+3] - 16) * 298;
		u = source[i] - 128;
		v = source[i+2] - 128;
        
		destination[c+0] = CLAMP((y1 + 409 * v + 128) >> 8);
		destination[c+1] = CLAMP((y1 - 100 * u - 208 * v + 128) >> 8);
		destination[c+2] = CLAMP((y1 + 516 * u + 128) >> 8);
        
        destination[c+3] = CLAMP((y2 + 409 * v + 128) >> 8);
		destination[c+4] = CLAMP((y2 - 100 * u - 208 * v + 128) >> 8);
		destination[c+5] = CLAMP((y2 + 516 * u + 128) >> 8);
    }
}
