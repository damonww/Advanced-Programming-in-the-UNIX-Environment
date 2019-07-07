#include<sys/wait.h>
#include<unistd.h>
#include<errno.h>

int system(char *cmdstring){
    pid_t pid;
    int status;

    if(cmdstring == NULL){
        return 1;
    }
    if((pid = fork()) < 0){
        status = -1;
    }else if(pid == 0){
        execl("/bin/sh", "-c", cmdstring, char*(0));
        _exit(127);
    }else{
        while(waitpid(pid, &status, o) < 0){
            if(errno != EINTR){
                status = -1;
                break;
            }
        }
    }

    return(status);
}