#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

int
main(void)
{
    /* Insert your code here */
    
    //initializing variables to execute ls in exec
    char *argv[2];

    argv[0] = "ls";
    argv[1] = 0;

    //variables declaration
    int fd_write;

    //close std output file descriptor
    if(close(1) == -1){
        perror("Error closing std output file decriptor");
    }

    //open file for redirecting output of ls
    fd_write = open("y.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    if(fd_write == -1){
        perror("Error opening file for writing ls output");
    }

    //execute ls in child process
    int res = execvp("ls", argv);
    if(res == -1){
        perror("Error in executing exec system call");
    }

    exit(0);
}