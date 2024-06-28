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

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef void* rtlsdr_dev_t;
#include "convenience.h"
#include "rtl_ais.h"

void usage(void)
{
	fprintf(stderr,
		"sdr check, a simple return of sdr devices in json format\n"
		"\n");
	exit(1);
}

static volatile int do_exit = 0;
static void sighandler(int signum)
{
        signum = signum;
	fprintf(stderr, "Signal caught, exiting!\n");
	do_exit = 1;
}

int main(int argc, char **argv)
{
#ifndef WIN32
	struct sigaction sigact;

	sigact.sa_handler = sighandler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGTERM, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
	sigaction(SIGPIPE, &sigact, NULL);
#else
	signal(SIGINT, sighandler);
	signal(SIGTERM, sighandler);
#endif
        int opt;
	
       
	while ((opt = getopt(argc, argv, "?")) != -1)
	{
		switch (opt) {
		
		case '?':
		default:
			usage();
			return 2;
		}
	}


	rtl_ais_start();

        
	  

	return 0;
}
