/* 02.01.21
 * Examen blanc janvier 2021
 * Info-f-201
 * Author: Attilio Discepoli 
 */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main (){
	int res = 0;
	int fd[2];
	pipe(fd); // Crée le pipe de communication
	if (fork() == 0){
		close(fd[READ]);
		char buffer[64];
		do{
			scanf("%s", buffer);
			write(fd[WRITE], buffer, strlen(buffer)+1);
		}while(strcmp(buffer, "x") != 0);
		close(fd[WRITE]);
	}else{
		close(fd[WRITE]);
		char value[64];
		do{			
			read(fd[READ], value, 64);
			res += atoi(value);
			printf(" %d\n", res);
		}while(strcmp(value, "x") != 0);
		close(fd[READ]);
	}
} 
