#include "apue.h"
#include <fcntl.h>

int main(int argc, const char* args[]){
    int i, fd;

    struct stat statbuf;
    struct timespec times[2];

    for(i = 1; i < argc; i++){
        if(stat(args[i], &statbuf) < 0){
            err_ret("%s: stat error", args[i]);
            continue;
        }
        if((fd = open(args[i], O_RDWR|O_TRUNC)) < 0){
            err_ret("%s: open error", args[i]);
            continue;
        }
        times[0] = statbuf.st_atim;
        times[1] = statbuf.st_mtim;
        if(futimens(fd, times) < 0){
            err_ret("%s: update time error", args[i]);
        }
        close(fd);
    }

    exit(0);
}