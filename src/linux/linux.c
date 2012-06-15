#include <opencapture.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <linux/videodev2.h>
#include "linux.h"

int is_capture_device(int fd)
{
        int ret = 0;
        struct v4l2_capability cap;
        if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == 0)
                if (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)
                        ret = 1;
        return ret;
}

int context_open_device(const char *name)
{
	int ret = open(name, O_RDWR | O_NONBLOCK);
	return ret;
}

int context_init_device(int fd)
{
	int ret = 0;
	return ret;
}

int context_start_capturing(int fd)
{
	int ret = 0;
	return ret;
}

int context_stop_capturing(int fd)
{
	int ret = 0;
	return ret;
}

int context_uninit_device(void)
{
	int ret = 0;
	return ret;
}

int context_close_device(int fd)
{
	int ret = 0;
	return ret;
}

oc_context_t* oc_context_create()
{
	oc_context_linux_t *context = (oc_context_linux_t*) malloc(sizeof(oc_context_linux_t));
	if (context)
		OC_INIT_CONTEXT(context);
	return context;
}

void oc_context_destroy(oc_context_t *_context)
{
    oc_context_linux_t *context = (oc_context_linux_t*) _context;
    free(context);
}

/* check_devices:
 * @dev_pfx  - video(audio) device path prefix, i.e. "/dev/video"
 * @dev_list - pointer to device list
 */
void check_devices(const char *dev_pfx, oc_device_list_t *dev_list)
{
	int i;
	char devname[DEVNAME_LEN];
	struct stat stat_buf;

	for (i=0; i < MAXDEV; i++) {
		snprintf(devname, DEVNAME_LEN-1, "%s%d", dev_pfx, i);
		if (stat(devname, &stat_buf) == 0) {	//File exist
			if (S_ISCHR(stat_buf.st_mode) &&	//char device
					major(stat_buf.st_rdev) == V4L_DEV_MAJOR) {	//v4l device
				dev_list->count++;
				dev_list->list = (oc_device_t **)realloc(dev_list->list,
									(i+1)*sizeof(oc_device_t));
				dev_list->list[i] =  malloc(sizeof(oc_device_t));
				dev_list->list[i]->name = malloc(DEVNAME_LEN);
				//or malloc(strlen(devname)+1)
				memcpy(dev_list->list[i]->name, devname, DEVNAME_LEN);
				//dev_list->list[i]->id?
				//dev_list->list[i]->native?
			}
		} else break;
	}
}

oc_device_list_t* oc_device_list_by_type(oc_context_t *_context, int type)
{
	oc_device_list_t *deviceList = malloc(sizeof(oc_device_list_t));

	deviceList->count = 0;

	if (type & OC_VIDEODEV_TYPE) check_devices(VIDEODEV_PFX, deviceList);
	if (type & OC_AUDIODEV_TYPE) check_devices(AUDIODEV_PFX, deviceList);


	return deviceList;
}

void oc_cli_monitor_video(const char *device_id)
{
	printf("monitor video device (not implemented yet): '%s'\n", device_id);
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

