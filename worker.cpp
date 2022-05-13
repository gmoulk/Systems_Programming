#include "sniffer.hpp"

extern char name_of_directory[4096];

void worker(int fd){
    char name_of_file[4096];
    read(fd,name_of_file,4096);
    char actual_name_of_file[4096];
    strcpy(actual_name_of_file,name_of_directory);
    strcat(actual_name_of_file,name_of_file);
        map<string, insert_str> num_of_apears;
        char* line;
        int charsRead;
        fd = open(actual_name_of_file, O_RDONLY );
        line = (char*)malloc(1);
        charsRead = read(fd,line,1);
        int now = 0;
        line = (char*)realloc(line,(now + 1)*2);
        while(line[now] != EOF && line[now] != '\n'){
            now++;
            read(fd,line + now,1);
            char charnow = line[now];
            line = (char*)realloc((void*)line,now + 2);
        }
        line[now] = 0;
        while(charsRead != 0){
            char* token = NULL;
            token = strstr(line,"http://");
            if(token == NULL){
                now = 0;
                free(line);
                line = (char*)malloc(1);
                charsRead = read(fd,line,1);
                if(charsRead == 0)
                    break;
                line = (char*)realloc(line,(now + 1)*2);
                while(line[now] != EOF && line[now] != '\n'){
                    now++;
                    charsRead = read(fd,line + now,1);
                    char charnow = line[now];
                    line = (char*)realloc((void*)line,now + 2);
                }
            line[now] = 0;
            continue;
        }
        token = token + 7;
        char* tokentemp = strstr(token,"www.");
        if(tokentemp != NULL){
            token = tokentemp;
            token = token + 4;
        }
        tokentemp = strtok(token,"/\n ");
        if(tokentemp != NULL){
            token = tokentemp;
            token = strtok(token,"/\n ");
        }
        string url = std::string(token);
        insert_str url_str = {url,1};
        auto itr = num_of_apears.begin();
        if((itr = num_of_apears.find(url)) != num_of_apears.end())
            itr->second.app++;
        else
            num_of_apears.insert(std::pair<string,insert_str>(url,url_str));
        now = 0;
        free(line);
        line = (char*)malloc(1);
        charsRead = read(fd,line,1);
        if(charsRead == 0)
            break;
        line = (char*)realloc(line,(now + 1)*2);
        while(line[now] != EOF && line[now] != '\n'){
            now++;
            charsRead = read(fd,line + now,1);
            char charnow = line[now];
            line = (char*)realloc((void*)line,now + 2);
        }
        line[now] = 0;
    }
        close(fd);
        char file_name[4096] = "../";
        strcat(file_name,name_of_file);
        strcat(file_name,".out");
        int newFd = open(file_name,O_WRONLY|O_CREAT);
        for (auto itr = num_of_apears.begin(); itr != num_of_apears.end(); ++itr) {
            string str_url = itr->first + " " + std::to_string(itr->second.app) + "\n";
            write(newFd,str_url.c_str(),str_url.length());
        }
        close(newFd);
}
