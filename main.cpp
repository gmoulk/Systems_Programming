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

void end(int signum);

int main(int argc,char** argv){
    int p[2];
    if(pipe(p) == -1){
        //creating pipe
        perror("pipe call");
        exit(1);
    }
    signal(SIGINT,end);
    pid_t lpid,ipid;
    int istatus;
    char* ibuff[4];
    switch (lpid = fork()){
    case -1:
        perror("fork call");
        exit(2);
        break;
    case 0:
        close(p[0]);
        printf("child");
        if((ipid = fork()) == -1){
            perror("fork");
            exit(1);
        }

        if(ipid != 0){
            if(wait(&istatus) != ipid){
                perror("wait");
                exit(1);
            }
            exit(1);
        }
        else{
            printf("bts!\n");
            ibuff[0] = (char*) malloc(20);
            strcpy(ibuff[0],"inotifywait");
            ibuff[1] = (char*) malloc(5);
            strcpy(ibuff[1],"-m");
            ibuff[2] = (char*) malloc(5);
            strcpy(ibuff[2],argv[1]);
            ibuff[3] = NULL;
            dup2(p[1], STDOUT_FILENO);
            close(p[0]);
            close(p[1]);
            execvp("inotifywait",ibuff);
            printf("ending listener child %d",getpid());
            exit(1);
        }
        break;
    default:
        close(p[1]);printf("running....\n");
        while(1){
        
        }   
    }
    return 0;
}

void end(int signum){
    printf("ending...\n");
    exit(0);
}