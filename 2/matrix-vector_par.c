#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define N_THREADS 12
#define SIZE 10000

long int M[SIZE][SIZE];
long int v1[SIZE], v2[SIZE];

int chunk_size = 1 + SIZE / N_THREADS;

void *mult_parte(void *id_p) {
  int id = (int)id_p;

  int start = id * chunk_size;
  int end = start + chunk_size;
  if (end > SIZE) end = SIZE;

  int i, j;
  for (i=start; i<end; i++) {
    v2[i] = 0;
    for (j=0; j<SIZE; j++) {
      v2[i] += M[i][j] * v1[j];
    }
  }
}


int main()
{
  struct timeval start, stop;

  int i,j;
  for (i=0; i<SIZE; i++) {
    v1[i] = i;
    for (j=0; j<SIZE; j++)
      M[i][j] = i+j;
  }


  gettimeofday(&start, NULL);

  pthread_t *threads;
  threads = malloc(N_THREADS * sizeof(pthread_t));

  for (i=0; i<N_THREADS; i++) {
    pthread_create(&threads[i], NULL, mult_parte, (void *)(i));
  }

  for (i=0; i<N_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  
  gettimeofday(&stop, NULL);

  free(threads);

  double temp = \
    (((double)(stop.tv_sec)*1000.0 + (double)(stop.tv_usec/1000.0)) - \
    ((double)(start.tv_sec)*1000.0 + (double)(start.tv_usec/1000.0)));

  fprintf(stdout, "Time elapsed = %g ms\n", temp);

  for (i=0; i<SIZE; i++)
    fprintf(stdout, "v[%d]=%ld\n", i, v2[i]);

	return 0;
}

