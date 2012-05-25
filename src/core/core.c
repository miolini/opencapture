#include <opencapture.h>
#include <stdio.h>
#include <string.h>

oc_device_list_t* oc_device_list_by_type(oc_context_t *context, int type);

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