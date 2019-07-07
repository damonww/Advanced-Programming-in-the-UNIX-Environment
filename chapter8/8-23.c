#include "apue.h"
#include <sys/wait.h>

void pr_exit(int status){
    if(WIFEXITED(status)){
        printf("normal termination, exited status = %d\n", WIFEXITED(status));
    }else if(WIFSIGNALED(status)){
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef __WCOREDUMP
        __WCOREDUMP(status) ? " (core file generated)" : "");
#else
        "");
#endif
    }else if(WIFSTOPPED(status)){
        printf("child stopped, signal number = %d\n", WIFSTOPPED(status));
    }    
}


int main(void){
    int status;

    if((status = system("date")) < 0){
        err_sys("system() error");
    }

    pr_exit(status);

    if((status = system("nusuchcommand")) < 0){
        err_sys("system() error");
    }

    pr_exit(status);

    if((status = system("who; exit 44")) < 0){
        err_sys("system() error");
    }

    pr_exit(status);

    exit(0);
}