/*
 * Gregory Coolen - Décembre 2020
 * Examen d'OS Janvier 2020 (Q2 - C)
 * main.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define R 0
#define W 1

int main(){
    int fd[2];
    pipe(fd);

    char term[16];
    pid_t pid;
    pid = fork();
    if(pid==0){
        close(fd[R]);
        while(1){
            scanf("%s", term);
            write(fd[W], term, strlen(term) + 1);
            if(strcmp(term, "x")==0) {
                exit(0);
            }
        }
    }
    else{
        close(fd[W]);
        int counter = 0;
        while (1){
            read(fd[R], term, 16);
            if(strcmp(term, "x")==0) {
                exit(0);
            }
            int i = atoi(term);
            counter += i;
            printf("%d\n", counter);
        }
    }
}
