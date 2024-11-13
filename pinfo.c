/**************************************************************************************************************
 * Filename: pinfo.c
 * Assignment: Lab 9: System Calls
 * Class Section: 121
 * Author: Alex Toma
 * Date: 11/05/2024
 **************************************************************************************************************/

// pinfo.c

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

int main(int argc, char* argv[])
{
    // make sure there are not too many arguments provided
    if (argc > 2) 
    {
        fprintf(stderr, "Error: Incorrect number of arguments. Please only provide 1 or no arguments\n");
        exit(1);
    }

    // determine process id (PID)
    pid_t pid;
    if (argc == 2)
    {
        pid = atoi(argv[1]);
    } else
    {
        pid = getpid();
    }

    // retrieve process priority
    int priority = getpriority(PRIO_PROCESS, pid);

    // get the scheduling policy 
    int schedPolicy = sched_getscheduler(pid);
    if (schedPolicy != 0)
    {
        perror("Error retrieving scheduling policy\n");
        exit(1);
    }

    // map the scheduling policy to a human readable string
    const char *schedMethod;
    switch (schedPolicy) 
    {
        case SCHED_FIFO:
            schedMethod = "SCHED_FIFO (Real-Time)";
            break;
        case SCHED_RR:
            schedMethod = "SCHED_RR (Round Robin)";
            break;
        case SCHED_OTHER:
            schedMethod = "SCHED_OTHER (Default)";
            break;
        case SCHED_BATCH:
            schedMethod = "SCHED_BATCH";
            break;
        case SCHED_IDLE:
            schedMethod = "SCHED_IDLE";
            break;
        default:
            schedMethod = "Unknown Scheduling Method";
            break;
    }

    // print the process information
    printf("Process Information:\n");
    printf("  PID: %d\n", pid);
    printf("  Priority: %d\n", priority);
    printf("  Scheduling Method: %s\n", schedMethod);

    return 0;
}