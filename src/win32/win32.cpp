#include "win32.h"
#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <DShow.h>

#pragma comment(lib, "strmiids")
#pragma comment(lib, "ole32")
#pragma comment(lib, "oleaut32")

void oc_cli_monitor_video(const char *device_id)
{
}

oc_context_t* oc_context_create()
{
    oc_context_win32_t *context = (oc_context_win32_t*) malloc(sizeof(oc_context_win32_t));
    return context;
}

void oc_context_destroy(oc_context_t *_context)
{
    oc_context_win32_t *context = (oc_context_win32_t*) _context;
    free(context);
}

HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum)
{
	// Create the System Device Enumerator.
	ICreateDevEnum *pDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

 if (SUCCEEDED(hr))
 {
  // Create an enumerator for the category.
  hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
  if (hr == S_FALSE)
  {
   hr = VFW_E_NOT_FOUND; // The category is empty. Treat as an error.
  }
  pDevEnum->Release();
 }
 return hr;
}


void DisplayDeviceInformation(IEnumMoniker *pEnum)
{
    IMoniker *pMoniker = NULL;
 
    while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
    {
        IPropertyBag *pPropBag;
        HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
        if (FAILED(hr))
        {
			printf("failed\n");
            pMoniker->Release();
            continue;  
        } 
 
        VARIANT var;
        VariantInit(&var);
 
        // Get description or friendly name.
        hr = pPropBag->Read(L"Description", &var, 0);
        if (FAILED(hr))
        {
            hr = pPropBag->Read(L"FriendlyName", &var, 0);
        }
        if (SUCCEEDED(hr))
        {
            printf("%S\n", var.bstrVal);
            VariantClear(&var); 
        }
 
        hr = pPropBag->Write(L"FriendlyName", &var);
 
        // WaveInID applies only to audio capture devices.
        hr = pPropBag->Read(L"WaveInID", &var, 0);
        if (SUCCEEDED(hr))
        {
            printf("WaveIn ID: %d\n", var.lVal);
            VariantClear(&var); 
        }
 
        hr = pPropBag->Read(L"DevicePath", &var, 0);
        if (SUCCEEDED(hr))
        {
            // The device path is not intended for display.
            printf("Device path: %S\n", var.bstrVal);
            VariantClear(&var); 
        }
 
        pPropBag->Release();
        pMoniker->Release();
    }
}


oc_device_list_t* oc_device_list_by_type(oc_context_t *_context, int type)
{
	oc_device_list_t *deviceList = (oc_device_list_t*) malloc(sizeof(oc_device_list_t));
	deviceList->count = 0;
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (SUCCEEDED(hr))
    {
        IEnumMoniker *pEnum;

        if (type == 0 || type == 1)
		{
			hr = EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnum);
			if (SUCCEEDED(hr))
			{
				DisplayDeviceInformation(pEnum);
				pEnum->Release();
			}
		}
		if (type == 0 || type == 2)
		{
			hr = EnumerateDevices(CLSID_AudioInputDeviceCategory, &pEnum);
			if (SUCCEEDED(hr))
			{
				DisplayDeviceInformation(pEnum);
				pEnum->Release();
			}
		}
        CoUninitialize();
	}
	else
	{
		printf("error: can't list capture devices with DirectShow\n");
	}
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
