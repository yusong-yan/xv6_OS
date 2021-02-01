#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stdbool.h>

int main(void){
    int number[34];
    int p[2];
    int index=0;
    for(int i = 2 ; i<= 35; i++){
        number[index++]=i;
    }
    int currentPrime = 2;
    while(index>0){
        pipe(p);
        int pid = fork();
        if (pid == 0){
            close(p[1]);
            index = 0;
            int curNumber = 0;
            while(read(p[0], &curNumber , sizeof(curNumber))!=0){
                number[index++]=curNumber;
            }
            close(p[0]);
            currentPrime = number[0];
            if (currentPrime == 31){
                printf("prime %d\n", currentPrime);
                exit(0);
            }
        }else{
            close(p[0]);
            printf("prime %d\n", currentPrime);
            for(int i = 0; i<=index; i++){
                if(number[i]%currentPrime!=0){
                    write(p[1], &number[i], sizeof(number[i]));
                }
            }
            close(p[1]);
            wait((int *)0);
            exit(0);
        }
    }
    //printf("Stop\n");
    exit(0);
}

