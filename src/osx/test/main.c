#include <stdio.h>
#include <opencapture.h>

int main() {
	printf("OpenCapture Test\n");
	oc_context_t *oc_context = oc_context_create();
	oc_device_list_t *deviceList = oc_device_list(oc_context);
	for(int i=0;i<deviceList->count;i++)
	{
		oc_device_t *device = deviceList->list[i];
		printf("device_id %s\n", device->id);
	}
	oc_context_destroy(oc_context);
	return 0;
}