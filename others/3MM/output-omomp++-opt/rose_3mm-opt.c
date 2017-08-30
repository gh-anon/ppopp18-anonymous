#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#include "header.h"
//#include "uwomp-barrier.h" 
#include "uwomp-barrier-optimized.h" 
void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1(int i,int j,int k);
void OmpRegBody1();
float **A;
float **B;
float **C;
float **D;
float **E;
float **F;
float **G;

//void ***arg_list_OmpRegBody1_0;

void ***arg_list_parallel_for_body1_0;

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

void init()
{
  int i;
  int j;
  srandom(1000);
  A = ((float **)(malloc(sizeof(float *) * N)));
  B = ((float **)(malloc(sizeof(float *) * N)));
  C = ((float **)(malloc(sizeof(float *) * N)));
  D = ((float **)(malloc(sizeof(float *) * N)));
  E = ((float **)(malloc(sizeof(float *) * N)));
  F = ((float **)(malloc(sizeof(float *) * N)));
  G = ((float **)(malloc(sizeof(float *) * N)));
  for (i = 0; i < N; i++) {
    A[i] = ((float *)(malloc(sizeof(float ) * N)));
    B[i] = ((float *)(malloc(sizeof(float ) * N)));
    C[i] = ((float *)(malloc(sizeof(float ) * N)));
    D[i] = ((float *)(malloc(sizeof(float ) * N)));
    E[i] = ((float *)(malloc(sizeof(float ) * N)));
    F[i] = ((float *)(malloc(sizeof(float ) * N)));
    G[i] = ((float *)(malloc(sizeof(float ) * N)));
  }
  for (i = 0; i < N; i++) 
    for (j = 0; j < N; j++) {
      A[i][j] = ((float )(random())) / 2147483647;
      B[i][j] = ((float )(random())) / 2147483647;
      C[i][j] = 0.0;
      D[i][j] = ((float )(random())) / 2147483647;
      E[i][j] = ((float )(random())) / 2147483647;
      F[i][j] = 0.0;
      G[i][j] = 0.0;
    }
}

void printMatrix(float **M)
{
  int i;
  int j;
  for (i = 0; i < N; i++) 
    for (j = 0; j < N; j++) 
      fprintf(stderr,"%f ",M[i][j]);
  fprintf(stderr,"\n");
  return ;
}

int main(int argc,char **argv)
{
  struct timeval tv1;
  struct timeval tv2;
  init();
  gettimeofday(&tv1,((void *)0));
#pragma omp parallel  shared(A,B,C,D,E,F,G)
{
    //struct __cont_env *init_contn_env = malloc(sizeof(struct __cont_env ));
    //init_contn_env -> cont_fn = uwomp_first_fun;
#pragma omp single 
{
      //uwomp_worklist_init((omp_get_num_threads()),32767);
      uwomp_worklist_init((omp_get_num_threads()), N, 0, 32767);
    arg_list_parallel_for_body1_0 = calloc(N - 0,sizeof(void **));
    //arg_list_OmpRegBody1_0 = calloc(N - 0,sizeof(void **));
 
    }
    void **__parreg_arglist;
    __parreg_arglist = ((void **)(malloc(3 * sizeof(void *))));
    OmpRegBody1_cps(__parreg_arglist,NULL,0,NULL);
    //uwomp_free_worklist_free();
  }
  gettimeofday(&tv2,((void *)0));
  fprintf(stdout,"Run time = ");
  getruntime(tv1,tv2);
//  fprintf(stderr, "Parallel Outuput:\n");
  //printMatrix(G);
  return 0;
}

void OmpRegBody1()
{
}

void parallel_for_body1(int i,int j,int k)
{
}

void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[0];
  //int j = (int )arg_list[1];
  //int k = (int )arg_list[2];
	int j, k;
  for (j = 0; j < N; j++) {
    for (k = 0; k < N; k++) {
      C[i][j] += A[i][k] * B[k][j];
      F[i][j] += D[i][k] * E[k][j];
    }
  }
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
  //arg_list[2] = k;
  //parallel_for_body1_cps_cont_env1 -> contn_env = contn_env;
  //parallel_for_body1_cps_cont_env1 -> cont_fn = parallel_for_body1_cps_cont1;
  old_env -> cont_fn = parallel_for_body1_cps_cont1;
  //uwomp_barrier(old_env ,phase_num);
  uwomp_barrier(old_env , i, phase_num);
}

void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[0];
  //int j = (int )arg_list[1];
  //int k = (int )arg_list[2];
	int j, k;
  for (j = 0; j < N; j++) {
    for (k = 0; k < N; k++) {
      G[i][j] += C[i][k] * F[k][j];
    }
  }
  if (old_env != NULL) {
    free(old_env);
  }
  if (contn_env != NULL) {
    uwomp_call_contn_fun(contn_env);
  }
  if (contn_env == NULL) {
			// TODO: Add the following check
			if((i + 1) <= max_task_id_array[omp_get_thread_num()])
			{
				int local_index = get_local_index(i + 1);
				// TODO: Here local index should be incremented.
				uwomp_execute_ready_worklist((omp_get_thread_num()), local_index);
			}
  }
}

void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i;
  int j;
  int k;
 
#pragma omp for  private(i,j,k)
  for (i = 0; i < N; i++) {
    if (arg_list_parallel_for_body1_0[i] == NULL) {
      arg_list_parallel_for_body1_0[i] = malloc(1 * sizeof(void *));
    }
    arg_list_parallel_for_body1_0[i][0] = i;
    //arg_list_parallel_for_body1_0[i][1] = j;
    //arg_list_parallel_for_body1_0[i][2] = k;
    struct __cont_env *OmpRegBody1_cps_cps_cont_env_1_1 = malloc(sizeof(struct __cont_env ));
    OmpRegBody1_cps_cps_cont_env_1_1 -> arg_list = arg_list_parallel_for_body1_0[i];
    OmpRegBody1_cps_cps_cont_env_1_1 -> contn_env = contn_env;
    OmpRegBody1_cps_cps_cont_env_1_1 -> cont_fn = parallel_for_body1_cps;
    //uwomp_add_to_local_pending_worklist(OmpRegBody1_cps_cps_cont_env_1_1,0);
    uwomp_add_to_local_pending_worklist(OmpRegBody1_cps_cps_cont_env_1_1, i, 0);
  }
  uwomp_execute_worklist();
}

//void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
//{
//  if (old_env != NULL) {
//    free(old_env);
//  }
//  if (contn_env != NULL) {
//    uwomp_call_contn_fun(contn_env);
//  }
//  if (contn_env == NULL) {
//    uwomp_execute_ready_worklist((omp_get_thread_num()));
//  }
//}
