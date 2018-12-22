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
main(int argc,char* argv[])
{
  /* Insert your code here */
  
    ssize_t bytes_read, bytes_written;

    //Check number of arguments
	if(argc!=3){
		fprintf(stderr, "Missing arguments! Please provide all required arguments.\n");
		exit(1);
	}

    //Open file to read
	int fd_read = open(argv[1], O_RDONLY, S_IRGRP | S_IROTH | S_IRUSR);
	
	if(fd_read < 0){
		perror("Error opening the specified file for reading");
		exit(1);
	}

    //Initialize buffer
	char* buffer = malloc(1024*sizeof(char));
    int byte_count = 1024*sizeof(char);

    //Open file to write
    int fd_write = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    if(fd_write < 0){
        perror("Error opening the specified file for writing");
		exit(1);
    }

    //Read and write to file
    while((bytes_read = read(fd_read, buffer, byte_count)) > 0){
        bytes_written = write(fd_write, buffer, bytes_read);

        if(bytes_written < 0){
            perror("Error writing to file");
        }
    }

    //Close files
    if(close(fd_read) == -1){
        perror("Error closing read file");
    }

    if(close(fd_write) == -1){
        perror("Error closing write file");
    }

    exit(0);
}
