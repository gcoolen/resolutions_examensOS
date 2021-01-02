// Author: Alexis Dumelié

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define BASE 10
#define SIZE 64	// TODO a better way rather than a magic number ?

void doChild(int fd, const char endChar){
	char input[SIZE];

	// Get int from input, hypothesised no format errors
	// Stops when endChar is given
	do{
		printf("Enter number>");
		if (!fgets(input, SIZE, stdin)){
			perror("Error reading input !");exit(EXIT_FAILURE);
		}
		write(fd, input, SIZE);
	}while (*input != endChar);

}

void doParent(int fd, const char endChar){
	char buffer[SIZE];

	int sum = 0;
	while (*buffer != endChar){
		read(fd, buffer, SIZE);	
		sum += strtol(buffer, NULL, BASE);
		printf("Sum is: %d\n", sum);
	}
}


int main(){
	// Note: as we can't know the order in which the process will execute
	// the order of prints will be messed up.
	const char endChar = 'x';

	int fd[2];	 // 0 for reading and 1 for writing
	if (pipe(fd)){
		perror("Error creating pipe");exit(EXIT_FAILURE);
	}
	if (fork()){ // Child (pid == 0)
		close(fd[0]);	// Close reading for child
		doChild(fd[1], endChar);
		close(fd[1]);

 
	}else{	// Parent 
		close(fd[1]);	// Close writing for parent
		doParent(fd[0], endChar);
		close(fd[0]);
	}

	exit(EXIT_SUCCESS);
}
