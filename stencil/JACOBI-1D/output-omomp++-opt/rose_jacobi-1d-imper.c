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
//#include "uwomp-barrier.h" 
//TODO
#include "uwomp-barrier-optimized.h"


void ***arg_list_parallel_for_body1_0;
// TODO: Following declarations are unused.
//void ***arg_list_parallel_for_body1__while__0_0;
//void ***arg_list_OmpRegBody1_0;

void parallel_for_body1__while__0_cps_cont5(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0(int *p_i,int **p_t,int **p_tsteps);
void parallel_for_body1(int i,int *t,int *tsteps);
void OmpRegBody1(int *n,int *t,int *tsteps);
double *A;
double *B;
/* Array initialization. */
//static void init_array (int n, DATA_TYPE POLYBENCH_1D(A,N,n), DATA_TYPE POLYBENCH_1D(B,N,n))

static void init_array(int n)
{
  int i;
  for (i = 0; i < n; i++) {
    A[i] = (((double )i) + 2) / n;
    B[i] = (((double )i) + 3) / n;
  }
}
/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */

//static void print_array(int n,double A[10000 + 0])
static void print_array(int n)
{
  int i;
  for (i = 0; i < n; i++) {
    fprintf(stderr,"%0.2lf ",A[i]);
    if (i % 20 == 0) 
      fprintf(stderr,"\n");
  }
  fprintf(stderr,"\n");
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */
//static void kernel_jacobi_1d_imper(int tsteps, int n, DATA_TYPE POLYBENCH_1D(A,N,n), DATA_TYPE POLYBENCH_1D(B,N,n)) {

static void kernel_jacobi_1d_imper(int tsteps,int n)
{
  int t = 0;
#pragma omp parallel 
{
    //struct __cont_env *init_contn_env = malloc(sizeof(struct __cont_env ));
    //init_contn_env -> cont_fn = uwomp_first_fun;
#pragma omp single 
		{
			// TODO: For omptimized code for static scheduling pass the second  and
			// third argument.
			uwomp_worklist_init((omp_get_num_threads()), n - 1 - 1, 1, 32764);
			//uwomp_worklist_init((omp_get_num_threads()),  32764);
			// TODO: Moved it here instead of declaring it before pfloop to
			// avoid one barrier.
			arg_list_parallel_for_body1_0 = calloc( n - 1 - 1,sizeof(void **));
			// TODO: Following allocations removed because it is unused.
			//arg_list_OmpRegBody1_0 = calloc( n - 1 - 1,sizeof(void **));
			//arg_list_parallel_for_body1__while__0_0 = calloc( n - 1 - 1,sizeof(void **));
		}
    void **__parreg_arglist;
    __parreg_arglist = ((void **)(malloc(6 * sizeof(void *))));
    __parreg_arglist[1] = &n;
    __parreg_arglist[2] = &t;
    __parreg_arglist[3] = &tsteps;
    OmpRegBody1_cps(__parreg_arglist,NULL,0,NULL);
		// TODO: This must be moved to the end of task. Take care that it must
		// be freed only by workers not by all tasks.
    //uwomp_free_worklist_free();
  }
}

int main(int argc,char **argv)
{
/* Retrieve problem size. */
//int n = N;
//int tsteps = TSTEPS;
  int n = __SIZE__;
  int tsteps = __TSTEPS__;
/* Variable declaration/allocation. */
//POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
//POLYBENCH_1D_ARRAY_DECL(B, DATA_TYPE, N, n);
  A = (calloc(__SIZE__,sizeof(double )));
  B = (calloc(__SIZE__,sizeof(double )));
/* Initialize array(s). */
//init_array (n, POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(B));
  init_array(n);
/* Start timer. */
//polybench_start_instruments;
  polybench_timer_start();
  ;
/* Run kernel. */
//kernel_jacobi_1d_imper (tsteps, n, POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(B));
  kernel_jacobi_1d_imper(tsteps,n);
/* Stop and print timer. */
  polybench_timer_stop();
  ;
  fprintf(stdout,"Run time = ");
  polybench_timer_print();
  ;
//polybench_stop_instruments;
//polybench_print_instruments;
/* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
//print_array(n);
//print_array(n, POLYBENCH_ARRAY(A));
//polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(A)));
/* Be clean. */
  free(((void *)A));
  ;
  free(((void *)B));
  ;
  return 0;
}

void OmpRegBody1(int *n,int *t,int *tsteps)
{
}

void parallel_for_body1(int i,int *t,int *tsteps)
{
}

void parallel_for_body1__while__0(int *p_i,int **p_t,int **p_tsteps)
{
}

void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
	// TODO: The copying of values to the arglist is completely removed here.
	// As t and tsteps are already pointers there is no need to pass their address to
	// avoid double dereferencing inside parallel_for_body1__while__0_cps.
	// We are also avoiding dereference to i. However, we are not sure if
	// we can do it always. As part of our while transformation i is converted
	// to a pointer assuming that 'i' is used in the continuation of while loop.
  parallel_for_body1__while__0_cps(arg_list,contn_env,phase_num,old_env);
}

/*
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
*/

void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int *n = (int *)arg_list[1];
	// TODO: Replace dereferences on read only variables.
	int vn = *n;
  int *t = (int *)arg_list[2];
  int *tsteps = (int *)arg_list[3];
  int i;
  int j;
  
#pragma omp for  private(i)
  for (i = 1; i <  vn - 1; i++) {
    if (arg_list_parallel_for_body1_0[i] == NULL) {
      arg_list_parallel_for_body1_0[i] = malloc(6 * sizeof(void *));
    }
    arg_list_parallel_for_body1_0[i][0] = i;
    arg_list_parallel_for_body1_0[i][1] = t;
    arg_list_parallel_for_body1_0[i][2] = tsteps;
    struct __cont_env *OmpRegBody1_cps_cps_cont_env_1_1 = malloc(sizeof(struct __cont_env ));
    OmpRegBody1_cps_cps_cont_env_1_1 -> arg_list = arg_list_parallel_for_body1_0[i];
    OmpRegBody1_cps_cps_cont_env_1_1 -> contn_env = contn_env;
		// TODO: Bypassing one function.
		// Reason: Arglist indices are for same variables.
    OmpRegBody1_cps_cps_cont_env_1_1 -> cont_fn = parallel_for_body1__while__0_cps; // parallel_for_body1_cps;
			// TODO: For omptimized code for static scheduling pass the second argument task_id.
    uwomp_add_to_local_pending_worklist(OmpRegBody1_cps_cps_cont_env_1_1, i, 0);
    //uwomp_add_to_local_pending_worklist(OmpRegBody1_cps_cps_cont_env_1_1, 0);
  }
  uwomp_execute_worklist();
}
/*
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

*/

