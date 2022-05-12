#include "sniffer.hpp"

extern char* ibuff[6];
extern pid_t lpid,ipid;
extern queue<workers> wk_queue;

void end(int signum){
    //Ending the Manager and killing the childs
    for(int i = 0;i < 6; i++)
        free(ibuff[i]);
    while(!wk_queue.empty()){
        workers wk = wk_queue.front();
        kill(wk.pid,SIGKILL);
        wk_queue.pop();
    }
    kill(lpid,SIGKILL);
    kill(ipid,SIGKILL);
    exit(0);
}