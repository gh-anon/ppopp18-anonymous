#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "uwomp-barrier-optimized.h" 
void longestSubSeq_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void longestSubSeq_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void longestSubSeq_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1(int i);
void OmpRegBody1();
int size_x;
int size_y;

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
int **table;
//two sequences
char *x;
char *y;

void printInput()
{
  fprintf(stdout,"size_x = %d, size_y = %d\n",size_x,size_y);
  fprintf(stdout,"x = %s\n",x);
  fprintf(stdout,"y = %s\n",y);
}

void printTable()
{
  int i;
  int j;
  for (i = 0; i <= size_x; i++) {
    for (j = 0; j <= size_y; j++) {
      fprintf(stdout,"%d ",table[i][j]);
    }
    fprintf(stdout,"\n");
  }
}
void ***arg_list_longestSubSeq_0;

void longestSubSeq(int i,int c)
{
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
// Read sizes of seqeunces
  fscanf(fp,"%d %d",&size_x,&size_y);
//Initializations
  x = (malloc(size_x * sizeof(char )));
  if (x == ((void *)0)) {
    printf("[ERROR] : Failed to allocate memory for first seq.\n");
    exit(1);
  }
  y = (malloc(size_y * sizeof(char )));
  if (y == ((void *)0)) {
    printf("[ERROR] : Failed to allocate memory for second seq.\n");
    exit(1);
  }
  fscanf(fp,"%s",x);
  fscanf(fp,"%s",y);
//printInput();
  int i;
  table = ((int **)(calloc((size_x + 1),sizeof(int *))));
  for (i = 0; i < size_x + 1; i++) 
    table[i] = ((int *)(calloc((size_y + 1),sizeof(int ))));
  gettimeofday(&tv1,0);
#pragma omp parallel 
{
//    struct __cont_env *init_contn_env = malloc(sizeof(struct __cont_env ));
//    init_contn_env -> cont_fn = uwomp_first_fun;
#pragma omp single 
{
    arg_list_parallel_for_body1_0 = calloc(size_x - -1,sizeof(void **));
     uwomp_worklist_init((omp_get_num_threads()),size_x - -1, 0, 0);
    }
    void **__parreg_arglist;
    __parreg_arglist = ((void **)(malloc(0 * sizeof(void *))));
    OmpRegBody1_cps(__parreg_arglist,NULL,0,NULL);
//    uwomp_free_worklist_free();
  }
//printTable();
  gettimeofday(&tv2,0);
  fprintf(stderr,"Run time = ");
  getruntime(tv1,tv2);
  fprintf(stdout,"longest subseq length = %d\n",table[size_x][size_y]);
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

void OmpRegBody1()
{
}

void parallel_for_body1(int i)
{
}

void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[0];
  arg_list[0] = 0;
  arg_list[1] = i;//added
  longestSubSeq_cps(arg_list,contn_env,phase_num,old_env);
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
//  int j = 0;
  
#pragma omp for 
  for (i = 0; i <= size_x; i++) {
    if (arg_list_parallel_for_body1_0[i] == NULL) {
      //arg_list_parallel_for_body1_0[i] = malloc(3 * sizeof(void *));
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

void longestSubSeq_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[1];
  int c = (int )arg_list[0];
  if (c > size_x + size_y) {
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
  if (c >= i && c <= i + size_y) {
    j = c - i;
    if (i == 0 || j == 0) 
      table[i][j] = 0;
     else if (((int )x[i - 1]) == ((int )y[j - 1])) 
      table[i][j] = 1 + table[i - 1][j - 1];
     else 
      table[i][j] = (table[i - 1][j] > table[i][j - 1]?table[i - 1][j] : table[i][j - 1]);
  }
  //struct __cont_env *longestSubSeq_cps_cont_env3;
  //if (old_env != NULL) {
  //  longestSubSeq_cps_cont_env3 = old_env;
  //  old_env = NULL;
  //  longestSubSeq_cps_cont_env3 -> cont_fn = longestSubSeq_cps_cont3;
  //}
  // else {
  //  longestSubSeq_cps_cont_env3 = malloc(sizeof(struct __cont_env ));
  //  longestSubSeq_cps_cont_env3 -> arg_list = arg_list;
  //  longestSubSeq_cps_cont_env3 -> contn_env = contn_env;
  //  longestSubSeq_cps_cont_env3 -> cont_fn = longestSubSeq_cps_cont3;
  //}
  arg_list[0] = c + 1;
	old_env->arg_list = arg_list;
  old_env-> cont_fn = longestSubSeq_cps;
  uwomp_barrier(old_env,i,phase_num);
}

void longestSubSeq_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int c = (int )arg_list[0];
  arg_list[0] = c + 1;
  longestSubSeq_cps(arg_list,contn_env,phase_num,old_env);
}

void longestSubSeq_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
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
