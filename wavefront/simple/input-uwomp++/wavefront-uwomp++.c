#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include "header.h"

#define max(x,y) ((x > y) ? x : y)
#define min(x,y) ((x < y) ? x : y)

float **A;

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


void init() {
  A = malloc(sizeof(float *) * M);

	int i, j;
  for (i = 0; i < M; i++) 
    A[i] = malloc (sizeof(float) * N);
  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++) {
      A[i][j] = (float)(random())/RAND_MAX;
		}

	return;
}

void printMatrix(float **B) {
  int i, j;

  for (i = 0; i < M; i++)
    for(j = 0; j < N; j++)
			fprintf(stderr, "%f ", B[i][j]);
	fprintf(stderr, "\n");
	return;
}

//void compute() {
//	int t=1;
//	#pragma omp parallel
//	{
//		int p,i,j;
//		#pragma omp for
//		for(p=1;p<N;p++){
//			while(t <= N+M-3){
//				if(t>=p && t<=M+p-1){
//					i=p; j=t-p+1;
//					A[i][j]=A[i-1][j]+A[i][j-1];
//				}
//				#pragma omp barrier
//				if(p==1){t++}
//				#pragma omp barrier
//			}
//		}
//	}
//}

void recTask(int p, int t) {
	int i, j;
	if (t > N+M-3)
		return;
	if(t>=p && t<=M+p-1){
		i=p; j=t-p+1;
		A[i][j]=A[i-1][j]+A[i][j-1];
	}
	#pragma omp barrier
	// Here is an important point to note. It reduces one barrier compared
	// to the while version since we can pass the value of t as a parameter
	// to recTask itself.
	//if(p==1){t++}
	//#pragma omp barrier
	// FIXME: i and j are read here. They are written in the previous countination.
	// But they are not stored there.
	recTask(p, t + 1);
}

void compute() {
	#pragma omp parallel
	{
		int p;
		#pragma omp for
		for(p=1;p<N;p++){
			recTask(p, 1);
		}
	}
}


int main() {
  struct timeval tv1, tv2;

	init();

  gettimeofday(&tv1, NULL);
	compute();
  gettimeofday(&tv2, NULL);
  fprintf(stdout, "Run time = ");
  getruntime(tv1, tv2);

	printMatrix(A);
}
