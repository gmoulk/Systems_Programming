#include "sniffer.hpp"

char* ibuff[6];
queue<workers> wk_queue;
char name_of_directory[4096];
pid_t lpid;

int main(int argc,char** argv){
    if(argc == 1){
        //Default parameter
        strcpy(name_of_directory,"./");
    }
    else if(argc == 3){
        strcpy(name_of_directory,argv[2]);
    }
    else{
        printf("Error at arguments:./sniffer [-p path]");
    }
    int p[2];
    if(pipe(p) == -1){
        //creating pipe
        perror("pipe call");
        exit(1);
    }
    //Crtl-C signal will trigger end function
    signal(SIGINT,end);
    int istatus;
    ibuff[0] = (char*) malloc(20);
    strcpy(ibuff[0],"inotifywait");
    ibuff[1] = (char*) malloc(5);
    strcpy(ibuff[1],"-m");
    ibuff[2] = (char*) malloc(5);
    strcpy(ibuff[2],"-e");
    ibuff[3] = (char*) malloc(20);
    strcpy(ibuff[3],"create,moved_to");
    ibuff[4] = (char*) malloc(4096);
    strcpy(ibuff[4],name_of_directory);
    ibuff[5] = NULL;
    char inbuff[4500];
    switch (lpid = fork()){
    case -1:
        //Fork failed
        perror("fork call");
        exit(2);
        break;
    case 0:
        dup2(p[1], STDOUT_FILENO);
        close(p[0]);
        close(p[1]);
        execvp("inotifywait",ibuff);
        exit(1);
        break;
    default:
        close(p[1]);
        //Manager takes control
        for(int i = 0;i < 6; i++)
            free(ibuff[i]);
        while(1){
            //dup2 in order to make parent read from pipe the names of file to change
            dup2(p[0], STDIN_FILENO);        
            int rsize = read(p[0],inbuff,4500);
            char* current_string = strtok(inbuff,"\n");
            printf("%s\n",inbuff);
            while(current_string != NULL){
                if(rsize != 0){
                    //find filename written in pipe
                    char* usefull_string = strtok(current_string," ");
                    usefull_string = strtok(NULL," ");
                    usefull_string = strtok(NULL," \n");
                    char temp[4096] = "/tmp/";
                    strcat(temp,usefull_string);
                    //create fifo inside temp
                    int readfd;
                    if(!wk_queue.empty()){
                        int workerstatus;
                        workers& test = wk_queue.front();
                        if(!test.stoped){
                            wk_queue.pop();
                            kill(test.pid,SIGCONT);
                            int fd = open(test.fifo.c_str(),O_WRONLY);
                            write(fd,usefull_string,4096);
                                while((waitpid(test.pid,&workerstatus,SIGCHLD)) == 0){                               
                                   
                                }
                                //Notified that worker stopped
                                close(fd);
                                test.stoped = 0;
                                wk_queue.push(test);
                        }
                        else{
                            //We don't have available workers make a new one!
                            int workerstatus;
                            if((mkfifo(temp,PERMS) < 0) && (errno != EEXIST)){
                                perror("error creating fifo");
                            }
                            int workerpid = fork();
                            if(workerpid == -1){
                                perror("Failed to fork");
                                return 1;
                            }
                        
                            if(workerpid == 0){
                                while (1)
                                {   
                                    if((readfd = open(temp,O_RDONLY)) < 0){
                                        perror("can't open read fifo");
                                    }
                                    worker(readfd);
                                    close(readfd);
                                    kill(getpid(),SIGSTOP);
                                } 
                            }
                            else{ 
                                if((readfd = open(temp,O_WRONLY)) < 0){
                                    perror("can't open write fifo");
                                }
                                write(readfd,usefull_string,4096);
                            }
                            while((waitpid(workerpid,&workerstatus,SIGCHLD)) == 0){                        
                                
                            }
                            //Push worker in queue
                            workers wk_new = {workerpid,0,temp};
                            wk_queue.push(wk_new);
                            close(readfd);
                        }
                    }
                    else{
                        //We don't have workers!
                        int workerstatus;
                        if((mkfifo(temp,PERMS) < 0) && (errno != EEXIST)){
                                perror("error creating fifo");
                        }
                        int workerpid = fork();
                        if(workerpid == -1){
                            perror("Failed to fork");
                            return 1;
                        }
                        if(workerpid == 0){
                            while (1)
                                {   
                                    if((readfd = open(temp,O_RDONLY)) < 0){
                                        perror("can't open read fifo");
                                    }
                                    worker(readfd);
                                    close(readfd);
                                    kill(getpid(),SIGSTOP);
                                } 
                        }
                        else{ 
                            if((readfd = open(temp,O_WRONLY)) < 0){
                                perror("can't open write fifo");
                            }
                            string fifo_name = std::string(temp);
                            write(readfd,usefull_string,4096);
                            while((waitpid(workerpid,&workerstatus,WUNTRACED)) == 0){
                                //Same as above
                            }
                            workers wk_new = {workerpid,0,fifo_name.c_str()};
                            wk_queue.push(wk_new);
                            close(readfd);
                        }
                    }
                    close(readfd);
                }
                current_string = strtok(NULL,"\n");
            }
                
            }
            
        }   
    return 0;
    }