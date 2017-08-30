#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "uwomp-barrier.h" 
void knapSack_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void knapSack_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void knapSack_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1(int k);
void OmpRegBody1();
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
#define    MAX(x,y)   ((x)>(y) ? (x) : (y))
/* (previously processed: ignoring self-referential macro declaration) macro name = table */ 
int *table;
// # of objects, capacity 
int N;
int C;
int C_plus;
// weights and profits
int *weights;
int *profits;
int *newProfit;
int *oldProfit;
//void ***arg_list_knapSack_0;

void knapSack(int *oldP,int *newP,int i,int k)
{
}

int main(int argc,char **argv)
{
  FILE *fp;
  int verbose;
  int count;
  struct timeval tv1;
  struct timeval tv2;
// Temp variables
  int i;
  int j;
  int size;
// Time
  double time;
// Read input file (# of objects, capacity, (per line) weight and profit )
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
  if (argc > 2) 
    verbose = atoi(argv[2]);
   else 
    verbose = 0;
  fscanf(fp,"%d %d",&N,&C);
  printf("The number of objects is %d, and the capacity is %d.\n",N,C);
  C_plus = C + 1;
  size = (N * sizeof(int ));
  weights = ((int *)(malloc(size)));
  profits = ((int *)(malloc(size)));
  if (weights == ((void *)0) || profits == ((void *)0)) {
    printf("[ERROR] : Failed to allocate memory for weights/profits.\n");
    exit(1);
  }
  for (i = 0; i < N; i++) {
    count = fscanf(fp,"%d %d",&weights[i],&profits[i]);
    if (count != 2) {
      printf("[ERROR] : Input file is not well formatted.\n");
      exit(1);
    }
  }
  fclose(fp);
// Solve for the optimal profit
  size = ((C + 1) * sizeof(int ));
  newProfit = (malloc(size));
  oldProfit = (malloc(size));
  for (j = 0; j <= C; j++) {
    if (j < weights[0]) 
      oldProfit[j] = 0;
     else 
      oldProfit[j] = profits[0];
  }
  gettimeofday(&tv1,0);
#pragma omp parallel 
{
    //struct __cont_env *init_contn_env = malloc(sizeof(struct __cont_env ));
    //init_contn_env -> cont_fn = uwomp_first_fun;
#pragma omp single 
{
    arg_list_parallel_for_body1_0 = calloc(C_plus - 0,sizeof(void **));
    //arg_list_OmpRegBody1_0 = calloc(C_plus - 0,sizeof(void **));
    //arg_list_knapSack_0 = calloc(C_plus - 0,sizeof(void **));
  
      uwomp_worklist_init((omp_get_num_threads()),32764);
    }
    void **__parreg_arglist;
    __parreg_arglist = ((void **)(malloc(0 * sizeof(void *))));
    OmpRegBody1_cps(__parreg_arglist,NULL,0,NULL);
    //uwomp_free_worklist_free();
  }
  gettimeofday(&tv2,0);
  fprintf(stderr,"Run time = ");
  getruntime(tv1,tv2);
// End of "Solve for the optimal profit"
// Backtracking
//	int c=C;
//	int solution[N];
//	for ( i=N-1 ; i > 0 ; i-- ) {
//		if ( c-weights[i] < 0 ) {
//			//printf("i=%d: 0 \n",i);
//			solution[i] = 0;
//		} else {
//			if ( table(i-1,c) > table(i-1,c-weights[i]) + profits[i] ) {
//
//				//printf("i=%d: 0 \n",i);
//				solution[i] = 0;
//			} else {
//				//printf("i=%d: 1 \n",i);
//				solution[i] = 1;
//				c = c - weights[i];
//			}
//		}
//	} 
//	//wim: first row does not look back
//	if(c<weights[0]){
//		//printf("i=0: 1 \n");
//		solution[0]=0;
//	} else {
//		//printf("i=0: 0 \n");
//		solution[0]=1;
//	}
  if (oldProfit[C] > newProfit[C]) 
    printf("The optimal profit is %d\n",oldProfit[C]);
   else 
    printf("The optimal profit is %d\n",newProfit[C]);
//	if (verbose==1) {
//
//		printf("Solution vector is: ");
//		for (i=0 ; i<N ; i++ ) {
//			printf("%d ", solution[i]);
//		}
//		printf("\n");
//	}
//
//	if (verbose==2) {
//		for (j=1; j<=C; j++){
//			printf ("%d\t", j);
//			for (i=0; i<N; i++)
//				printf ("%d ", table(i, j));
//			printf("\n");
//		}
//	}
  return 0;
}
//void ***arg_list_OmpRegBody1_0;

void OmpRegBody1()
{
}

void parallel_for_body1(int k)
{
}

void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int k = (int )arg_list[0];
  arg_list[0] = 0;
  arg_list[1] = k;
  arg_list[2] = newProfit;
  arg_list[3] = oldProfit;
  knapSack_cps(arg_list,contn_env,phase_num,old_env);
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
  int k;

#pragma omp for 
  for (k = 0; k < C_plus; k++) {
    if (arg_list_parallel_for_body1_0[k] == NULL) {
      arg_list_parallel_for_body1_0[k] = malloc(4 * sizeof(void *));
    }
    arg_list_parallel_for_body1_0[k][0] = k;
    struct __cont_env *OmpRegBody1_cps_cps_cont_env_1_1 = malloc(sizeof(struct __cont_env ));
    OmpRegBody1_cps_cps_cont_env_1_1 -> arg_list = arg_list_parallel_for_body1_0[k];
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

void knapSack_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int *oldP = (int *)arg_list[3];
  int *newP = (int *)arg_list[2];
  int i = (int )arg_list[0];
  int k = (int )arg_list[1];
//0 to N-1 row index
  if (i >= N) {
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
  if (k == 0) 
    newP[k] = 0;
  if (k < weights[i]) 
    newP[k] = oldP[k];
   else 
    newP[k] = (oldP[k] > profits[i] + oldP[k - weights[i]]?oldP[k] : profits[i] + oldP[k - weights[i]]);
  //struct __cont_env *knapSack_cps_cont_env3;
  //if (old_env != NULL) {
  //  knapSack_cps_cont_env3 = old_env;
  //  old_env = NULL;
  //}
  // else {
  //  knapSack_cps_cont_env3 = malloc(sizeof(struct __cont_env ));
  //}
  //knapSack_cps_cont_env3 -> arg_list = arg_list;
  //arg_list[2] = newP;
  //knapSack_cps_cont_env3 -> contn_env = contn_env;
  //knapSack_cps_cont_env3 -> cont_fn = knapSack_cps_cont3;
  arg_list[3] = newP;
  arg_list[2] = oldP;
  arg_list[0] = i + 1;
  //old_env-> cont_fn = knapSack_cps_cont3;
	old_env->arg_list = arg_list;
  old_env-> cont_fn = knapSack_cps;
  uwomp_barrier(old_env,phase_num);
}

void knapSack_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  //arg_list[3] = newP;
  //arg_list[2] = oldP;
  //arg_list[0] = i + 1;
  ////arg_list[1] = k;
  knapSack_cps(arg_list,contn_env,phase_num,old_env);
}

void knapSack_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
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
