/*
 * Copyright (C) 2012 by Kyle Keen <keenerd@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* a collection of user friendly tools
 * todo: use strtol for more flexible int parsing
 * */

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
			//fprintf(stdout, "  %d:  %s, %s, SN: %s\n", i, vendor, product, serial);
			if (i>0)
				fprintf(stdout,",");
			fprintf(stdout, "{\"index\": %d, \"vendor\": \"%s\", \"product\":\"%s\", \"serial\":\"%s\"}",i, vendor, product, serial );
		}
		fprintf(stdout, "]}");
	}
}

// vim: tabstop=8:softtabstop=8:shiftwidth=8:noexpandtab
