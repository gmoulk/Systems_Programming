#include "sniffer.hpp"

extern char* ibuff[6];
extern pid_t lpid;
extern queue<workers> wk_queue;

void end(int signum){
    //Ending the Manager and killing the childs
    while(!wk_queue.empty()){
        workers wk = wk_queue.front();
        kill(wk.pid,SIGKILL);
        wk_queue.pop();
    }
    kill(lpid,SIGKILL);
    exit(0);
}