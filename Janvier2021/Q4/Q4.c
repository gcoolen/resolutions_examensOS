// Author : Alexis Dumelié
// 000478309


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

// Reads file and gives contents to child for priting
void doParent(int fd, const char* file){
	char c; 
	FILE* f = fopen(file, "r");
	if (f == NULL){perror("Error opening file !");exit(EXIT_FAILURE);}

	while ((c= getc(f)) != EOF){	// Give one char at a time to child
		write(fd, &c, sizeof(char));
	}
	write(fd, &c, sizeof(char));	// Write EOF to stop child
	fclose(f);

}

// Child prints what parent gives him
void doChild(int fd){
	char c;
	do{
		read(fd, &c, sizeof(char));
		if ( c != EOF ){
			printf("%s", &c);
		}
	}while (c != EOF); 

}

int main(int argc, const char* argv[]){

	if (argc != 2){perror("Invalid number of arguments");exit(EXIT_FAILURE);}

	int fd[2];	

	if (pipe(fd)){
		perror("Error creating pipe");exit(EXIT_FAILURE);
	}

	if (fork()){ 
		close(fd[WRITE]);
		doChild(fd[READ]);
		close(fd[READ]);

 
	}else{
		close(fd[READ]);	
		doParent(fd[WRITE], argv[1]);
		close(fd[WRITE]);
	}

	exit(EXIT_SUCCESS);
}
