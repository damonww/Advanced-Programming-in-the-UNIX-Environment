#include "apue.h"

int main(void){
    char c;

    while((c = getc(stdin)) != EOF){
        if(EOF == putc(c, stdout)){
            err_sys("output error");
        }
    }

    if(ferror(stdin)){
        err_sys("input error");
    }

    exit(0);
}