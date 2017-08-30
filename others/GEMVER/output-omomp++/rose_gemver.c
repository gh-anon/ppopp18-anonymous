/**
 * gemver.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "polybench.h"
/* Include benchmark-specific header. */
/* Default data type is double, default size is 4000. */
#include "gemver.h"
#include "header.h"
#include "uwomp-barrier.h" 
void OmpRegBody1_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1(int i,int j,int *n);
void OmpRegBody1(int *n);
double **A;
double *u1;
double *v1;
double *u2;
double *v2;
double *w;
double *x;
double *y;
double *z;
double alpha;
double beta;


void ***arg_list_parallel_for_body1_0;

//void ***arg_list_OmpRegBody1_0;

/* Array initialization. */
//static void init_array (int n, DATA_TYPE *alpha, DATA_TYPE *beta, DATA_TYPE POLYBENCH_2D(A,N,N,n,n), DATA_TYPE POLYBENCH_1D(u1,N,n), DATA_TYPE POLYBENCH_1D(v1,N,n), DATA_TYPE POLYBENCH_1D(u2,N,n), DATA_TYPE POLYBENCH_1D(v2,N,n), DATA_TYPE POLYBENCH_1D(w,N,n), DATA_TYPE POLYBENCH_1D(x,N,n), DATA_TYPE POLYBENCH_1D(y,N,n), DATA_TYPE POLYBENCH_1D(z,N,n))

static void init_array(int n)
{
  int i;
  int j;
//*alpha = 43532;
//*beta = 12313;
  alpha = 43532;
  beta = 12313;
  for (i = 0; i < n; i++) {
    u1[i] = i;
    u2[i] = ((i + 1) / n) / 2.0;
    v1[i] = ((i + 1) / n) / 4.0;
    v2[i] = ((i + 1) / n) / 6.0;
    y[i] = ((i + 1) / n) / 8.0;
    z[i] = ((i + 1) / n) / 9.0;
    x[i] = 0.0;
    w[i] = 0.0;
    for (j = 0; j < n; j++) 
      A[i][j] = ((double )i) * j / n;
  }
}
/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
//static void print_array(int n, DATA_TYPE POLYBENCH_1D(w,N,n))

static void print_array(int n)
{
  int i;
  for (i = 0; i < n; i++) {
    fprintf(stderr,"%0.2lf ",w[i]);
    if (i % 20 == 0) 
      fprintf(stderr,"\n");
  }
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */
//static void kernel_gemver(int n, DATA_TYPE alpha, DATA_TYPE beta, DATA_TYPE POLYBENCH_2D(A,N,N,n,n), DATA_TYPE POLYBENCH_1D(u1,N,n), DATA_TYPE POLYBENCH_1D(v1,N,n), DATA_TYPE POLYBENCH_1D(u2,N,n), DATA_TYPE POLYBENCH_1D(v2,N,n), DATA_TYPE POLYBENCH_1D(w,N,n), DATA_TYPE POLYBENCH_1D(x,N,n), DATA_TYPE POLYBENCH_1D(y,N,n), DATA_TYPE POLYBENCH_1D(z,N,n))

static void kernel_gemver(int n)
{
#pragma omp parallel 
{
    //struct __cont_env *init_contn_env = malloc(sizeof(struct __cont_env ));
    //init_contn_env -> cont_fn = uwomp_first_fun;
#pragma omp single 
{
      uwomp_worklist_init((omp_get_num_threads()),32766);
			arg_list_parallel_for_body1_0 = calloc( n - 0,sizeof(void **));
			//arg_list_OmpRegBody1_0 = calloc( n - 0,sizeof(void **));

    }
    void **__parreg_arglist;
    __parreg_arglist = ((void **)(malloc(1 * sizeof(void *))));
    __parreg_arglist[0] = &n;
    OmpRegBody1_cps(__parreg_arglist,NULL,0,NULL);
    //uwomp_free_worklist_free();
  }
}

int main(int argc,char **argv)
{
/* Retrieve problem size. */
//int n = N;
  int n = __N__;
/* Variable declaration/allocation. */
//DATA_TYPE alpha;
//DATA_TYPE beta;
//POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);
//POLYBENCH_1D_ARRAY_DECL(u1, DATA_TYPE, N, n);
//POLYBENCH_1D_ARRAY_DECL(v1, DATA_TYPE, N, n);
//POLYBENCH_1D_ARRAY_DECL(u2, DATA_TYPE, N, n);
//POLYBENCH_1D_ARRAY_DECL(v2, DATA_TYPE, N, n);
//POLYBENCH_1D_ARRAY_DECL(w, DATA_TYPE, N, n);
//POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
//POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);
//POLYBENCH_1D_ARRAY_DECL(z, DATA_TYPE, N, n);
  A = (calloc(__N__,sizeof(double *)));
  int i;
  for (i = 0; i < __N__; i++) {
    A[i] = (calloc(__N__,sizeof(double )));
  }
  u1 = (calloc(__N__,sizeof(double )));
  v1 = (calloc(__N__,sizeof(double )));
  u2 = (calloc(__N__,sizeof(double )));
  v2 = (calloc(__N__,sizeof(double )));
  w = (calloc(__N__,sizeof(double )));
  x = (calloc(__N__,sizeof(double )));
  y = (calloc(__N__,sizeof(double )));
  z = (calloc(__N__,sizeof(double )));
/* Initialize array(s). */
//init_array (n, &alpha, &beta, POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(u1), POLYBENCH_ARRAY(v1), POLYBENCH_ARRAY(u2), POLYBENCH_ARRAY(v2), POLYBENCH_ARRAY(w), POLYBENCH_ARRAY(x), POLYBENCH_ARRAY(y), POLYBENCH_ARRAY(z)); 
  init_array(n);
/* Start timer. */
  polybench_start_instruments;
  ;
/* Run kernel. */
//kernel_gemver (n, alpha, beta, POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(u1), POLYBENCH_ARRAY(v1), POLYBENCH_ARRAY(u2), POLYBENCH_ARRAY(v2), POLYBENCH_ARRAY(w), POLYBENCH_ARRAY(x), POLYBENCH_ARRAY(y), POLYBENCH_ARRAY(z));
  kernel_gemver(n);
/* Stop and print timer. */
  ;
/* Stop and print timer. */
  polybench_stop_instruments;


  fprintf(stdout,"Run time = ");
  polybench_print_instruments;
  ;
/* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
//polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(w)));
//print_array(n, POLYBENCH_ARRAY(w));
  print_array(n);
/* Be clean. */
  free(((void *)A));
  ;
  free(((void *)u1));
  ;
  free(((void *)v1));
  ;
  free(((void *)u2));
  ;
  free(((void *)v2));
  ;
  free(((void *)w));
  ;
  free(((void *)x));
  ;
  free(((void *)y));
  ;
  free(((void *)z));
  ;
  return 0;
}

void OmpRegBody1(int *n)
{
}

void parallel_for_body1(int i,int j,int *n)
{
}

void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[0];
  //int j = (int )arg_list[1];
  int *n = (int *)arg_list[1];
	int vn = *n;
	int j;
  for (j = 0; j <  vn; j++) 
    A[i][j] = A[i][j] + u1[i] * v1[j] + u2[i] * v2[j];
  //struct __cont_env *parallel_for_body1_cps_cont_env1;
  //if (old_env != NULL) {
  //  parallel_for_body1_cps_cont_env1 = old_env;
  //  old_env = NULL;
  //}
  // else {
  //  parallel_for_body1_cps_cont_env1 = malloc(sizeof(struct __cont_env ));
  //}
  //parallel_for_body1_cps_cont_env1 -> arg_list = arg_list;
  //arg_list[1] = j;
  //parallel_for_body1_cps_cont_env1 -> contn_env = contn_env;
  //parallel_for_body1_cps_cont_env1 -> cont_fn = parallel_for_body1_cps_cont1;
  old_env-> cont_fn = parallel_for_body1_cps_cont1;
  uwomp_barrier(old_env,phase_num);
}

