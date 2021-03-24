// Author: Alexis Dumelié
// 000478309

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

static volatile int count = 0; 
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct params{
	bool can_print;
	const int* N;
};

void* countToN(void* args){
	struct params* p = (struct params*) args;
	for (int i = 0; i < *p->N; i++){
		pthread_mutex_lock(&mutex);
		count++;
		if (p->can_print){printf("%d\n", count);}
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(int argc, char const* argv[]){

	if (argc != 3){perror("Invalid number of arguments");exit(EXIT_FAILURE);}

	const int X = atoi(argv[1]);	// Assume no errors in parsing argument as int
	const int N = atoi(argv[2]);
	pthread_t threads[X];
	for (int i = 0; i < X; i++){
		struct params* p = (struct params*) malloc(sizeof(struct params));	
		p->N = &N; p->can_print = (i % 2 == 0); // One thread out of two prints
		if (pthread_create(&threads[i], NULL, countToN, p)){
			perror("Error on thread creation");exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < X; i++){
		if (pthread_join(threads[i], NULL)){
			perror("Error joining thread");exit(EXIT_FAILURE);
		}
	}
	printf("Final count = %d\n", count);

	exit(EXIT_SUCCESS);
}
