#include "apue.h"
#include <sys/wait.h>

int main(void){
    pid_t pid;

    if((pid = fork()) < 0){
        err_sys("fork error\n");
    }else if(pid == 0){
        if((pid = fork()) < 0){
            err_sys("fork error\n");
        }else if(pid > 0){
            exit(0);
        }

        sleep(2);
        printf("second child process, the pid of its parent is %ld\n", (long) getppid());
        exit(0);
    }

    if(waitpid(pid, NULL, 0) != pid){
        err_sys("waitpid error\n");
    }
    printf("child, pid = %ld\n", (long) pid);

    exit(0);
}