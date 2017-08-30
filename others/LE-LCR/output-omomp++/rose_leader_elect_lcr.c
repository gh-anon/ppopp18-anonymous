#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define Infinity INT_MAX
#define FILE_NAME_SIZE 100
#include "uwomp-barrier.h" 
void parallel_for_body1__while__0_cps_cont5(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps_cont2(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void OmpRegBody1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps_cont1(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env);
void parallel_for_body1__while__0(int *p_i,int *p_p,int *p_pt,int *p_sval);
void parallel_for_body1(int i,int p,int pt,int sval);
void OmpRegBody1();

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
char input_file[100];
char output_file[100];
/**
 * <code>PROCESS</code> specifies the structure for each abstract node
 * part of the Leader election algorithm.
 */

struct Process 
{
/** Specifies identifier for each node. */
  int id;
/** Represents the Identifier that the process will send to its neighbor. */
  int send;
/** Represents the Identifier of the leader. */
  int leaderId;
/** Represents the Identifier that the process receives from its neighbor. */
  int recievedId;
/** Represents the status of the process and will be set to true for leader. */
  int status;
}
;
int processes;
int *IdStore;
struct Process *processSet;
int step;
/** Initializes all the fields of the abstract node. */

void initialize()
{
  int i;
  for (i = 0; i < processes; i++) {
    int pt = i;
    processSet[i] . id = IdStore[pt];
    processSet[i] . leaderId = processSet[i] . id;
    processSet[i] . send = processSet[i] . id;
    processSet[i] . status = 0;
  }
}
/** 
 * Sends message to the neighbor.
 * 
 * @param	receiver	Node which receives the message.
 * @param	sval		Message value.
 */
//#define sendMessage(receiver, sval) processSet[receiver].recievedId = sval
/** Aims at selecting the leader from a set of nodes. */

void leaderElect()
{
#pragma omp parallel 
{
    //struct __cont_env *init_contn_env = malloc(sizeof(struct __cont_env ));
    //init_contn_env -> cont_fn = uwomp_first_fun;
#pragma omp single 
{
      uwomp_worklist_init((omp_get_num_threads()),32764);
    }
    void **__parreg_arglist;
    __parreg_arglist = ((void **)(malloc(0 * sizeof(void *))));
    OmpRegBody1_cps(__parreg_arglist,NULL,0,NULL);
    //uwomp_free_worklist_free();
  }
}
/** 
 * Sets the leader for a node.
 * 
 * @param	uNode		Leader node.
 * @param	aNode		Node whose leader has to be set.
 */
//#define setLeader(uNode, aNode) processSet[aNode].leaderId = uNode
/** Transmits the message from one node to another. */

void transmitLeader()
{
  int lead = 0;
  int tmp = 0;
  int i;
  for (i = 0; i < processes; i++) {
    int check = 0;
    if (processSet[i] . status) 
      check = 1;
    tmp = check;
    if (tmp == 1) 
      lead = i;
//if(!loadValue.equals(0)) {
//	at(D(i)) {
//		val ipt:Long = i(0);
//		nval(i) = loadweight(nval(i)+ipt);
//	}
//}
  }
  int pt = lead;
  int j;
  for (j = 0; j < processes; j++) {
    int pt_loc = lead;
//if(pt.equals(R.maxPoint())) {
    if (pt == processes - 1) {
      pt = 0;
    }
     else {
      pt = pt + 1;
    }
    processSet[pt] . leaderId = pt_loc;
  }
  int lindex = lead;
  int pt_loc = lindex;
  processSet[lindex] . leaderId = pt_loc;
}
/** Validates the output resulting from the execution of the algorithm. */

void outputVerifier()
{
  int max = - 2147483647 - 1;
  int i;
  for (i = 0; i < processes; i++) {
    if (max < IdStore[i]) {
      max = IdStore[i];
    }
  }
  int p = 0;
  int lead = processSet[p] . leaderId;
  int q = lead;
  lead = processSet[q] . id;
  if (max == lead) {
    fprintf(stdout,"Output verified\n");
  }
   else {
    fprintf(stdout,"Output not verified\n");
  }
}

int main(int argc,char *argv[])
{
  strcpy(input_file,"inputlcr.txt");
  strcpy(output_file,"outputlcr.txt");
/*Process command line arguments and take the values for each and input and output files*/
  int verify = 0;
  int i;
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i],"-ver") == 0 || strcmp(argv[i],"-verify") == 0) {
      verify = 1;
    }
     else if (strcmp(argv[i],"-in") == 0) {
      i++;
      strcpy(input_file,argv[i]);
    }
     else if (strcmp(argv[i],"-out") == 0) {
      i++;
      strcpy(output_file,argv[i]);
    }
  }
  FILE *input = fopen(input_file,"r");
  if (input == ((void *)0)) {
    fprintf(stderr,"Error in opening the input file\n");
    exit(0);
  }
/* 
	 * Get number of processes.
	 */
  fscanf(input,"%d",&processes);
/*
	 * Allocate memory for set of ids.
	 */
  IdStore = (calloc(processes,sizeof(int )));
/*
	 * Read ids.
	 */
  for (i = 0; i < processes; i++) {
    fscanf(input,"%d",&IdStore[i]);
  }
/*
	 * Distribution of nodes.
	 */
  processSet = (calloc(processes,sizeof(struct Process )));
