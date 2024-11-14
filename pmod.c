/**************************************************************************************************************
 * Filename: pmod.c
 * Assignment: Lab 9: System Calls
 * Class Section: 121
 * Author: Alex Toma
 * Date: 11/05/2024
 **************************************************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define NICE 10

int main(int argc, char* argv[])
{
    // reduce priority by 10, check for errors
    int newPriority = nice(NICE);
    if (newPriority == -1 && errno != 0)
    {
        perror("ERROR: Failed to change priority\n");
        exit(1);
    }

    printf("Priority reducd by %d. new Priority is: %d\n", NICE, newPriority);

    // setup timespec struct for nanosleep
    struct timespec time;
    time.tv_sec = 1;          // 1 second
    time.tv_nsec = 837272638; // 837,272,638 nanoseconds

    // note: had to separate the second as otherwise it overflows the program

    // Sleep for the duration stated
    printf("Sleeping for %ld second(s) and %ld nanosecond(s) (or 1,837,272,638 ns)...\n", time.tv_sec, time.tv_nsec);
    if (nanosleep(&time, NULL) != 0) 
    {
        perror("ERROR: Nanosleep failed\n");
        exit(1);
    }

    // print a goodbye message
    printf("Goodbye! :)\n");

    return 0;
}