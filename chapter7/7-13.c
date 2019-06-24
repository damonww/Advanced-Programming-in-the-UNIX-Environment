#include "apue.h"
#include<setjmp.h>
static void f1(int, int, int, int,int);
static void f2(void);

static jmp_buf jmpbuffer;
static int globval;

int main(void){
    int autoval;
    register int regival;
    volatile int volaval;
    static int statval;
    globval = 0, autoval = 1,regival = 2,volaval = 3,statval = 4;

    if(setjmp(jmpbuffer) != 0){
        printf("after longjmp: \n");
        printf("globval = %d, autoval = %d, regival = %d,"
        " volaval = %d, statval = %d\n", globval, autoval, regival, volaval, statval);
        exit(0);
    }

    globval = 90, autoval = 91, regival = 92, volaval = 93, statval = 94;
    f1(globval, autoval, regival, volaval, statval);
    exit(0);
}

static void f1(int i, int j, int k, int l, int m){
    printf("in f1(): \n");
        printf("globval = %d, autoval = %d, regival = %d,"
        " volaval = %d, statval = %d\n", i, j, k, l, m);
    f2();
}

static void f2(){
    longjmp(jmpbuffer, 1);
}