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

//void ompRegBody(int *iters) {
//		int i;
//#pragma omp for private (i)
//    for (i = 1; i <= N; i++) {
//      while ( delta > epsilon ) {
//        newA[i] = (oldA[i-1]+oldA[i+1])/2.0 ;
//        diff[i] = fabs(newA[i]-oldA[i]);
//#pragma omp barrier
//        if (i == 1) {
//          sum(diff, &delta); (*iters)++;
//          temp = newA; newA = oldA; oldA = temp;
//        }
//#pragma omp barrier
//      }
//    }
//}

int main()
{
  int j;
  struct timeval tv1, tv2;
  srand48(101); // initialize the prng with a fixed seed.

  oldA = (double *)malloc(sizeof(double) * (N + 2));
  newA = (double *)malloc(sizeof(double) * (N + 2));
  diff = (double *)malloc(sizeof(double) * (N + 2));

  //fprintf(stderr, "VAL = %f\n", VAL);
  oldA[0] = EPSILON/(N+1);
  for (j = 1; j <= N; j++) {
    oldA[j] = drand48();
    //fprintf (stderr, "a[j] %.2lf", oldA[j]);
  }
  oldA[N+1] = EPSILON/(N+1);

  epsilon = EPSILON;
  delta = epsilon+1;
  int iters = 0;
  gettimeofday(&tv1, NULL);
//#pragma omp parallel
//  {
//		ompRegBody(&iters);
//	}

#pragma omp parallel
  {
		int i;
#pragma omp for private (i)
    for (i = 1; i <= N; i++) {
      while ( delta > epsilon ) {
        newA[i] = (oldA[i-1]+oldA[i+1])/2.0 ;
        diff[i] = fabs(newA[i]-oldA[i]);
#pragma omp barrier
        if (i == 1) {
          sum(diff, &delta); iters++;
          temp = newA; newA = oldA; oldA = temp;
        }
#pragma omp barrier
      }
    }
	}

  fprintf(stderr, "#iterations = %d\n", iters);
  gettimeofday(&tv2, NULL);
  fprintf(stderr, "Run time = ");
  getruntime(tv1, tv2);
  return 0;
}
