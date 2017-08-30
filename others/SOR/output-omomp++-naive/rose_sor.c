#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "header.h"
#include <math.h>
#include "uwomp-barrier-no-reuseopt.h" 
void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num);
void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num);
void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num);
void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num);
void parallel_for_body1(int i,int j,int *n);
void OmpRegBody1(int *m,int *n);
double **A;

void getruntime(struct timeval tv1,struct timeval tv2)
{
  time_t sec1;
  time_t sec2;
  suseconds_t usec1;
  suseconds_t usec2;
  sec1 = tv1 . tv_sec;
  sec2 = tv2 . tv_sec;
  usec1 = tv1 . tv_usec;
  usec2 = tv2 . tv_usec;
  double start_time = ((double )sec1) + usec1 / 1000000.0;
  double end_time = ((double )sec2) + usec2 / 1000000.0;
  fprintf(stdout,"%f\n",end_time - start_time);
}

int printArray(double **A,int m,int n)
{
  int i;
  int j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) 
      fprintf(stderr,"%f ",A[i][j]);
    fprintf(stderr,"\n");
  }
}

int main()
{
  int ii;
  int jj;
  int kk;
  int m;
  int n;
  int niters;
  struct timeval tv1;
  struct timeval tv2;
  m = M;
  n = N;
  niters = NITERS;
// initialize the prng with a fixed seed.
  srand48(101);
  A = ((double **)(malloc(sizeof(double *) * m)));
  for (ii = 0; ii < n; ii++) {
    A[ii] = ((double *)(malloc(sizeof(double ) * n)));
  }
  for (jj = 0; jj < m; jj++) {
    for (kk = 0; kk < m; kk++) {
      A[jj][kk] = drand48();
//fprintf (stderr, "a[jj] %.2lf", oldA[jj]);
    }
  }
  gettimeofday(&tv1,((void *)0));
  for (kk = 0; kk < niters; kk++) {
#pragma omp parallel  shared(A)
{
      struct __cont_env *init_contn_env = malloc(sizeof(struct __cont_env ));
      init_contn_env -> cont_fn = uwomp_first_fun;
#pragma omp single 
{
        uwomp_worklist_init((omp_get_num_threads()),32764);
      }
      void **__parreg_arglist;
      __parreg_arglist = ((void **)(malloc(4 * sizeof(void *))));
      __parreg_arglist[2] = &m;
      __parreg_arglist[3] = &n;
      OmpRegBody1_cps(__parreg_arglist,NULL,0);
//      uwomp_free_worklist_free();
    }
  }
  gettimeofday(&tv2,((void *)0));
  fprintf(stdout,"Run time = ");
  getruntime(tv1,tv2);
	//printArray(A, m, n);
  return 0;
}
void ***arg_list_OmpRegBody1_0;

void OmpRegBody1(int *m,int *n)
{
}
void ***arg_list_parallel_for_body1_0;

void parallel_for_body1(int i,int j,int *n)
{
}

void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num)
{
  int i = (int )arg_list[0];
  int j = (int )arg_list[1];
  int *n = (int *)arg_list[2];
  for (j = 1; j <  *n - 1; j++) {
    if ((i + j) % 2 == 0) 
      A[i][j] = 0.25 * (A[i - 1][j] + A[i + 1][j] + A[i][j - 1] + A[i][j + 1]);
  }
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
  int *n = (int *)arg_list[2];
  for (j = 1; j <  *n - 1; j++) {
    if ((i + j) % 2 == 1) 
      A[i][j] = 0.25 * (A[i - 1][j] + A[i + 1][j] + A[i][j - 1] + A[i][j + 1]);
  }
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
  int *m = (int *)arg_list[2];
  int *n = (int *)arg_list[3];
  int i;
  int j;
#pragma omp single 
  {
    //arg_list_parallel_for_body1_0 = calloc( *m - 1 - 1,sizeof(void **));
    // FIXME: ARGLIST_ADD_IF_CHECK
    // Useful when paralle region is called from an outer serial loop.
    if(arg_list_parallel_for_body1_0 == NULL)
      // FIXME: ARG_LIST_SIZE_WRONG
      arg_list_parallel_for_body1_0 = calloc( *m,sizeof(void **));
    //arg_list_OmpRegBody1_0 = calloc( *m - 1 - 1,sizeof(void **));
    if(arg_list_OmpRegBody1_0 == NULL)
      arg_list_OmpRegBody1_0 = calloc( *m,sizeof(void **));
  }
  
#pragma omp for  private(i,j)
  for (i = 1; i <  *m - 1; i++) {
    if (arg_list_parallel_for_body1_0[i] == NULL) {
      arg_list_parallel_for_body1_0[i] = malloc(4 * sizeof(void *));
    }
    arg_list_parallel_for_body1_0[i][0] = i;
    arg_list_parallel_for_body1_0[i][1] = j;
    arg_list_parallel_for_body1_0[i][2] = n;
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
