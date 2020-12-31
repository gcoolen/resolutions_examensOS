//Author: Alexis Dumelie

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>


static int res = 1;		// Global result

struct params {
  int lower, upper;
};

void* fact(void* args) {
  // Do factorial of given internval
  struct params* p = (struct params*) args;
  int* tmp_res = (int*) malloc(sizeof(int));
  *tmp_res = 1;
  for (int i = p->lower; i <= p->upper; i++) {
    *tmp_res *= i;
  }
  // Uncomment line if you want to see the work each thread performs
  //printf("Bounds: %d lower, %d upper, tmpres = %d \n", p->lower, p->upper, *tmp_res); // FOR DEBUG
  free(p);
  return (void*) tmp_res;
}


int main(int argc, char const* argv[]) {
  // Arg 1: n, Arg 2 t: number of threads

  if (argc != 3) {perror("Invalid number of arguments"); exit(EXIT_FAILURE);}
  const int N = atoi(argv[1]); // Assuming no errors as atoi does not handle them
  const int T = atoi(argv[2]);
  if (T > N) {perror("Cannot divide N into more than N tasks !"); exit(EXIT_FAILURE);}

  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  int step = N / T;
  int lower = 1, upper = step;
  pthread_t threads[T];
  for (int i = 0; i < T; i++) {
    struct params* p = (struct params*)malloc(sizeof(struct params));
    if (i == T - 1) {
      // If N%T != 0 will have remaining "part"
      p->lower = lower; p->upper = N;	// Taking extra "part" into task area of final thread
    } else {
      p->lower = lower; p->upper = upper;
    }

    if (pthread_create(&threads[i], NULL, *fact, p)) {
      perror("Error on thread creation !"); exit(EXIT_FAILURE);
    }

    lower = upper + 1;
    upper += step;
  }

  for (int i = 0; i < T; i++) {
    int* tmp_res;
    if (pthread_join(threads[i], (void**) &tmp_res)) {perror("Error in thread join !"); exit(EXIT_FAILURE);}

    pthread_mutex_lock(&mutex);
    res *= *tmp_res;
    pthread_mutex_unlock(&mutex);
    free(tmp_res);		// free tmp_res allocated in thread fact
  }

  printf("Result of %d! is %d\n", N, res);
  pthread_mutex_destroy(&mutex);

  exit(EXIT_SUCCESS);
}
