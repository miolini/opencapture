#include <stdio.h>
#include <opencapture.h>
#include "cli.h"
#include <string.h>

void oc_cli_print_help()
{
	printf("\t--help\n\t\tHelp information\n");
	printf("\t--list-all\n\t\tList all available devices\n");
	printf("\t--list-video\n\t\tList all available video devices\n");
	printf("\t--list-audio\n\t\tList all available audio devices\n");
	printf("\n");
	printf("\t--monitor-video <device_id>\n");
}

void oc_cli_print_devices(oc_context_t *oc_context, int deviceType)
{
	int i = 0;
	oc_device_list_t *devices;
	switch(deviceType) {
		case 0:
			devices = oc_device_list(oc_context);
			break;
		case 1:
			devices = oc_device_list_video(oc_context);
			break;
		case 2:
			devices = oc_device_list_audio(oc_context);
			break;
	}
	if (devices->count == 0) 
	{
		printf("error: devices not found\n");
		return;
	}
	for(i=0;i<devices->count;i++)
	{
		oc_device_t *device = devices->list[i];
		printf("device: name='%s', id='%s'\n", device->name, device->id);
	}

	oc_device_list_destroy(devices);
}

int main(int argc, char *argv[]) 
{
	oc_context_t *oc_context;
	printf("OpenCapture Library 0.1 Console\n");
	oc_context = oc_context_create();
	if (argc > 1) 
	{
		char *opt = argv[1];
		if (strcmp(opt,"--help") == 0)
			oc_cli_print_help();
		if (strcmp(opt,"--list-all") == 0) 
			oc_cli_print_devices(oc_context, 0);
		else if (strcmp(opt,"--list-video") == 0)
			oc_cli_print_devices(oc_context, 1);
		else if (strcmp(opt,"--list-audio") == 0)
			oc_cli_print_devices(oc_context, 2);
		else if (strcmp(opt,"--monitor-video") == 0) 
		{
			if (argc == 2) 
			{
				printf("error:\tfor monitor video need parameter: device_id\n");
				return -1;
			}
			oc_cli_monitor_video(argv[2]);
		}
		else 
			printf("Unknown option: %s\n, try read help (opencapture --help)", opt);
	}
	else {
		oc_cli_print_help();
	}
	oc_context_destroy(oc_context);
	printf("\n");
}
