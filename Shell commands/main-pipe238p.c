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

    //variable declaration
    int pid1, pid2, res;
    int p1[2], p2[2];

    //variable initialization for exec
    char *ls_argv[2] = {"ls", 0};
    char *grep_argv[3] = {"grep", "main", 0};
    char *wc_argv[2] = {"wc", 0};

    //creating pipes
    if(pipe(p1) == -1){
        perror("Error while creating pipe");
        exit(1);
    }

    if(pipe(p2) == -1){
        perror("Error while creating pipe");
        exit(1);
    }
    
    //create 1st child process
    pid1 = fork();

    if(pid1 < 0){
        perror("Error in creating child process");
        exit(1);
    }

    if(pid1 == 0){
        
        //set appropriate file descriptors towrite into pipe by ls
        close(1);
        dup(p1[1]);

        //close all pipes
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        res = execvp(ls_argv[0], ls_argv);
        if(res == -1){
            perror("Error executing ls system call");
            exit(1);
        }
    }
    else{
        //wait(NULL);

        //create 2nd child process
        pid2 = fork();
        
        if(pid2 < 0){
            perror("Error in creating child process");
            exit(1);
        }

        if(pid2 == 0){
            //set appropriate file descriptors to read o/p of ls and write into pipe by grep
            close(0);
            dup(p1[0]);
            close(1);
            dup(p2[1]);

            //close all pipes
            close(p1[0]);
            close(p1[1]);
            close(p2[0]);
            close(p2[1]);

            res = execvp(grep_argv[0], grep_argv);
            if(res == -1){
                perror("Error executing grep system call");
                exit(1);
            }

         }
         else{
            //wait(NULL);

            //set appropriate file descriptors to read o/p of grep
            close(0);
            dup(p2[0]);

            //close all pipes
            close(p1[0]);
            close(p1[1]);
            close(p2[0]);
            close(p2[1]);

            res = execvp(wc_argv[0], wc_argv);
            if(res == -1){
                perror("Error executing wc system call");
                exit(1);
            }
         }
    }
    
    //wait for child processes to execute
    //wait(NULL);
    //wait(NULL);

    exit(0);
}