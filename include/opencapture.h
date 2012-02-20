#ifndef OPENCAPTURE_H
#define OPENCAPTURE_H

typedef struct
{
	const char *id;
	const char *name;
} oc_device_t;

typedef struct
{
	oc_device_t **list;
	int count;
} oc_device_list_t;

typedef void oc_context_t;

oc_context_t* oc_context_create();
void oc_context_destroy(oc_context_t *context);

oc_device_list_t*  oc_device_list(oc_context_t *context);
oc_device_list_t*  oc_device_list_video(oc_context_t *context);
oc_device_list_t*  oc_device_list_audio(oc_context_t *context);

void oc_start(oc_context_t *context, oc_device_t *device);

#endif