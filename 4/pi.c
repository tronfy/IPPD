/* File:     pi.c
 * Purpose:  Estimate pi using the formula
 *
 *              pi = 4*[1 - 1/3 + 1/5 - 1/7 + 1/9 - . . . ]
 *
 * Compile:  gcc -g -Wall -o pi.x pi.c -lm
 * Run:      pi.x <thread_count> <n>
 *           thread_count is the number of threads (this sequential
 *              version only uses 1 thread)
 *           n is the number of terms of the series to use
 *
 * Output:   The estimate of pi and the value of pi computed by the
 *           arctan function in the math library
 *
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void Usage(char *prog_name);

int main(int argc, char *argv[]) {
  long long n, i;
  struct timeval start, stop;
  double factor = 1.0;
  double sum = 0.0;
  int thread_count = 1;

  if (argc != 3)
    Usage(argv[0]);
  thread_count = strtol(argv[1], NULL, 10);
  n = strtoll(argv[2], NULL, 10);
  if (thread_count < 1 || n < 1)
    Usage(argv[0]);

  gettimeofday(&start, NULL);

  for (i = 0; i < n; i++, factor = -factor) {
    sum += factor / (2 * i + 1);
  }

  sum = 4.0 * sum;

  gettimeofday(&stop, NULL);

  double t =
      (((double)stop.tv_sec) * 1000.0 + ((double)(stop.tv_usec) / 1000.0)) -
      (((double)start.tv_sec) * 1000.0 + ((double)(start.tv_usec) / 1000.0));

  fprintf(stdout, "Time elapsed: %g ms\n", t);

  printf("With n = %lld terms and %d threads,\n", n, thread_count);
  printf("   Our estimate of pi = %.14f\n", sum);
  printf("                   pi = %.14f\n", 4.0 * atan(1.0));

  return 0;
} /* main */

/*------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   Print a message explaining how to run the program
 * In arg:    prog_name
 */
void Usage(char *prog_name) {
  fprintf(stderr, "usage: %s <thread_count> <n>\n", prog_name); /* Change */
  fprintf(stderr,
          "   thread_count is the number of threads >= 1\n"); /* Change */
  fprintf(stderr, "   n is the number of terms and should be >= 1\n");
  exit(0);
} /* Usage */
