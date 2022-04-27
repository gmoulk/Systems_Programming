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

#define PERMS 0666

struct worker{
    pid_t pid;
    char* name_of_pipe;
};
typedef struct worker* Worker;

int starting_files(void);
void workerPart(void);

int main(void){
    char inbuf[30];
    int p[2];
    pid_t pid,lpid;
    int lstatus;
    char* lbuff[3];
    // int numberOfStartingFilles = starting_files();
    // printf("OKOKOKOKOKOK!\n");
    // for(int i = 0; i < numberOfStartingFilles; i++){
    //     printf("OK!\n");
    //     Worker wk = malloc(sizeof(struct worker));
    //     if((wk->pid = fork()) == -1){
    //         perror("fork");
    //         exit(1);
    //     }
    //     int sizeOfString = i + 5;
    //     wk->name_of_pipe = malloc(sizeOfString);
    //     sprintf(wk->name_of_pipe,"pipe%d",i+1);
    //     printf("Just created worker with pid %d and named pipe %s",wk->pid,wk->name_of_pipe);
    // }
    if(pipe(p) == -1){
        //creating pipe
        perror("pipe call");
        exit(1);
    }

    switch (pid = fork())
    {
    case -1:
        perror("fork call");
        exit(2);
    case 0:
        close(p[0]);
        if((lpid = fork()) == -1){
            perror("fork");
            exit(1);
        }

        if(lpid != 0){
            printf("ending listener%d\n",getpid());
            if(wait(&lstatus) != lpid){
                perror("wait");
                exit(1);
            }
            exit(1);
        }
        else{
            printf("bts!\n");
            lbuff[0] = malloc(20);
            strcpy(lbuff[0],"inotifywait");
            lbuff[1] = malloc(5);
            strcpy(lbuff[1],".");
            lbuff[2] = NULL;
            dup2(p[1], STDOUT_FILENO);
            close(p[0]);
            close(p[1]);
            execvp("inotifywait",lbuff);
            printf("ending listener child %d",getpid());
            exit(1);
        }
        break;
    default:
        dup2(p[0], STDIN_FILENO);        
        int rsize = read(p[0],inbuf,20);
        printf("all ok!\n");
        printf("printing.... %.*s\n",rsize,inbuf);
        if((mkfifo(inbuf,PERMS) < 0) && (errno != EEXIST)){
            perror("error creating fifo");
        }
        int pipeFd;
        printf("nope!\n");
        // if((pipeFd = open(inbuf,O_RDONLY)) < 0){
        //     printf("at least we didnt made fifo!\n");
        //     perror("can't open read fifo");
        // }
        
        int workerPid;
        int workerStatus;
        printf("at least we made fifo!\n");
        if((workerPid = fork()) == -1){
            perror("fork");
            exit(1);
        }

        if(workerPid != 0){
            printf("aaaaa");
            if(wait(&workerStatus) != workerPid){
                perror("wait");
                exit(1);
            }
        }
        else{
            workerPart();
            printf("stoping worker!,pid:%d\n",getpid());
            exit(1);
            printf("heyyyyyy");
        }
        close(pipeFd);
        close(p[0]);
        close(p[1]);    
    }
    printf("ENDING....,ppid:%d\n",getpid());
    return 0;
}

int starting_files(void){
    pid_t pid,pid2;
    int p[2];
    char num[4];
    if(pipe(p) == -1){
        perror("pipe");
        exit(1);
    }
    if((pid = fork()) == -1){
        perror("fork");
        exit(1);
    }
    if((pid2 = fork()) == -1){
        perror("fork");
        exit(1);
    }
    if(pid != 0){
        close(p[0]);
        dup2(p[1],1);
        close(p[1]);
        execlp("ls","ls",NULL);
        perror("execlp");
        exit(2);
    }
    if(pid2 != 0){
        close(p[1]);
        dup2(p[0],0);
        close(p[0]);
        fgets(num,4,0);
        execlp("wc","wc","-l",NULL);    
    }
    printf("string is %s",num);
    return 1;
}

void workerPart(){
    printf("worker doing its part!!!\n");
}