/*
	 * Initialize
	 */
  initialize();
  struct timeval tv1;
  struct timeval tv2;
  gettimeofday(&tv1,((void *)0));
//for(step = 0; step < processes; step++) {
  leaderElect();
//}
  transmitLeader();
  gettimeofday(&tv2,((void *)0));
  fprintf(stderr,"Run time = ");
  getruntime(tv1,tv2);
//printOutput(output_file);
  if (verify) 
    outputVerifier();
//if(!bfs.loadValue.equals(0)) {
//	var sumval:double=0;
//	for(i=0; i<bfs.nodes; i++) {
//		val pt:Point = Point.make(i);
//		var arrSum:Long = bfs.getNval(pt);
//		sumval = sumval + arrSum;
//	}
//	if(sumval > 0)
//		Console.OUT.println();
//}
  return 0;
}
//void ***arg_list_OmpRegBody1_0;

void OmpRegBody1()
{
}
void ***arg_list_parallel_for_body1_0;

void parallel_for_body1(int i,int p,int pt,int sval)
{
}
//void ***arg_list_parallel_for_body1__while__0_0;

void parallel_for_body1__while__0(int *p_i,int *p_p,int *p_pt,int *p_sval)
{
}

void parallel_for_body1_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  //int i = (int )arg_list[0];
  //int p = (int )arg_list[1];
  //int pt = (int )arg_list[2];
  //int sval = (int )arg_list[3];
  //arg_list[2] = &i;
  //arg_list[3] = &p;
  //arg_list[4] = &pt;
  //arg_list[5] = &sval;
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
  int i;
  //int pt;
  //int p;
  //int sval;
#pragma omp single 
{
    arg_list_parallel_for_body1_0 = calloc(processes - 0,sizeof(void **));
    //arg_list_OmpRegBody1_0 = calloc(processes - 0,sizeof(void **));
    //arg_list_parallel_for_body1__while__0_0 = calloc(processes - 0,sizeof(void **));
  }
  
#pragma omp for  private(i)
  for (i = 0; i < processes; i++) {
    if (arg_list_parallel_for_body1_0[i] == NULL) {
      arg_list_parallel_for_body1_0[i] = malloc(1 * sizeof(void *));
    }
    arg_list_parallel_for_body1_0[i][0] = i;
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

void parallel_for_body1__while__0_cps(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[0];
  //int p = (int )arg_list[1];
  //int pt = (int )arg_list[2];
  //int sval = (int )arg_list[3];
  if (!(step < processes)) {
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
  int pt = i;
  pt = (pt + 1) % processes;
  int p = pt;
  int sval = processSet[i] . send;
  processSet[p] . recievedId = sval;
  //struct __cont_env *parallel_for_body1__while__0_cps_cont_env3;
  //if (old_env != NULL) {
  //  parallel_for_body1__while__0_cps_cont_env3 = old_env;
  //  old_env = NULL;
  //}
  // else {
  //  parallel_for_body1__while__0_cps_cont_env3 = malloc(sizeof(struct __cont_env ));
  //}
  //parallel_for_body1__while__0_cps_cont_env3 -> arg_list = arg_list;
  //arg_list[0] = i;
  //arg_list[1] = p;
  //arg_list[6] = pt;
  //arg_list[7] = sval;
  //parallel_for_body1__while__0_cps_cont_env3 -> contn_env = contn_env;
  //parallel_for_body1__while__0_cps_cont_env3 -> cont_fn = parallel_for_body1__while__0_cps_cont3;
  old_env-> cont_fn = parallel_for_body1__while__0_cps_cont3;
  uwomp_barrier(old_env,phase_num);
}

void parallel_for_body1__while__0_cps_cont3(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  int i = (int )arg_list[0];
  if (processSet[i] . recievedId > processSet[i] . leaderId) {
    processSet[i] . send = processSet[i] . recievedId;
    processSet[i] . leaderId = processSet[i] . recievedId;
  }
   else if (processSet[i] . recievedId == processSet[i] . id) {
    processSet[i] . status = 1;
    processSet[i] . leaderId = processSet[i] . id;
  }
  if (i == 1) {
    step++;
  }
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
  //parallel_for_body1__while__0_cps_cont_env4 -> cont_fn = parallel_for_body1__while__0_cps; //parallel_for_body1__while__0_cps_cont4;
  old_env-> cont_fn = parallel_for_body1__while__0_cps; //parallel_for_body1__while__0_cps_cont4;
  uwomp_barrier(old_env,phase_num);
}

void parallel_for_body1__while__0_cps_cont4(void **arg_list,struct __cont_env *contn_env,int phase_num,struct __cont_env *old_env)
{
  //int i = (int )arg_list[0];
  //int p = (int )arg_list[1];
  //int *p_i = (int *)arg_list[2];
  //int *p_p = (int *)arg_list[3];
  //int *p_pt = (int *)arg_list[4];
  //int *p_sval = (int *)arg_list[5];
  //int pt = (int )arg_list[6];
  //int sval = (int )arg_list[7];
  // *p_i = i;
  // *p_p = p;
  // *p_pt = pt;
  // *p_sval = sval;
  //arg_list[2] = p_i;
  //arg_list[3] = p_p;
  //arg_list[4] = p_pt;
  //arg_list[5] = p_sval;
  parallel_for_body1__while__0_cps(arg_list,contn_env,phase_num,old_env);
}

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
