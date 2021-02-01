#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void){
    char msgBuf[4];
    int p[2];
    int p2[2];
    if(pipe(p)<0)
        exit(1);
    if(pipe(p2)<0)
        exit(1);

    int pid = fork();
    if (pid <0)
        exit(1);
    else if (pid == 0){
        close(p[1]);
        int n;
        while((n = read(p[0], msgBuf, sizeof(msgBuf)))>0){}
        printf("%d: received %s\n", getpid(), msgBuf);
        write(p2[1], "pong", 4);
        close(p2[1]);
    }else{
        write(p[1], "ping", 4);
        close(p[1]);
        close(p2[1]);
        int n;
        while((n = read(p2[0], msgBuf, sizeof(msgBuf)))>0){}
        printf("%d: received %s\n", getpid(), msgBuf);
    }
    exit(0);
}