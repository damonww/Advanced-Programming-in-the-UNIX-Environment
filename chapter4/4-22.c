#include "apue.h"
#include <dirent.h>
#include <limits.h>

typedef int Myfunc(const char *, const struct stat *, int);
static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);

static long nreg, nblk, ndir, nchr, nsock, nfifo, nslink, ntot;


int main(int argc, char *argv[]){ // print results
    if(argc != 2){
        err_quit("usage: ftw <starting-pathname>");
    }
    int ret;

    if((ret = myftw(argv[1], myfunc)) != 0){
        err_quit("ftw error");
    }

    ntot = nreg + ndir + nblk + nchr + nsock + nfifo + nslink;

    if(ntot == 0){
        ntot = 1;
    }

    printf("regular files = %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot);
    printf("directories = %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot);
    printf("block special = %7ld, %5.2f %%\n", nblk, nblk*100.0/ntot);
    printf("char special = %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot);
    printf("FIFOs = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
    printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot);
    printf("sockets = %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);
}

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4

static char *fullpath;
static size_t pathlen;

static int myftw(char *pathname, Myfunc *func){ // return whatever func return
    fullpath = path_alloc(&pathlen);
    if(strlen(pathname) >= pathlen){
        pathlen = strlen(pathname) * 2;
        if((fullpath = realloc(fullpath, pathlen)) == NULL){
            err_sys("realloc error");
        }
    }
    strcpy(fullpath, pathname);

    return dopath(func);
}

static int dopath(Myfunc *func){ // recursive the path
    struct stat buf;
    int ret, n;

    if(stat(fullpath, &buf) < 0){
        err_sys("%s: stat error", fullpath);
        return func(fullpath, &buf, FTW_NS);
    }
    if(S_ISDIR(buf.st_mode) == 0){
        return func(fullpath, &buf, FTW_F);
    }
    if((ret = func(fullpath, &buf, FTW_D)) != 0){
        return ret;
    }

    DIR *dp;
    struct dirent *dirp;

    if((dp = opendir(fullpath)) == NULL){
        return func(fullpath, &buf, FTW_DNR);
    }

    n = strlen(fullpath);
    if(n + NAME_MAX + 2 > pathlen){ // 2 = "\0" + "/"
        pathlen *= 2;
        if((fullpath = realloc(fullpath, pathlen)) == NULL){
            err_sys("realloc error");
        }
    }
    
    fullpath[n++] = '/';
    fullpath[n] = 0;

    while((dirp = readdir(dp)) != NULL){
        if(strcmp(dirp->d_name, ".") == 0){
            continue;
        }
        if(strcmp(dirp->d_name, "..") == 0){
            continue;
        }
        strcpy(&fullpath[n], dirp->d_name);
        if((ret = dopath(func)) != 0){
            break;
        }
    }
    fullpath[n-1] = 0;
    if(closedir(dp) < 0){
        err_ret("closedir error");
    }

    return ret;
}

static int myfunc(const char *pathname, const struct stat *statptr, int type){ //add up
    switch(type){
        case FTW_F:
            switch(statptr->st_mode & S_IFMT){
                case S_IFREG: nreg++; break;
                case S_IFBLK: nblk++; break;
                case S_IFCHR: nchr++; break;
                case S_IFIFO: nfifo++; break;
                case S_IFLNK: nslink++; break;
                case S_IFSOCK: nsock++; break;
                case S_IFDIR:
                    err_dump("for S_IFDIR for %s", fullpath);
            }
            break;
        case FTW_D: ndir++; break;
        case FTW_DNR:
            err_ret("can't read directory: %s", fullpath);
            break;
        case FTW_NS:
            err_ret("stat error for %s", fullpath);
            break;
        default:
            err_dump("unknown type %d for pathname %s", type, pathname);
    }

    return 0;
}