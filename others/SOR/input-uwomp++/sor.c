#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "header.h"
#include <math.h>

double **A;

void getruntime(struct timeval tv1, struct timeval tv2) {
  time_t sec1, sec2;
  suseconds_t usec1, usec2;

  sec1 = tv1.tv_sec;
  sec2 = tv2.tv_sec;
  usec1 = tv1.tv_usec;
  usec2 = tv2.tv_usec;

  double start_time = (double)sec1 + (usec1/1000000.0);
  double end_time = (double)sec2 + (usec2/1000000.0);
  fprintf(stdout, "%f\n", end_time - start_time);
}
printArray(double **A, int m, int n) {
  int i, j;
  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++)
      fprintf(stderr, "%f ", A[i][j]);
    fprintf(stderr, "\n");
  }
}
int main()
{
  int ii, jj, kk;
  int m, n, niters;
  struct timeval tv1, tv2;
  
  m = M; n = N; niters = NITERS;
  srand48(101); // initialize the prng with a fixed seed.
  
  A = (double **)malloc(sizeof(double*) * m);
  for(ii = 0; ii < n; ii++) {
    A[ii] = (double *) malloc (sizeof(double) * n);
  }

  for (jj = 0; jj < m; jj++) {
    for (kk = 0; kk < m; kk++) {
      A[jj][kk] = drand48();
      //fprintf (stderr, "a[jj] %.2lf", oldA[jj]);
    }
  }

  gettimeofday(&tv1, NULL);
  for(kk = 0; kk < niters; kk++) {
#pragma omp parallel shared(A) 
    {
			int i, j;
#pragma omp for private(i, j)
      for(i = 1; i < m-1; i++) {
        for(j = 1; j < n-1; j++) {
          if((i + j) % 2 == 0)
            A[i][j] = 0.25*(A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1]);
        }
#pragma omp barrier
        for(j = 1; j < n-1; j++) {
          if((i + j) % 2 == 1)
            A[i][j] = 0.25*(A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1]);
        }
      }
    }
  }
  gettimeofday(&tv2, NULL);
  fprintf(stdout, "Run time = ");
  getruntime(tv1, tv2);
  return 0;
}
