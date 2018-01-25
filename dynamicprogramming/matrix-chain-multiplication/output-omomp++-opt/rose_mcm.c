#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "uwomp-barrier-optimized.h" 
void matrix_paranth_for_len_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void matrix_paranth_for_len_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void matrix_paranth_for_len_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1(int i);
void OmpRegBody1();
int N;
int *P;
int **M;

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
  fprintf(stderr,"%f\n",end_time - start_time);
}
//void matrix_paranth(int i)
//{
//	int l,j,k,v;
//	for(l=2; l<=N; l++)
//	{
//		if(i<=N-l+1)
//		{
//			 j = i+l-1;
//			 printf("%d: [%d,%d]\n",omp_get_thread_num(),i,j);
//			 M[i][j] = INT_MAX;
//			 for(k=i; k<j; k++)
//			 {
//					v = M[i][k] +M[k+1][j] + P[i-1]*P[k]*P[j];
//					if(v<M[i][j])
//						M[i][j] = v;
//			 }
//		}
//#pragma omp barrier
//	}
//}

void matrix_paranth_for_len(int i,int l)
{
}

int print_val()
{
  int i;
  int j;
  for (i = 0; i <= N; i++) {
    for (j = 0; j <= N; j++) {
      printf("%d\t",M[i][j]);
    }
    printf("\n");
  }
}

int main(int argc,char **argv)
{
  struct timeval tv1;
  struct timeval tv2;
// Time
  double time;
  FILE *fp;
// Read input file (sequences in two lines)
  if (argc > 1) {
    fp = fopen(argv[1],"r");
    if (fp == ((void *)0)) {
      printf("[ERROR] : Failed to read file named '%s'.\n",argv[1]);
      exit(1);
    }
  }
   else {
    printf("USAGE : %s [filename].\n",argv[0]);
    exit(1);
  }
// Read number of matrices
  fscanf(fp,"%d",&N);
  int i;
  P = (calloc((N + 1),sizeof(int )));
  for (i = 0; i <= N; i++) {
    fscanf(fp,"%d",&P[i]);
  }
  M = ((int **)(calloc((N + 1),sizeof(int *))));
  for (i = 0; i <= N; i++) 
    M[i] = ((int *)(calloc((N + 1),sizeof(int ))));
  for (i = 0; i <= N; i++) 
    M[i][i] = 0;
  gettimeofday(&tv1,0);
#pragma omp parallel 
{
//    struct __cont_env *init_contn_env = malloc(sizeof(struct __cont_env ));
//    init_contn_env -> cont_fn = uwomp_first_fun;
#pragma omp single 
	{
		arg_list_parallel_for_body1_0 = calloc(N,sizeof(void **));
		uwomp_worklist_init((omp_get_num_threads()),N, 1, 0);
	}
    void **__parreg_arglist;
    __parreg_arglist = ((void **)(malloc(0 * sizeof(void *))));
    OmpRegBody1_cps(__parreg_arglist,NULL,0,NULL);
//    uwomp_free_worklist_free();
  }
  gettimeofday(&tv2,0);
  fprintf(stderr,"Run time = ");
  getruntime(tv1,tv2);
//print_val();
  fprintf(stdout,"Optimum number of multiplications = %d\n",M[1][N]);
  return 0;
}

void OmpRegBody1()
{
}

void parallel_for_body1(int i)
{
}

void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[0];
  arg_list[1] = 2;
  matrix_paranth_for_len_cps(arg_list,contn_env,phase_num,old_env);
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
//    uwomp_execute_ready_worklist((omp_get_thread_num()));
  }
}

void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i;

#pragma omp for 
  for (i = 1; i <= N; i++) {
    if (arg_list_parallel_for_body1_0[i] == NULL) {
      arg_list_parallel_for_body1_0[i] = malloc(2 * sizeof(void *));
    }
    arg_list_parallel_for_body1_0[i][0] = i;
    struct __cont_env *OmpRegBody1_cps_cps_cont_env_1_1 = malloc(sizeof(struct __cont_env ));
    OmpRegBody1_cps_cps_cont_env_1_1 -> arg_list = arg_list_parallel_for_body1_0[i];
    OmpRegBody1_cps_cps_cont_env_1_1 -> contn_env = contn_env;
    OmpRegBody1_cps_cps_cont_env_1_1 -> cont_fn = parallel_for_body1_cps;
    uwomp_add_to_local_pending_worklist(OmpRegBody1_cps_cps_cont_env_1_1,i,0);
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
//    uwomp_execute_ready_worklist((omp_get_thread_num()));
  }
}

void matrix_paranth_for_len_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[0];
  int l = (int )arg_list[1];
  if (l > N) {
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
  int j;
  int k;
  int v;
  if (i <= N - l + 1) {
    j = i + l - 1;
    M[i][j] = 2147483647;
    for (k = i; k < j; k++) {
      v = M[i][k] + M[k + 1][j] + P[i - 1] * P[k] * P[j];
      if (v < M[i][j]) 
        M[i][j] = v;
    }
  }
  //struct __cont_env *matrix_paranth_for_len_cps_cont_env3;
  //if (old_env != NULL) {
  //  matrix_paranth_for_len_cps_cont_env3 = old_env;
  //  old_env = NULL;
  //  matrix_paranth_for_len_cps_cont_env3 -> cont_fn = matrix_paranth_for_len_cps_cont3;
  //}
  // else {
  //  matrix_paranth_for_len_cps_cont_env3 = malloc(sizeof(struct __cont_env ));
  //  matrix_paranth_for_len_cps_cont_env3 -> arg_list = arg_list;
  //  matrix_paranth_for_len_cps_cont_env3 -> contn_env = contn_env;
  //  matrix_paranth_for_len_cps_cont_env3 -> cont_fn = matrix_paranth_for_len_cps_cont3;
  //}
  arg_list[1] = l + 1;
	old_env->arg_list = arg_list;
  old_env-> cont_fn = matrix_paranth_for_len_cps;
  uwomp_barrier(old_env,i,phase_num);
}

void matrix_paranth_for_len_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int l = (int )arg_list[1];
  arg_list[1] = l + 1;
  matrix_paranth_for_len_cps(arg_list,contn_env,phase_num,old_env);
}

void matrix_paranth_for_len_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  if (old_env != NULL) {
    free(old_env);
  }
  if (contn_env != NULL) {
    uwomp_call_contn_fun(contn_env);
  }
  if (contn_env == NULL) {
//    uwomp_execute_ready_worklist((omp_get_thread_num()));
  }
}
