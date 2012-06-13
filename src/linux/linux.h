#ifndef OC_LINUX_H
#define OC_LINUX_H

#define VIDEODEV_PFX    "/dev/video"
#define AUDIODEV_PFX    "/dev/radio"
#define DEVNAME_LEN     16
#define MAXDEV		64      	//See ~linux/Documentation/devices.txt

#define OC_VIDEODEV_TYPE	1
#define OC_AUDIODEV_TYPE	(1 << 1)

typedef struct {
	int (*open_device)(const char *name);
	int (*init_device)(int fd);
	int (*start_capturing)(int fd);
	int (*stop_capturing)(int fd);
	int (*uninit_device)(void);
	int (*close_device)(int fd);
} oc_context_linux_t;

#define	OC_INIT_CONTEXT(oc_context)						\
	do {									\
		oc_context->open_device 	= oc_context##_open_device;	\
		oc_context->init_device 	= oc_context##_init_device;	\
		oc_context->start_capturing	= oc_context##_start_capturing;	\
		/*TODO: main_looping*/						\
		oc_context->stop_capturing	= oc_context##_stop_capturing;	\
		oc_context->uninit_device	= oc_context##_uninit_device;	\
		oc_context->close_device	= oc_context##_close_device;	\
	} while(0)
#endif

