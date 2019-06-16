#include "apue.h"
#include <fcntl.h>

int main(int argc, const char *argv[]){
    if(rmdir(argv[1]) < 0){
        err_ret("%s: rmdir error", argv[1]);
    }

    exit(0);
}