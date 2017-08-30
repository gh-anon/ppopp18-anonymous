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
#include "uwomp-barrier-no-reuseopt.h" 
void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num);
void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num);
void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num);
void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num);
void parallel_for_body1(int i,int j,int *nx,int *ny);
void OmpRegBody1(int *nx,int *ny);
double **ex;
double **ey;
double **hz;
double *_fict_;
/* Array initialization. */
//static void init_array (int tmax, int nx, int ny, DATA_TYPE POLYBENCH_2D(ex,NX,NY,nx,ny), DATA_TYPE POLYBENCH_2D(ey,NX,NY,nx,ny), DATA_TYPE POLYBENCH_2D(hz,NX,NY,nx,ny), DATA_TYPE POLYBENCH_1D(_fict_,TMAX,tmax)) {

static void init_array(int tmax,int nx,int ny)
{
  int i;
  int j;
  for (i = 0; i < tmax; i++) 
    _fict_[i] = ((double )i);
  for (i = 0; i < nx; i++) 
    for (j = 0; j < ny; j++) {
      ex[i][j] = ((double )i) * (j + 1) / nx;
      ey[i][j] = ((double )i) * (j + 2) / ny;
      hz[i][j] = ((double )i) * (j + 3) / nx;
    }
}
/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
//static void print_array(int nx, int ny, DATA_TYPE POLYBENCH_2D(ex,NX,NY,nx,ny), DATA_TYPE POLYBENCH_2D(ey,NX,NY,nx,ny), DATA_TYPE POLYBENCH_2D(hz,NX,NY,nx,ny))

static void print_array(int nx,int ny)
{
  int i;
  int j;
  for (i = 0; i < nx; i++) 
    for (j = 0; j < ny; j++) {
      fprintf(stderr,"%0.2lf ",ex[i][j]);
      fprintf(stderr,"%0.2lf ",ey[i][j]);
      fprintf(stderr,"%0.2lf ",hz[i][j]);
      if ((i * nx + j) % 20 == 0) 
        fprintf(stderr,"\n");
    }
  fprintf(stderr,"\n");
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */
//static void kernel_fdtd_2d(int tmax, int nx, int ny, DATA_TYPE POLYBENCH_2D(ex,NX,NY,nx,ny), DATA_TYPE POLYBENCH_2D(ey,NX,NY,nx,ny), DATA_TYPE POLYBENCH_2D(hz,NX,NY,nx,ny), DATA_TYPE POLYBENCH_1D(_fict_,TMAX,tmax))

static void kernel_fdtd_2d(int tmax,int nx,int ny)
{
  int t;
  int ii;
  int jj;
//#pragma scop
  for (t = 0; t < tmax; t++) {
    for (jj = 0; jj < ny; jj++) 
      ey[0][jj] = _fict_[t];
    for (ii = 1; ii < nx; ii++) 
      for (jj = 0; jj < ny; jj++) 
        ey[ii][jj] = ey[ii][jj] - 0.5 * (hz[ii][jj] - hz[ii - 1][jj]);
#pragma omp parallel 
{
      struct __cont_env *init_contn_env = malloc(sizeof(struct __cont_env ));
      init_contn_env -> cont_fn = uwomp_first_fun;
#pragma omp single 
{
        uwomp_worklist_init((omp_get_num_threads()),32765);
      }
      void **__parreg_arglist;
      __parreg_arglist = ((void **)(malloc(4 * sizeof(void *))));
      __parreg_arglist[2] = &nx;
      __parreg_arglist[3] = &ny;
      OmpRegBody1_cps(__parreg_arglist,NULL,0);
      //uwomp_free_worklist_free();
    }
  }
//#pragma endscop
}

int main(int argc,char **argv)
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
  ex = (calloc(__NX__,sizeof(double *)));
  ey = (calloc(__NX__,sizeof(double *)));
  hz = (calloc(__NX__,sizeof(double *)));
  int i;
  for (i = 0; i < __NX__; i++) {
    ex[i] = (calloc(__NY__,sizeof(double )));
    ey[i] = (calloc(__NY__,sizeof(double )));
    hz[i] = (calloc(__NY__,sizeof(double )));
  }
  _fict_ = (calloc(__TMAX__,sizeof(double *)));
/* Initialize array(s). */
//init_array (tmax, nx, ny, POLYBENCH_ARRAY(ex), POLYBENCH_ARRAY(ey), POLYBENCH_ARRAY(hz), POLYBENCH_ARRAY(_fict_));
  init_array(tmax,nx,ny);
/* Start timer. */
  polybench_start_instruments;
  ;
/* Run kernel. */
//kernel_fdtd_2d (tmax, nx, ny, POLYBENCH_ARRAY(ex), POLYBENCH_ARRAY(ey), POLYBENCH_ARRAY(hz), POLYBENCH_ARRAY(_fict_));
  kernel_fdtd_2d(tmax,nx,ny);
/* Stop and print timer. */
  polybench_stop_instruments;
	fprintf(stdout, "Run time = ");
  polybench_print_instruments;
/* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
//  polybench_prevent_dce(print_array(nx, ny, POLYBENCH_ARRAY(ex),
//				    POLYBENCH_ARRAY(ey),
//				    POLYBENCH_ARRAY(hz)));
//print_array(nx, ny, POLYBENCH_ARRAY(ex), POLYBENCH_ARRAY(ey), POLYBENCH_ARRAY(hz));
  //print_array(nx,ny);
/* Be clean. */
  free(((void *)ex));
  ;
  free(((void *)ey));
  ;
  free(((void *)hz));
  ;
  free(((void *)_fict_));
  ;
  return 0;
}
void ***arg_list_OmpRegBody1_0;

