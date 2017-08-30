#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "header.h"
#include <math.h>
#include "uwomp-barrier.h" 
void parallel_for_body1__while__0_cps_cont6(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0_cps_cont5(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void sum_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0(int *p_i,int **p_iters);
void parallel_for_body1(int i,int *iters);
void OmpRegBody1(int *iters);
double *newA;
double *oldA;
double *diff;
double *temp;
double epsilon;
double delta;

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
void ***arg_list_sum_0;

double sum(double *d,double *delta)
{
}
//void ompRegBody(int *iters) {
//		int i;
//#pragma omp for private (i)
//    for (i = 1; i <= N; i++) {
//      while ( delta > epsilon ) {
//        newA[i] = (oldA[i-1]+oldA[i+1])/2.0 ;
//        diff[i] = fabs(newA[i]-oldA[i]);
//#pragma omp barrier
//        if (i == 1) {
//          sum(diff, &delta); (*iters)++;
//          temp = newA; newA = oldA; oldA = temp;
//        }
//#pragma omp barrier
//      }
//    }
//}

int main()
{
  int j;
  struct timeval tv1;
  struct timeval tv2;
// initialize the prng with a fixed seed.
  srand48(101);
  oldA = ((double *)(malloc(sizeof(double ) * (N + 2))));
  newA = ((double *)(malloc(sizeof(double ) * (N + 2))));
  diff = ((double *)(malloc(sizeof(double ) * (N + 2))));
//fprintf(stderr, "VAL = %f\n", VAL);
  oldA[0] = EPSILON / (N + 1);
  for (j = 1; j <= N; j++) {
    oldA[j] = drand48();
//fprintf (stderr, "a[j] %.2lf", oldA[j]);
  }
  oldA[N + 1] = EPSILON / (N + 1);
  epsilon = EPSILON;
  delta = epsilon + 1;
  int iters = 0;
  gettimeofday(&tv1,((void *)0));
#pragma omp parallel 
{
    //struct __cont_env *init_contn_env = malloc(sizeof(struct __cont_env ));
    //init_contn_env -> cont_fn = uwomp_first_fun;
#pragma omp single 
	{
		uwomp_worklist_init((omp_get_num_threads()),32766);
		arg_list_parallel_for_body1_0 = calloc(N - -1,sizeof(void **));
		//arg_list_OmpRegBody1_0 = calloc(N - -1,sizeof(void **));
		arg_list_sum_0 = calloc(N - -1,sizeof(void **));
		//arg_list_parallel_for_body1__while__0_0 = calloc(N - -1,sizeof(void **));
	}
    void **__parreg_arglist;
    __parreg_arglist = ((void **)(malloc(1 * sizeof(void *))));
    __parreg_arglist[0] = &iters;
    OmpRegBody1_cps(__parreg_arglist,NULL,0,NULL);
    //uwomp_free_worklist_free();
  }
  fprintf(stderr,"#iterations = %d\n",iters);
  gettimeofday(&tv2,((void *)0));
  fprintf(stdout,"Run time = ");
  getruntime(tv1,tv2);
  return 0;
}
//void ***arg_list_OmpRegBody1_0;

void OmpRegBody1(int *iters)
{
}

void parallel_for_body1(int i,int *iters)
{
}
//void ***arg_list_parallel_for_body1__while__0_0;

void parallel_for_body1__while__0(int *p_i,int **p_iters)
{
}

void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  //int i = (int )arg_list[0];
  //int *iters = (int *)arg_list[1];
  //arg_list[3] = &i;
  //arg_list[4] = &iters;
  parallel_for_body1__while__0_cps(arg_list,contn_env,phase_num,old_env);
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
  int *iters = (int *)arg_list[0];
  int i;

  
#pragma omp for  private(i)
  for (i = 1; i <= N; i++) {
    if (arg_list_parallel_for_body1_0[i] == NULL) {
      arg_list_parallel_for_body1_0[i] = malloc(3 * sizeof(void *));
    }
    arg_list_parallel_for_body1_0[i][0] = i;
    arg_list_parallel_for_body1_0[i][1] = iters;
    struct __cont_env *OmpRegBody1_cps_cps_cont_env_1_1 = malloc(sizeof(struct __cont_env ));
    OmpRegBody1_cps_cps_cont_env_1_1 -> arg_list = arg_list_parallel_for_body1_0[i];
    OmpRegBody1_cps_cps_cont_env_1_1 -> contn_env = contn_env;
    OmpRegBody1_cps_cps_cont_env_1_1 -> cont_fn = parallel_for_body1__while__0_cps; //parallel_for_body1_cps;
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

void sum_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  double *d = (double *)arg_list[0];
  double *delta = (double *)arg_list[1];
  double res = 0.0;
  int i;
  for (i = 1; i <= N; i++) 
    res += d[i];
   *delta = res;
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

void parallel_for_body1__while__0_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  //int *p_i = (int *)arg_list[3];
  //int **p_iters = (int **)arg_list[4];
  //int __if_v0;
  int i =  (int *)arg_list[0];
  //int *iters =  (int *)arg_list[1];
  if (!(delta > epsilon)) {
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
  newA[i] = (oldA[i - 1] + oldA[i + 1]) / 2.0;
  diff[i] = fabs(newA[i] - oldA[i]);
  //struct __cont_env *parallel_for_body1__while__0_cps_cont_env3;
  //if (old_env != NULL) {
  //  parallel_for_body1__while__0_cps_cont_env3 = old_env;
  //  old_env = NULL;
  //}
  // else {
  //  parallel_for_body1__while__0_cps_cont_env3 = malloc(sizeof(struct __cont_env ));
  //}
  //parallel_for_body1__while__0_cps_cont_env3 -> arg_list = arg_list;
  //arg_list[0] = __if_v0;
  //arg_list[1] = i;
  //arg_list[2] = iters;
  //parallel_for_body1__while__0_cps_cont_env3 -> contn_env = contn_env;
  //parallel_for_body1__while__0_cps_cont_env3 -> cont_fn = parallel_for_body1__while__0_cps_cont3;
  old_env-> cont_fn = parallel_for_body1__while__0_cps_cont3;
  uwomp_barrier(old_env,phase_num);
}

void parallel_for_body1__while__0_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int __if_v0;
  int i = (int )arg_list[0];
  __if_v0 = i == 1;
  if (__if_v0) {
    struct __cont_env *parallel_for_body1__while__0_cps_cont_env4;
    if (old_env != NULL) {
      parallel_for_body1__while__0_cps_cont_env4 = old_env;
      old_env = NULL;
    }
     else {
      parallel_for_body1__while__0_cps_cont_env4 = malloc(sizeof(struct __cont_env ));
    }
    parallel_for_body1__while__0_cps_cont_env4 -> arg_list = arg_list;
    //arg_list[0] = __if_v0;
    arg_list[2] = __if_v0;
    parallel_for_body1__while__0_cps_cont_env4 -> contn_env = contn_env;
    parallel_for_body1__while__0_cps_cont_env4 -> cont_fn = parallel_for_body1__while__0_cps_cont4;
    if (arg_list_sum_0[i] == NULL) {
      arg_list_sum_0[i] = malloc(2 * sizeof(void *));
    }
    arg_list_sum_0[i][0] = diff;
    arg_list_sum_0[i][1] = &delta;
    sum_cps(arg_list_sum_0[i],parallel_for_body1__while__0_cps_cont_env4,phase_num,old_env);
  }
   else {
    struct __cont_env *parallel_for_body1__while__0_cps_cont_env4;
    if (old_env != NULL) {
      parallel_for_body1__while__0_cps_cont_env4 = old_env;
      old_env = NULL;
    }
     else {
      parallel_for_body1__while__0_cps_cont_env4 = malloc(sizeof(struct __cont_env ));
    }
    parallel_for_body1__while__0_cps_cont_env4 -> arg_list = arg_list;
    //arg_list[0] = __if_v0;
    arg_list[2] = __if_v0;
    parallel_for_body1__while__0_cps_cont_env4 -> contn_env = contn_env;
    parallel_for_body1__while__0_cps_cont_env4 -> cont_fn = parallel_for_body1__while__0_cps_cont4;
    if (old_env != NULL) {
      free(old_env);
    }
    uwomp_call_contn_fun(parallel_for_body1__while__0_cps_cont_env4);
  }
}

void parallel_for_body1__while__0_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int __if_v0 = (int )arg_list[2];
  int *iters = (int *)arg_list[1];
  if (__if_v0) {
    ( *iters)++;
    temp = newA;
    newA = oldA;
    oldA = temp;
  }
  //struct __cont_env *parallel_for_body1__while__0_cps_cont_env5;
  //if (old_env != NULL) {
  //  parallel_for_body1__while__0_cps_cont_env5 = old_env;
  //  old_env = NULL;
  //}
  // else {
  //  parallel_for_body1__while__0_cps_cont_env5 = malloc(sizeof(struct __cont_env ));
  //}
  //parallel_for_body1__while__0_cps_cont_env5 -> arg_list = arg_list;
  ////arg_list[2] = iters;
  //parallel_for_body1__while__0_cps_cont_env5 -> contn_env = contn_env;
  //parallel_for_body1__while__0_cps_cont_env5 -> cont_fn = parallel_for_body1__while__0_cps_cont5;
  //parallel_for_body1__while__0_cps_cont_env5 -> cont_fn = parallel_for_body1__while__0_cps;
  old_env-> cont_fn = parallel_for_body1__while__0_cps;
  uwomp_barrier(old_env,phase_num);
}

void parallel_for_body1__while__0_cps_cont5(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  //int i = (int )arg_list[1];
  //int *iters = (int *)arg_list[2];
  //int *p_i = (int *)arg_list[3];
  //int **p_iters = (int **)arg_list[4];
  // *p_i = i;
  // *p_iters = iters;
  //arg_list[3] = p_i;
  //arg_list[4] = p_iters;
  parallel_for_body1__while__0_cps(arg_list,contn_env,phase_num,old_env);
}

void parallel_for_body1__while__0_cps_cont6(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
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
