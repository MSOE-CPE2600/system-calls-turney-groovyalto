/**************************************************************************************************************
 * Filename: info.c
 * Assignment: Lab 9: System Calls
 * Class Section: 121
 * Author: Alex Toma
 * Date: 11/05/2024
 **************************************************************************************************************/

// info.c

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>

int main(int argc, char* argv[])
{
    // get the current time in nanoseconds
    struct timespec currentTime;
    if (clock_gettime(CLOCK_REALTIME, &currentTime) == 0) {
        struct tm localTime;
        if (localtime_r(&currentTime.tv_sec, &localTime) != NULL) {
            double nanoseconds = (localTime.tm_hour * 3600 + localTime.tm_min * 60 + localTime.tm_sec) * 1e9 + currentTime.tv_nsec;
            printf("Current Time in Nanoseconds(ns): %.0f ns\n", nanoseconds);
        }
    }

    // get the system's network hostname
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0 && hostname[0] != '\0') {
        printf("Hostname: %s\n", hostname);
    }

    // get system information using uname
    struct utsname sysInfo;
    if (uname(&sysInfo) == 0) {
        if (sysInfo.sysname[0] != '\0') {
            printf("Operating System: %s\n", sysInfo.sysname);
        }
        if (sysInfo.release[0] != '\0') {
            printf("Kernel Release: %s\n", sysInfo.release);
        }
        if (sysInfo.version[0] != '\0') {
            printf("Kernel Version: %s\n", sysInfo.version);
        }
        if (sysInfo.machine[0] != '\0') {
            printf("Hardware Architecture: %s\n", sysInfo.machine);
        }
    }

    // get the number of cpus
    int numCPUs = get_nprocs();
    if (numCPUs > 0) {
        printf("Number of Processors: %d\n", numCPUs);
    }

    // get memory information with sysconf
    long pageSize = getpagesize();
    long totalPages = sysconf(_SC_PHYS_PAGES);
    long freePages = sysconf(_SC_AVPHYS_PAGES);

    if (totalPages > 0 && pageSize > 0) {
        long totalMemory = totalPages * pageSize;
        printf("Total Amount of Physical Memory in Bytes: %ld\n", totalMemory);
    }
    
    if (freePages > 0 && pageSize > 0) {
        long freeMemory = freePages * pageSize;
        printf("Total Amount of Free Memory in Bytes: %ld\n", freeMemory);
    }

    return 0;
}