void OmpRegBody1(int *nx,int *ny)
{
}
void ***arg_list_parallel_for_body1_0;

void parallel_for_body1(int i,int j,int *nx,int *ny)
{
}

void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num)
{
  int i = (int )arg_list[0];
  int j = (int )arg_list[1];
  int *nx = (int *)arg_list[2];
  int *ny = (int *)arg_list[3];
  for (j = 1; j <  *ny; j++) 
    ex[i][j] = ex[i][j] - 0.5 * (hz[i][j] - hz[i][j - 1]);
  struct __cont_env *parallel_for_body1_cps_cont_env1;
//  if (old_env != NULL) {
//    parallel_for_body1_cps_cont_env1 = old_env;
//    old_env = NULL;
//  }
//   else {
    parallel_for_body1_cps_cont_env1 = malloc(sizeof(struct __cont_env ));
//  }
  parallel_for_body1_cps_cont_env1 -> arg_list = arg_list;
  arg_list[1] = j;
  parallel_for_body1_cps_cont_env1 -> contn_env = contn_env;
  parallel_for_body1_cps_cont_env1 -> cont_fn = parallel_for_body1_cps_cont1;
  uwomp_barrier(parallel_for_body1_cps_cont_env1,phase_num);
}

void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num)
{
  int i = (int )arg_list[0];
  int j = (int )arg_list[1];
  int *nx = (int *)arg_list[2];
  int *ny = (int *)arg_list[3];
  for (j = 0; j <  *ny - 1; j++) 
// in the original code the second loop has one bound less.
    if (i !=  *nx - 1) 
      hz[i][j] = hz[i][j] - 0.7 * (ex[i][j + 1] - ex[i][j] + ey[i + 1][j] - ey[i][j]);
//  if (old_env != NULL) {
//    free(old_env);
//  }
  if (contn_env != NULL) {
    uwomp_call_contn_fun(contn_env);
  }
  if (contn_env == NULL) {
    uwomp_execute_ready_worklist((omp_get_thread_num()));
  }
}

void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num)
{
  int *nx = (int *)arg_list[2];
  int *ny = (int *)arg_list[3];
  int i;
  int j;
#pragma omp single 
{
    arg_list_parallel_for_body1_0 = calloc( *nx - 0,sizeof(void **));
    arg_list_OmpRegBody1_0 = calloc( *nx - 0,sizeof(void **));
  }
  
#pragma omp for  private(i,j)
  for (i = 0; i <  *nx; i++) {
    if (arg_list_parallel_for_body1_0[i] == NULL) {
      arg_list_parallel_for_body1_0[i] = malloc(4 * sizeof(void *));
    }
    arg_list_parallel_for_body1_0[i][0] = i;
    arg_list_parallel_for_body1_0[i][1] = j;
    arg_list_parallel_for_body1_0[i][2] = nx;
    arg_list_parallel_for_body1_0[i][3] = ny;
    struct __cont_env *OmpRegBody1_cps_cps_cont_env_1_1 = malloc(sizeof(struct __cont_env ));
    OmpRegBody1_cps_cps_cont_env_1_1 -> arg_list = arg_list_parallel_for_body1_0[i];
    OmpRegBody1_cps_cps_cont_env_1_1 -> contn_env = contn_env;
    OmpRegBody1_cps_cps_cont_env_1_1 -> cont_fn = parallel_for_body1_cps;
    uwomp_add_to_local_pending_worklist(OmpRegBody1_cps_cps_cont_env_1_1,0);
  }
  uwomp_execute_worklist();
}

void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num)
{
//  if (old_env != NULL) {
//    free(old_env);
//  }
  if (contn_env != NULL) {
    uwomp_call_contn_fun(contn_env);
  }
  if (contn_env == NULL) {
    uwomp_execute_ready_worklist((omp_get_thread_num()));
  }
}
