/**
 * jacobi-2d-imper.c: This file is part of the PolyBench/C 3.2 test suite.
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
/* Default data type is double, default size is 20x1000. */
#include "jacobi-2d-imper.h"
/* Array initialization. */

#include "header.h"

double **A;
double **B;

//static void init_array(int n,double A[__SIZE__ + 0][__SIZE__ + 0],double B[__SIZE__ + 0][__SIZE__ + 0])
static void init_array(int n)
{
  int i;
  int j;
  for (i = 0; i < n; i++) 
    for (j = 0; j < n; j++) {
      A[i][j] = (((double )i) * (j + 2) + 2) / n;
      B[i][j] = (((double )i) * (j + 3) + 3) / n;
    }
}
/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */

static void print_array(int n,double A[__SIZE__ + 0][__SIZE__ + 0])
{
  int i;
  int j;
  for (i = 0; i < n; i++) 
    for (j = 0; j < n; j++) {
      fprintf(stderr,"%0.2lf ",A[i][j]);
      if ((i * n + j) % 20 == 0) 
        fprintf(stderr,"\n");
    }
  fprintf(stderr,"\n");
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */

//static void kernel_jacobi_2d_imper(int tsteps,int n,double A[__SIZE__ + 0][__SIZE__ + 0],double B[__SIZE__ + 0][__SIZE__ + 0])
static void kernel_jacobi_2d_imper(int tsteps,int n)
{
  int t = 0;
#pragma omp parallel 
{
    int i;
    int j;
    
#pragma omp for  private(i,j)
    for (i = 1; i < n - 1; i++) {
      while(t < tsteps){
        for (j = 1; j < n - 1; j++) 
          B[i][j] = 0.2 * (A[i][j] + A[i][j - 1] + A[i][1 + j] + A[1 + i][j] + A[i - 1][j]);
#pragma omp barrier 
        for (j = 1; j < n - 1; j++) 
          A[i][j] = B[i][j];
        if (i == 1) 
          t++;
#pragma omp barrier 
      }
    }
  }
//#pragma endscop
}


int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int n = __SIZE__;
  int tsteps = __TSTEPS__;
/* Variable declaration/allocation. */
	// CHANGE: Moved as a global declaration
  //double (*A)[__SIZE__ + 0][__SIZE__ + 0];
  //A1 = ((double (*)[__SIZE__ + 0][__SIZE__ + 0])(polybench_alloc_data(((__SIZE__ + 0) * (__SIZE__ + 0)),(sizeof(double )))));

	A = calloc(__SIZE__, sizeof(double *));
	B = calloc(__SIZE__, sizeof(double *));
	int i;
	for (i = 0; i < __SIZE__; i++) {
		A[i] = calloc(__SIZE__, sizeof(double));
		B[i] = calloc(__SIZE__, sizeof(double));
	}


	// CHANGE: Moved as a global declaration
  //double (*B)[__SIZE__ + 0][__SIZE__ + 0];
  //B1 = ((double (*)[__SIZE__ + 0][__SIZE__ + 0])(polybench_alloc_data(((__SIZE__ + 0) * (__SIZE__ + 0)),(sizeof(double )))));
  ;
/* Initialize array(s). */
	// CHANGE: Moved as a global declaration
  //init_array(n, *A, *B);
  init_array(n);
/* Start timer. */
  polybench_timer_start();;
/* Run kernel. */
	// CHANGE: We are not passing A and B because it is global.
  //kernel_jacobi_2d_imper(tsteps,n, *A, *B);
  kernel_jacobi_2d_imper(tsteps,n);
/* Stop and print timer. */
  polybench_timer_stop();;
	fprintf(stdout , "Run time = ");
  polybench_timer_print();;
/* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
//  polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(A)));
//print_array(n, POLYBENCH_ARRAY(A));
/* Be clean. */
  free(((void *)A));
  ;
  free(((void *)B));
  ;
  return 0;
}
