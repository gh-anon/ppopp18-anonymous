/**
 * jacobi-1d-imper.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
//#include <polybench.h>
#include "polybench.h"

/* Include benchmark-specific header. */
/* Default data type is double, default size is 100x10000. */
#include "jacobi-1d-imper.h"


#include "header.h"
double *A;
double *B;
/* Array initialization. */
//static void init_array (int n, DATA_TYPE POLYBENCH_1D(A,N,n), DATA_TYPE POLYBENCH_1D(B,N,n))
static void init_array (int n)
{
  int i;

  for (i = 0; i < n; i++)
      {
	A[i] = ((DATA_TYPE) i+ 2) / n;
	B[i] = ((DATA_TYPE) i+ 3) / n;
      }
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array(int n,
		 DATA_TYPE POLYBENCH_1D(A,N,n))

{
  int i;

  for (i = 0; i < n; i++)
    {
      fprintf(stderr, DATA_PRINTF_MODIFIER, A[i]);
      if (i % 20 == 0) fprintf(stderr, "\n");
    }
  fprintf(stderr, "\n");
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
//static void kernel_jacobi_1d_imper(int tsteps, int n, DATA_TYPE POLYBENCH_1D(A,N,n), DATA_TYPE POLYBENCH_1D(B,N,n)) {
static void kernel_jacobi_1d_imper(int tsteps, int n) {
  int t = 0;

#pragma omp parallel
    {
			int  i, j;
#pragma omp for private(i)
      for (i = 1; i < _PB_N - 1; i++){
          while(t < _PB_TSTEPS) {
            B[i] = 0.33333 * (A[i-1] + A[i] + A[i + 1]);
#pragma omp barrier
            A[i] = B[i];
          if (i == 1) t++;
#pragma omp barrier
          }
      }
    }
}


int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  //int n = N;
  //int tsteps = TSTEPS;
  int n = __SIZE__;
  int tsteps = __TSTEPS__;
  /* Variable declaration/allocation. */
  //POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
  //POLYBENCH_1D_ARRAY_DECL(B, DATA_TYPE, N, n);

	A = calloc(__SIZE__, sizeof(double));
	B = calloc(__SIZE__, sizeof(double));

  /* Initialize array(s). */
  //init_array (n, POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(B));
  init_array (n);

  /* Start timer. */
  //polybench_start_instruments;
  polybench_timer_start();;

  /* Run kernel. */
  //kernel_jacobi_1d_imper (tsteps, n, POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(B));
  kernel_jacobi_1d_imper (tsteps, n);

  /* Stop and print timer. */
  polybench_timer_stop();;
	fprintf(stdout , "Run time = ");
  polybench_timer_print();;
  //polybench_stop_instruments;
  //polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  //print_array(n, POLYBENCH_ARRAY(A));
  //polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(A)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(A);
  POLYBENCH_FREE_ARRAY(B);

  return 0;
}
