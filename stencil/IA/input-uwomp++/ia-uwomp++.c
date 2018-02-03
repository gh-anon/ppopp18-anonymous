#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "header.h"
#include <math.h>

double *newA, *oldA, *diff, *temp;

double epsilon;
double delta;
int iters = 0;

void getruntime(struct timeval tv1, struct timeval tv2) {
  time_t sec1, sec2;
  suseconds_t usec1, usec2;

  sec1 = tv1.tv_sec;
  sec2 = tv2.tv_sec;
  usec1 = tv1.tv_usec;
  usec2 = tv2.tv_usec;

  double start_time = (double)sec1 + (usec1/1000000.0);
  double end_time = (double)sec2 + (usec2/1000000.0);
  fprintf(stderr, "%f\n", end_time - start_time);
}


double sum(double *d, double *delta) {
  double res = 0.0;
  int i;
  for (i = 1; i <= N; i++)
    res += d[i];

  *delta = res;
}


void iterAvg (int i, double *oldA, double *newA) {
	if (delta <= epsilon)
		return;
	newA[i] = (oldA[i-1]+oldA[i+1])/2.0 ;
	diff[i] = fabs(newA[i]-oldA[i]);
#pragma omp barrier
	if (i == 1) {
		sum(diff, &delta); iters++;
	}
#pragma omp barrier
	iterAvg(i, newA, oldA);
}

int main()
{
  int j;
  struct timeval tv1, tv2;
  srand48(101); // initialize the prng with a fixed seed.

  oldA = (double *)malloc(sizeof(double) * (N + 2));
  newA = (double *)malloc(sizeof(double) * (N + 2));
  diff = (double *)malloc(sizeof(double) * (N + 2));

  oldA[0] = EPSILON/(N+1);
  for (j = 1; j <= N; j++) {
    oldA[j] = drand48();
  }
  oldA[N+1] = EPSILON/(N+1);

  epsilon = EPSILON;
  delta = epsilon+1;
  gettimeofday(&tv1, NULL);

#pragma omp parallel
  {
		int i;
#pragma omp for private (i)
    for (i = 1; i <= N; i++) {
			iterAvg(i, oldA, newA);
    }
	}

  fprintf(stderr, "#iterations = %d\n", iters);
  gettimeofday(&tv2, NULL);
  fprintf(stderr, "Run time = ");
  getruntime(tv1, tv2);
  return 0;
}
