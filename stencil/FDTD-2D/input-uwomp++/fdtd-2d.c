/**
 * fdtd-2d.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "header.h"
/* Include polybench common header. */
#include "polybench.h"

/* Include benchmark-specific header. */
/* Default data type is double, default size is 50x1000x1000. */
#include "fdtd-2d.h"

double **ex;
double **ey;
double **hz;
double *_fict_;

/* Array initialization. */
//static void init_array (int tmax, int nx, int ny, DATA_TYPE POLYBENCH_2D(ex,NX,NY,nx,ny), DATA_TYPE POLYBENCH_2D(ey,NX,NY,nx,ny), DATA_TYPE POLYBENCH_2D(hz,NX,NY,nx,ny), DATA_TYPE POLYBENCH_1D(_fict_,TMAX,tmax)) {
static void init_array (int tmax, int nx, int ny) {
  int i, j;

  for (i = 0; i < tmax; i++)
    _fict_[i] = (DATA_TYPE) i;
  for (i = 0; i < nx; i++)
    for (j = 0; j < ny; j++)
      {
	ex[i][j] = ((DATA_TYPE) i*(j+1)) / nx;
	ey[i][j] = ((DATA_TYPE) i*(j+2)) / ny;
	hz[i][j] = ((DATA_TYPE) i*(j+3)) / nx;
      }
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
//static void print_array(int nx, int ny, DATA_TYPE POLYBENCH_2D(ex,NX,NY,nx,ny), DATA_TYPE POLYBENCH_2D(ey,NX,NY,nx,ny), DATA_TYPE POLYBENCH_2D(hz,NX,NY,nx,ny))
static void print_array(int nx, int ny)
{
  int i, j;

  for (i = 0; i < nx; i++)
    for (j = 0; j < ny; j++) {
      fprintf(stderr, DATA_PRINTF_MODIFIER, ex[i][j]);
      fprintf(stderr, DATA_PRINTF_MODIFIER, ey[i][j]);
      fprintf(stderr, DATA_PRINTF_MODIFIER, hz[i][j]);
      if ((i * nx + j) % 20 == 0) fprintf(stderr, "\n");
    }
  fprintf(stderr, "\n");
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
//static void kernel_fdtd_2d(int tmax, int nx, int ny, DATA_TYPE POLYBENCH_2D(ex,NX,NY,nx,ny), DATA_TYPE POLYBENCH_2D(ey,NX,NY,nx,ny), DATA_TYPE POLYBENCH_2D(hz,NX,NY,nx,ny), DATA_TYPE POLYBENCH_1D(_fict_,TMAX,tmax))
static void kernel_fdtd_2d(int tmax, int nx, int ny)
{
  int t, ii, jj;

//#pragma scop
    for(t = 0; t < _PB_TMAX; t++)
    {
      for (jj = 0; jj < _PB_NY; jj++)
        ey[0][jj] = _fict_[t];
      for (ii = 1; ii < _PB_NX; ii++)
        for (jj = 0; jj < _PB_NY; jj++)
          ey[ii][jj] = ey[ii][jj] - 0.5*(hz[ii][jj]-hz[ii-1][jj]);
#pragma omp parallel
  {
		int i, j;
#pragma omp for private(i,j)
      for (i = 0; i < _PB_NX; i++) {
        for (j = 1; j < _PB_NY; j++)
          ex[i][j] = ex[i][j] - 0.5*(hz[i][j]-hz[i][j-1]);
#pragma omp barrier
        for (j = 0; j < _PB_NY - 1; j++)
          if(i != _PB_NX - 1) // in the original code the second loop has one bound less.
            hz[i][j] = hz[i][j] - 0.7*  (ex[i][j+1] - ex[i][j] +
                ey[i+1][j] - ey[i][j]);
      }
    }
  }
//#pragma endscop
}


int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  //int tmax = TMAX;
  //int nx = NX;
  //int ny = NY;
  int tmax = __TMAX__;
  int nx = __NX__;
  int ny = __NY__;


  /* Variable declaration/allocation. */
  //POLYBENCH_2D_ARRAY_DECL(ex,DATA_TYPE,NX,NY,nx,ny);
  //POLYBENCH_2D_ARRAY_DECL(ey,DATA_TYPE,NX,NY,nx,ny);
  //POLYBENCH_2D_ARRAY_DECL(hz,DATA_TYPE,NX,NY,nx,ny);
  //POLYBENCH_1D_ARRAY_DECL(_fict_,DATA_TYPE,TMAX,tmax);
	ex = calloc(__NX__, sizeof(double *));
	ey = calloc(__NX__, sizeof(double *));
	hz = calloc(__NX__, sizeof(double *));
	int i;
	for (i = 0; i < __NX__; i++) {
		ex[i] = calloc(__NY__, sizeof(double));
		ey[i] = calloc(__NY__, sizeof(double));
		hz[i] = calloc(__NY__, sizeof(double));
	}
	_fict_ = calloc(__TMAX__, sizeof(double *));

  /* Initialize array(s). */
  //init_array (tmax, nx, ny, POLYBENCH_ARRAY(ex), POLYBENCH_ARRAY(ey), POLYBENCH_ARRAY(hz), POLYBENCH_ARRAY(_fict_));
  init_array (tmax, nx, ny);

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  //kernel_fdtd_2d (tmax, nx, ny, POLYBENCH_ARRAY(ex), POLYBENCH_ARRAY(ey), POLYBENCH_ARRAY(hz), POLYBENCH_ARRAY(_fict_));
  kernel_fdtd_2d (tmax, nx, ny);


  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
//  polybench_prevent_dce(print_array(nx, ny, POLYBENCH_ARRAY(ex),
//				    POLYBENCH_ARRAY(ey),
//				    POLYBENCH_ARRAY(hz)));

  //print_array(nx, ny, POLYBENCH_ARRAY(ex), POLYBENCH_ARRAY(ey), POLYBENCH_ARRAY(hz));
  print_array(nx, ny);
  /* Be clean. */
  POLYBENCH_FREE_ARRAY(ex);
  POLYBENCH_FREE_ARRAY(ey);
  POLYBENCH_FREE_ARRAY(hz);
  POLYBENCH_FREE_ARRAY(_fict_);

  return 0;
}
