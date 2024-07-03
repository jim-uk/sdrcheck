#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#define _USE_MATH_DEFINES
#endif

#include <math.h>

#include "rtl-sdr.h"


void verbose_device_search(char *s)
{
	int i, device_count, device, offset;
	char *s2;
	char vendor[256], product[256], serial[256];
	device_count = rtlsdr_get_device_count();
	if (!device_count) {
		fprintf(stdout,"{\"numberofdevices\":0,\"devices\":[],\"error\":\"No Devices Found\"}");
	}else{
		//fprintf(stderr, "Found %d device(s):\n", device_count);
		fprintf(stdout,"{\"numberofdevices\":%d,\"devices\":[", device_count);
		for (i = 0; i < device_count; i++) {
			vendor[0]='\0';
			product[0]="\0";
			serial[0]='\0';
			rtlsdr_get_device_usb_strings(i, vendor, product, serial);
			//check to make sure no illegal characters
			checkChars(vendor);
			checkChars(product);
			checkChars(serial);

			//fprintf(stdout, "  %d:  %s, %s, SN: %s\n", i, vendor, product, serial);
			if (i>0)
				fprintf(stdout,",");
			fprintf(stdout, "{\"index\": %d, \"vendor\": \"%s\", \"product\":\"%s\", \"serial\":\"%s\"}",i, vendor, product, serial );
		}
		fprintf(stdout, "]}");
	}
}

void checkChars(char *in){
	size_t length = strlen(in); 

	for (size_t i = 0; i < length; i++)
	{
		if (in[i]==0){
			break;
		}
		if (in[i]<32 || in[i]>127){
			in[i]=42;
		}
	}
	}
}

