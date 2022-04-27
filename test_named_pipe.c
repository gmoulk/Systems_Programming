#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <signal.h>
#include <fcntl.h>
extern int errno;

void workerPart(void);

#define PERMS 0666

int main(){
    if((mkfifo("jt",PERMS) < 0) && (errno != EEXIST)){
        perror("error creating fifo");
    }
    int pipeFd;
    printf("nope!\n");
    if((pipeFd = open("jt",O_RDONLY)) < 0){
        printf("at least we didnt made fifo!\n");
        perror("can't open read fifo");
    }        
    int workerPid;
    int workerStatus;
    printf("at least we made fifo!\n");
    if((workerPid = fork()) == -1){
        perror("fork");
        exit(1);
    }

    if(workerPid != 0){
        if(wait(&workerStatus) != workerPid){
            perror("wait");
            exit(1);
        }
    }
    else{
        workerPart();
        exit(1);
    }
    close(pipeFd);
}

void workerPart(){
    printf("worker doing its part!!!\n");
}