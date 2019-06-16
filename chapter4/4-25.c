#include "apue.h"
#include <sys/sysmacros.h>

#ifdef SOLARIS
#include <sys/mkdev.h>
#endif


int main(int argc, const char *argv[]){
    struct stat statbuf;

    for(int i = 1; i < argc; i++){
        if(stat(argv[i], &statbuf) < 0){
            err_ret("%s: stat error");
            continue;
        }
        printf("%s: dev = %d/%d", argv[i], major(statbuf.st_dev), minor(statbuf.st_dev));
        if(S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode)){
            printf(" (%s) rdev = %d/%d", (S_ISCHR(statbuf.st_mode) ? "character" : "block")
            , major(statbuf.st_rdev), minor(statbuf.st_rdev));
        }
        printf("\n");
    }

    exit(0);
}