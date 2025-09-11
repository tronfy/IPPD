#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 15000

// single thread: 1500ms
// t | static | static,1 | dynamic | guided
// 2 | 1170   | 750      | 754     | 740
// 4 | 950    | 630      | 590     | 600

double f(int i) {
  int j, start = i * (i + 1) / 2, finish = start + i;
  double return_val = 0.0;

  for (j = start; j <= finish; j++)
    return_val += sin(j);

  return return_val;
}

int main(int argc, char *argv[]) {
  unsigned long i;
  struct timeval start, stop;
  double sum = 0.0;

  int thread_count = strtol(argv[1], NULL, 10);

  gettimeofday(&start, NULL);

#pragma omp parallel for schedule(runtime) reduction(+ : sum) num_threads(thread_count)
  for (i = 0; i < N; i++)
    sum += f(i);

  gettimeofday(&stop, NULL);

  double tempo =
      (((double)(stop.tv_sec) * 1000.0 + (double)(stop.tv_usec / 1000.0)) -
       ((double)(start.tv_sec) * 1000.0 + (double)(start.tv_usec / 1000.0)));

  fprintf(stdout, "Soma = %g\n", sum);
  fprintf(stdout, "Tempo total gasto = %g ms\n", tempo);

  return 0;
}
