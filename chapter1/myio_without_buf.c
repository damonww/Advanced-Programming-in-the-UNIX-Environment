#include "apue.h"

int main(void){
    char c;
    
    while((c = getc(stdin)) != EOF){
        if(putc(c, stdout) == EOF)
            err_sys("putc error");
    }

    if(c != EOF){
        err_sys("getc error");
    }

    exit(0);
}
