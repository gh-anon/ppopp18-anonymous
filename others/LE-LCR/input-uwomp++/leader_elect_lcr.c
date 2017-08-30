#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define Infinity INT_MAX

#define FILE_NAME_SIZE 100

void getruntime(struct timeval tv1, struct timeval tv2) {
	time_t sec1, sec2;
	suseconds_t usec1, usec2;

	sec1 = tv1.tv_sec;
	sec2 = tv2.tv_sec;
	usec1 = tv1.tv_usec;
	usec2 = tv2.tv_usec;

	double start_time = (double)sec1 + (usec1/1000000.0);
	double end_time = (double)sec2 + (usec2/1000000.0);
	fprintf(stderr, "%f\n", end_time - start_time);
}

char input_file[FILE_NAME_SIZE];
char output_file[FILE_NAME_SIZE];

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
};

int processes;
int *IdStore;
struct Process *processSet;
int step;

/** Initializes all the fields of the abstract node. */
void initialize() {
	int i;
	for(i = 0; i < processes; i++) {
		int pt = i;
		processSet[i].id = IdStore[pt];
		processSet[i].leaderId = processSet[i].id;
		processSet[i].send = processSet[i].id;
		processSet[i].status = FALSE;
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
void leaderElect() {
#pragma omp parallel
	{
		int i;
		int pt, p, sval;
#pragma omp for private(i)
		for(i = 0; i < processes; i++) {
			while (step < processes) {
				pt = i;
				pt = (pt + 1) % processes;
				p = pt;
				sval = processSet[i].send;
				processSet[p].recievedId = sval;

#pragma omp barrier

				if(processSet[i].recievedId > processSet[i].leaderId) {
					processSet[i].send = processSet[i].recievedId;
					processSet[i].leaderId = processSet[i].recievedId;
				} else if(processSet[i].recievedId == processSet[i].id) {
					processSet[i].status = TRUE;
					processSet[i].leaderId = processSet[i].id;
				}
				if(i == 1) { step++; }
#pragma omp barrier
			}
		}
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
void transmitLeader() {
	int lead = 0;
	int tmp = 0;

	int i;
	for(i = 0; i < processes; i++) {	
		int check = 0;
		if(processSet[i].status)
			check=1;
		tmp = check;
		if(tmp == 1)
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
	for(j = 0; j < processes; j++) {
		int pt_loc = lead;
		//if(pt.equals(R.maxPoint())) {
		if(pt == processes - 1) {
			pt = 0;
		} else {
			pt = pt+1;
		}
		processSet[pt].leaderId = pt_loc; 
	}

	int lindex = lead;
	int pt_loc = lindex;
	processSet[lindex].leaderId = pt_loc;
}

/** Validates the output resulting from the execution of the algorithm. */  	
void outputVerifier() {
	int max = INT_MIN;
	int i;
	for(i = 0; i < processes; i++) {
		if(max < IdStore[i]) {
			max = IdStore[i];
		}
	}
	int p = 0;
	int lead = processSet[p].leaderId;
	int q = lead;
	lead = processSet[q].id;
	if(max == lead) {
		fprintf(stderr, "Output verified\n");
	} else {
		fprintf(stderr, "Output not verified\n");
	}
}

int main(int argc, char *argv[]) {
	strcpy(input_file, "inputlcr.txt");
	strcpy(output_file, "outputlcr.txt");

	/*Process command line arguments and take the values for each and input and output files*/
	int verify = FALSE;
	int i;
	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i],"-ver")==0 || strcmp(argv[i],"-verify")==0) {
			verify = TRUE;
		}
		else if(strcmp(argv[i], "-in")==0)
		{
			i++;
			strcpy(input_file, argv[i]);
		}
		else if(strcmp(argv[i], "-out")==0)
		{
			i++;
			strcpy(output_file, argv[i]);
		}
	}

	FILE *input = fopen(input_file, "r" );
	if(input == NULL) {
		fprintf(stderr, "Error in opening the input file\n");
		exit(0);
	}

	/* 
	 * Get number of processes.
	 */
	fscanf(input, "%d", &processes);
	/*
	 * Allocate memory for set of ids.
	 */
	IdStore = calloc(processes, sizeof(int));
	/*
	 * Read ids.
	 */
	for(i = 0; i < processes; i++) {
		fscanf(input, "%d", &IdStore[i]);
	}
	/*
	 * Distribution of nodes.
	 */
	processSet = calloc(processes, sizeof(struct Process));
	/*
	 * Initialize
	 */
	initialize();

	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);

	//for(step = 0; step < processes; step++) {
		leaderElect();
	//}
	transmitLeader();

	gettimeofday(&tv2, NULL);
	fprintf(stderr, "Estimated Time = ");
	getruntime(tv1, tv2);

	//printOutput(output_file);
	if(verify)
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
