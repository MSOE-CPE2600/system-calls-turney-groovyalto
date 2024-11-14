/**************************************************************************************************************
 * Filename: finfo.c
 * Assignment: Lab 9: System Calls
 * Class Section: 121
 * Author: Alex Toma
 * Date: 11/05/2024
 **************************************************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

// helper functions

// display the file type
void display_file_type(mode_t mode) 
{
    printf("File Type: ");
    if (S_ISREG(mode)) printf("Regular File\n");
    else if (S_ISDIR(mode)) printf("Directory\n");
    else if (S_ISCHR(mode)) printf("Character Device\n");
    else if (S_ISBLK(mode)) printf("Block Device\n");
    else if (S_ISLNK(mode)) printf("Symbolic Link\n");
    else if (S_ISFIFO(mode)) printf("FIFO (Named Pipe)\n");
    else if (S_ISSOCK(mode)) printf("Socket\n");
    else printf("Unknown Type\n");
}

// display file permissions in a readable format
void display_permissions(mode_t mode) 
{
    printf("Permissions: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

// display last modification time
void display_modification_time(time_t mod_time) 
{
    struct tm *time_info = localtime(&mod_time);
    if (time_info == NULL) 
    {
        perror("Error formatting time");
        return;
    }
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info);
    printf("Last Modification: %s\n", buffer);
}

// main function

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        perror("Usage: Please provide a filename");
        exit(1);
    }

    struct stat file_info;
    if (stat(argv[1], &file_info) != 0) 
    {
        perror("Error accessing file");
        exit(1);
    }

    // display file type
    display_file_type(file_info.st_mode);

    // display file permissions
    display_permissions(file_info.st_mode);

    // display owner information
    printf("Owner UID: %d\n", file_info.st_uid);

    // display file size
    printf("File Size: %ld bytes\n", file_info.st_size);

    // display last modification time
    display_modification_time(file_info.st_mtime);

    return 0;
}