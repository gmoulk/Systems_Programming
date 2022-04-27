#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <list>
#include <string>

#include  <fcntl.h>
#include  <unistd.h>
#include  <sys/stat.h>

int getLine(char* line,int fd);

int main(){
    // FILE* fp;
    // char* line = NULL;
    // size_t len = 0;
    // size_t read;
    
    // fp = fopen("hello","r");
    // if(fp == NULL)
    //     exit(1);

    // while((read = getline(&line,&len,fp)) != -1){
    //     //printf("%s",line);
    //     printf("Domain:");
    //     char* token = NULL;
    //     token = strstr(line,"/");
    //     if(token == NULL)
    //         continue;
    //     token = token + 2;
    //     //printf("%s\n",token);
    //     char* tokentemp = strstr(token,"www.");
    //     if(tokentemp != NULL){
    //         token = tokentemp;
    //         token = token + 4;
    //         //printf("%s\n",token);
    //     }
    //     tokentemp = strtok(token,"/");
    //     if(tokentemp != NULL){
    //         token = tokentemp;
    //         token = strtok(token,"/");
    //     }
    //     printf("%s\n",token); 
    // }
    // fclose(fp);
    // if(line)
    //     free(line);
    // return 0;
    int fd;
    char* buff;
    fd = open("hello", O_RDONLY );
    getLine(buff,fd);
    //printf("%s\n",buff);
    return 0;
}

int getLine(char* line,int fd){
    int now = 0;
    line = (char*)malloc(1);
    read(fd,line,1);
    if(line[now] == EOF || line[now] == '\n')
        return now + 1;
    line = (char*)realloc(line,(now + 1)*2);
    while(line[now] != EOF && line[now] != '\n'){
        now++;
        // printf("line now %c\n",line[now]);
        read(fd,line + now,1);
        char charnow = line[now];
        line = (char*)realloc((void*)line,now + 1);
    }
    line[now] = 0;
    printf("%s\n",line);

    now = 0;
    line = (char*)malloc(1);
    read(fd,line,1);
    if(line[now] == EOF || line[now] == '\n')
        return now + 1;
    line = (char*)realloc(line,(now + 1)*2);
    while(line[now] != EOF && line[now] != '\n'){
        now++;
        // printf("line now %c\n",line[now]);
        read(fd,line + now,1);
        char charnow = line[now];
        line = (char*)realloc((void*)line,now + 1);
    }
    line[now] = 0;
    printf("%s",line);
    return now + 1;
}