void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[0];
  //int j = (int )arg_list[1];
  int *n = (int *)arg_list[1];
	int vn = *n;
	int j;
  for (j = 0; j <  vn; j++) 
    x[i] = x[i] + beta * A[j][i] * y[j];
  x[i] = x[i] + z[i];
  //struct __cont_env *parallel_for_body1_cps_cont_env2;
  //if (old_env != NULL) {
  //  parallel_for_body1_cps_cont_env2 = old_env;
  //  old_env = NULL;
  //}
  // else {
  //  parallel_for_body1_cps_cont_env2 = malloc(sizeof(struct __cont_env ));
  //}
  //parallel_for_body1_cps_cont_env2 -> arg_list = arg_list;
  //arg_list[1] = j;
  //parallel_for_body1_cps_cont_env2 -> contn_env = contn_env;
  //parallel_for_body1_cps_cont_env2 -> cont_fn = parallel_for_body1_cps_cont2;
  old_env-> cont_fn = parallel_for_body1_cps_cont2;
  uwomp_barrier(old_env,phase_num);
}

void parallel_for_body1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[0];
  //int j = (int )arg_list[1];
  int *n = (int *)arg_list[1];
	int vn = *n;
	int j;
  for (j = 0; j <  vn; j++) 
    w[i] = w[i] + alpha * A[i][j] * x[j];
  if (old_env != NULL) {
    free(old_env);
  }
  if (contn_env != NULL) {
    uwomp_call_contn_fun(contn_env);
  }
  if (contn_env == NULL) {
    uwomp_execute_ready_worklist((omp_get_thread_num()));
  }
}

void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int *n = (int *)arg_list[0];
	int vn = *n;
  int i;
  //int j;
 
#pragma omp for  private(i)
  for (i = 0; i <  vn; i++) {
    if (arg_list_parallel_for_body1_0[i] == NULL) {
      arg_list_parallel_for_body1_0[i] = malloc(2 * sizeof(void *));
    }
    arg_list_parallel_for_body1_0[i][0] = i;
    //arg_list_parallel_for_body1_0[i][1] = j;
    arg_list_parallel_for_body1_0[i][1] = n;
    struct __cont_env *OmpRegBody1_cps_cps_cont_env_1_1 = malloc(sizeof(struct __cont_env ));
    OmpRegBody1_cps_cps_cont_env_1_1 -> arg_list = arg_list_parallel_for_body1_0[i];
    OmpRegBody1_cps_cps_cont_env_1_1 -> contn_env = contn_env;
    OmpRegBody1_cps_cps_cont_env_1_1 -> cont_fn = parallel_for_body1_cps;
    uwomp_add_to_local_pending_worklist(OmpRegBody1_cps_cps_cont_env_1_1,0);
  }
  uwomp_execute_worklist();
}

void OmpRegBody1_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  if (old_env != NULL) {
    free(old_env);
  }
  if (contn_env != NULL) {
    uwomp_call_contn_fun(contn_env);
  }
  if (contn_env == NULL) {
    uwomp_execute_ready_worklist((omp_get_thread_num()));
  }
}
