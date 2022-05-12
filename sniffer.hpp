#pragma once
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

#include <iostream>
#include <queue>
#include <iterator>
#include <map>
using namespace std;

typedef struct {
    int pid;
    bool stoped;
    string fifo;
} workers;

typedef struct {
    string name;
    int app;
} insert_str;

#define PERMS 0666

void end(int signum);
void worker(int fd);