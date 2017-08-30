#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#include "header.h"

float **A, **B, **C, **D, **E, **F, **G;

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
  int i, j;

  srandom(1000);

  A = (float **)malloc(sizeof(float *) * N);
  B = (float **)malloc(sizeof(float *) * N);
  C = (float **)malloc(sizeof(float *) * N);
  D = (float **)malloc(sizeof(float *) * N);
  E = (float **)malloc(sizeof(float *) * N);
  F = (float **)malloc(sizeof(float *) * N);
  G = (float **)malloc(sizeof(float *) * N);

  for (i = 0; i < N; i++) {
    A[i] = (float *) malloc (sizeof(float) * N);
    B[i] = (float *) malloc (sizeof(float) * N);
    C[i] = (float *) malloc (sizeof(float) * N);
    D[i] = (float *) malloc (sizeof(float) * N);
    E[i] = (float *) malloc (sizeof(float) * N);
    F[i] = (float *) malloc (sizeof(float) * N);
    G[i] = (float *) malloc (sizeof(float) * N);
  }

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      A[i][j] = (float)(random())/RAND_MAX;
      B[i][j] = (float)(random())/RAND_MAX;
      C[i][j] = 0.0;
      D[i][j] = (float)(random())/RAND_MAX;
      E[i][j] = (float)(random())/RAND_MAX;
      F[i][j] = 0.0;
      G[i][j] = 0.0;
    }
}

void printMatrix(float **M) {
  int i, j;

  for (i = 0; i < N; i++)
    for(j = 0; j < N; j++)
      fprintf(stderr, "%f ", M[i][j]);
  fprintf(stderr, "\n");
  return;
}

int main(int argc, char **argv) {
  struct timeval tv1, tv2;

  init();
  gettimeofday(&tv1, NULL);

#pragma omp parallel shared (A, B, C, D, E, F, G) 
  {
		int i, j, k;
#pragma omp for private(i, j, k)
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {           
        for (k = 0; k < N; k++) {
          C[i][j] += A[i][k] * B[k][j];
          F[i][j] += D[i][k] * E[k][j];
        }
      }
#pragma omp barrier
      for (j = 0; j < N; j++) {           
        for (k = 0; k < N; k++) {
          G[i][j] += C[i][k] * F[k][j];         
        }
      }
    }
  }

  gettimeofday(&tv2, NULL);
  fprintf(stdout, "Run time = ");
  getruntime(tv1, tv2);

//  fprintf(stderr, "Parallel Outuput:\n");
//  printMatrix(G);
  return 0;
}
