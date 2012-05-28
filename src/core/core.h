#ifndef OPENCAPTURE_CORE_H
#define OPENCAPTURE_CORE_H

#include "../../include/opencapture.h"


oc_device_list_t*			oc_device_list_by_type(oc_context_t *_context, int type);
void						oc_device_list_insert(oc_device_list_t *deviceList, oc_device_t *device);


#endif