void parallel_for_body1__while__0_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[0];
  int *t = (int *)arg_list[1];
  int *tsteps = (int *)arg_list[2];
  if (!( *t <  *tsteps)) {
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
    return ;
  }
  B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
	/* TODO: Optimization DirectlyUseOldEnv
	 * The specific conditions for this needs to be found out. However
	 * it can be done.
	 */ 
  //struct __cont_env *parallel_for_body1__while__0_cps_cont_env3;
  //if (old_env != NULL) {
  //  parallel_for_body1__while__0_cps_cont_env3 = old_env;
  //  old_env = NULL;
  //}
  // else {
  //  parallel_for_body1__while__0_cps_cont_env3 = malloc(sizeof(struct __cont_env ));
  //}
	/* TODO: Optimization SetOnlyContFun
	 * Conditions:
	 * 1. Values written are only through pointer dereferencing or through
	 *    global variables. In this case no update is required for arglist.
	 *    In this particular function we are already not updating any index
	 *    of arglist.
	 * 2. For all cps functions generated from a single original function
	 *    the cont_env parameter would be always same as old_env->cont_env.
	 *    So if we are reusing old_env, no need to reset that.
	 */
	// TODO: Here also we are avoiding setting i, t and tsteps because we
	// are not updating i. Also t and tsteps are pointers.
  //parallel_for_body1__while__0_cps_cont_env3 -> arg_list = arg_list;
  //parallel_for_body1__while__0_cps_cont_env3 -> contn_env = contn_env;
  //parallel_for_body1__while__0_cps_cont_env3 -> cont_fn = parallel_for_body1__while__0_cps_cont3;
  old_env -> cont_fn = parallel_for_body1__while__0_cps_cont3;
  //uwomp_barrier(parallel_for_body1__while__0_cps_cont_env3,phase_num);
  // TODO: Add the second arguemnt task id
  uwomp_barrier(old_env, i, phase_num);
}

void parallel_for_body1__while__0_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[0];
  int *t = (int *)arg_list[1];
  A[i] = B[i];
  if (i == 1) 
    ( *t)++;
	/* TODO: Optimization DirectlyUseOldEnv
	 * The specific conditions for this needs to be found out. However
	 * it can be done.
	 */ 
  //struct __cont_env *parallel_for_body1__while__0_cps_cont_env4;
  //if (old_env != NULL) {
  //  parallel_for_body1__while__0_cps_cont_env4 = old_env;
  //  old_env = NULL;
  //}
  // else {
  //  parallel_for_body1__while__0_cps_cont_env4 = malloc(sizeof(struct __cont_env ));
  //}
  //parallel_for_body1__while__0_cps_cont_env4 -> arg_list = arg_list;
  //parallel_for_body1__while__0_cps_cont_env4 -> contn_env = contn_env;
  //parallel_for_body1__while__0_cps_cont_env4 -> cont_fn = parallel_for_body1__while__0_cps; // parallel_for_body1__while__0_cps_cont4;
	// TODO: Bypassing one function.
	// Reason: Arglist indices are for same variables.
  old_env -> cont_fn = parallel_for_body1__while__0_cps; // parallel_for_body1__while__0_cps_cont4;
  //uwomp_barrier(parallel_for_body1__while__0_cps_cont_env4,phase_num);
  //TODO: Add the second argument task id
  uwomp_barrier(old_env, i, phase_num);
}

void parallel_for_body1__while__0_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  parallel_for_body1__while__0_cps(arg_list,contn_env,phase_num,old_env);
}

/*
void parallel_for_body1__while__0_cps_cont5(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
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
*/
