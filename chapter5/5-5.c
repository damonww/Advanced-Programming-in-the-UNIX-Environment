#include "apue.h"

int main(void){

    char buf[MAXLINE];

    while(fgets(buf, MAXLINE, stdin) != NULL){
        if(EOF == fputs(buf, stdout)){
            err_sys("output error");
        }
    }

    if(ferror(stdin)){
        err_sys("input error");
    }

    exit(0);
}