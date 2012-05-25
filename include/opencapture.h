#ifndef OPENCAPTURE_H
#define OPENCAPTURE_H

typedef void oc_context_t;

typedef struct
{
	const char *id;
	const char *name;
    int type;
	void *native;
} oc_device_t;

typedef struct
{
	oc_device_t **list;
	int count;
} oc_device_list_t;

typedef struct
{
	oc_device_t *videoInput;
	oc_device_t *audioInput;
	void *session;
} oc_session_t;



#define OC_CALLBACK(func) void (*func)(oc_context_t *context, int width, int height, char *data)

oc_context_t* oc_context_create();
void oc_context_destroy(oc_context_t *context);

oc_device_list_t*  oc_device_list(oc_context_t *context);
oc_device_list_t*  oc_device_list_video(oc_context_t *context);
oc_device_list_t*  oc_device_list_audio(oc_context_t *context);
int oc_device_find_by_id(oc_context_t *context, const char *name, oc_device_t **device);
void oc_device_list_destroy(oc_device_list_t *device);

void oc_start(oc_context_t *context, oc_device_t *videoInput, OC_CALLBACK(videoCallback), oc_device_t *audioInput);

#define CLAMP(value) value > 255 ? 255 : (value < 0 ? 0 : value) 
void oc_convrert_yuv442_to_rgb24(const unsigned char* source, unsigned char* destination, 
                                 unsigned long width, unsigned long height);


#endif