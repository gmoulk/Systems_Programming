#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc,char** argv){
    int pid,status;
    char* buff[4];
    if((pid = fork()) == -1){
        perror("fork");
        exit(1);
    }

    if(pid != 0){
        if(wait(&status) != pid){
            perror("wait");
            exit(1);
        }
    }
    else{
        buff[0] = malloc(20);
        strcpy(buff[0],"inotifywait");
        buff[1] = malloc(5);
        strcpy(buff[1],"-m");
        buff[2] = malloc(5);
        strcpy(buff[2],argv[1]);
        buff[3] = NULL;
        execvp("inotifywait",buff);
        exit(1);
    }
    return 0;
}