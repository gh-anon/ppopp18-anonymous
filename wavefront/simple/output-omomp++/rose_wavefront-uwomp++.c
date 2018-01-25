#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include "header.h"
#define max(x,y) ((x > y) ? x : y)
#define min(x,y) ((x < y) ? x : y)
#include "uwomp-barrier.h" 
void recTask_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void recTask_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void recTask_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1(int p);
void OmpRegBody1();
float **A;

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
  A = (malloc(sizeof(float *) * 1024));
  int i;
  int j;
  for (i = 0; i < 1024; i++) 
    A[i] = (malloc(sizeof(float ) * 1024));
  for (i = 0; i < 1024; i++) 
    for (j = 0; j < 1024; j++) {
      A[i][j] = ((float )(random())) / 2147483647;
    }
  return ;
}

void printMatrix(float **B)
{
  int i;
  int j;
  for (i = 0; i < 1024; i++) 
    for (j = 0; j < 1024; j++) 
      fprintf(stderr,"%f ",B[i][j]);
  fprintf(stderr,"\n");
  return ;
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
void ***arg_list_recTask_0;

void recTask(int p,int t)
{
}

void compute()
{
#pragma omp parallel 
{
    //struct __cont_env *init_contn_env = malloc(sizeof(struct __cont_env ));
    //init_contn_env -> cont_fn = uwomp_first_fun;
#pragma omp single 
{
      uwomp_worklist_init((omp_get_num_threads()),0);
    }
    void **__parreg_arglist;
    __parreg_arglist = ((void **)(malloc(4 * sizeof(void *))));
    OmpRegBody1_cps(__parreg_arglist,NULL,0,NULL);
    //uwomp_free_worklist_free();
  }
}

int main()
{
  struct timeval tv1;
  struct timeval tv2;
  init();
  gettimeofday(&tv1,((void *)0));
  compute();
  gettimeofday(&tv2,((void *)0));
  fprintf(stdout,"Run time = ");
  getruntime(tv1,tv2);
  printMatrix(A);
}
void ***arg_list_OmpRegBody1_0;

void OmpRegBody1()
{
}
void ***arg_list_parallel_for_body1_0;

void parallel_for_body1(int p)
{
}

void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  arg_list[3] = 1;
  recTask_cps(arg_list,contn_env,phase_num,old_env);
}

void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
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

void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int p;
#pragma omp single 
{
    arg_list_parallel_for_body1_0 = calloc(1024,sizeof(void **));
    arg_list_OmpRegBody1_0 = calloc(1024,sizeof(void **));
    arg_list_recTask_0 = calloc(1024,sizeof(void **));
  }
  
#pragma omp for 
  for (p = 1; p < 1024; p++) {
    if (arg_list_parallel_for_body1_0[p] == NULL) {
      arg_list_parallel_for_body1_0[p] = malloc(4 * sizeof(void *));
    }
//		printf("p = %d\n", p);
    arg_list_parallel_for_body1_0[p][0] = p;
    struct __cont_env *OmpRegBody1_cps_cps_cont_env_1_1 = malloc(sizeof(struct __cont_env ));
    OmpRegBody1_cps_cps_cont_env_1_1 -> arg_list = arg_list_parallel_for_body1_0[p];
    OmpRegBody1_cps_cps_cont_env_1_1 -> contn_env = contn_env;
    OmpRegBody1_cps_cps_cont_env_1_1 -> cont_fn = parallel_for_body1_cps;
    uwomp_add_to_local_pending_worklist(OmpRegBody1_cps_cps_cont_env_1_1,0);
  }
  uwomp_execute_worklist();
}

void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
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

void recTask_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int p = (int )arg_list[0];
  int t = (int )arg_list[3];
  int i;
  int j;
//	printf("p = %d t = %d\n", p, t);
  if (t > 1024 + 1024 - 3) {
    if (old_env != NULL) {
      free(old_env);
    }
    if (contn_env != NULL) {
      uwomp_call_contn_fun(contn_env);
    }
    if (contn_env == NULL) {
      uwomp_execute_ready_worklist((omp_get_thread_num()));
    }
    return ;
  }
  if (t >= p && t <= 1024 + p - 1) {
    i = p;
    j = t - p + 1;
    A[i][j] = A[i - 1][j] + A[i][j - 1];
  }
  struct __cont_env *recTask_cps_cont_env3;
  if (old_env != NULL) {
    recTask_cps_cont_env3 = old_env;
    old_env = NULL;
    recTask_cps_cont_env3 -> cont_fn = recTask_cps_cont3;
  }
   else {
    recTask_cps_cont_env3 = malloc(sizeof(struct __cont_env ));
    recTask_cps_cont_env3 -> arg_list = arg_list;
    recTask_cps_cont_env3 -> contn_env = contn_env;
    recTask_cps_cont_env3 -> cont_fn = recTask_cps_cont3;
  }
  uwomp_barrier(recTask_cps_cont_env3,phase_num);
}

void recTask_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int t = (int )arg_list[3];
  arg_list[3] = t + 1;
  recTask_cps(arg_list,contn_env,phase_num,old_env);
}

void recTask_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
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
