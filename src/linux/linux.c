#include <opencapture.h>
#include "linux.h"
#include <stdio.h>
#include <stdlib.h>

oc_context_t* oc_context_create()
{
    oc_context_linux_t *context = (oc_context_linux_t*) malloc(sizeof(oc_context_linux_t));
    return context;
}

void oc_context_destroy(oc_context_t *_context)
{
    oc_context_linux_t *context = (oc_context_linux_t*) _context;
    free(context);
}

oc_device_list_t* oc_device_list_by_type(oc_context_t *_context, int type)
{
    oc_device_list_t *deviceList = malloc(sizeof(oc_device_list_t));
    deviceList->count = 0;
    return deviceList;
}

void oc_device_list_destroy(oc_device_list_t *devices)
{
    if (devices->count > 0)
    {
	int i;
	for(i=0;i<devices->count;i++)
	{
	    oc_device_t *device = devices->list[i];
	    free(device);
	}
	free(devices->list);
    }
    free(devices);
}