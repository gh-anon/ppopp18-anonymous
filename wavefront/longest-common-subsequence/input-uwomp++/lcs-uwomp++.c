#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int size_x;
int size_y;

void getruntime(struct timeval tv1,struct timeval tv2)
{
  time_t sec1;
  time_t sec2;
  suseconds_t usec1;
  suseconds_t usec2;
  sec1 = tv1.tv_sec;
  sec2 = tv2.tv_sec;
  usec1 = tv1.tv_usec;
  usec2 = tv2.tv_usec;
  double start_time = (((double )sec1) + (usec1 / 1000000.0));
  double end_time = (((double )sec2) + (usec2 / 1000000.0));
  fprintf(stderr,"%f\n",(end_time - start_time));
}

#define    MAX(x,y)   ((x)>(y) ? (x) : (y))

int **table;
char *x,*y;//two sequences

void printInput() {
	fprintf(stdout, "size_x = %d, size_y = %d\n", size_x, size_y);
	fprintf(stdout, "x = %s\n", x);
	fprintf(stdout, "y = %s\n", y);
}

void printTable() {
	int i, j;

	for(i = 0; i <= size_x; i++) {
		for(j = 0; j <= size_y; j++) {
			fprintf(stdout, "%d ", table[i][j]);
		}
		fprintf(stdout, "\n");
	}
}

void longestSubSeq(int i, int c) {
	if(c > size_x + size_y)
		return;
	int j;
	if (c >= i && c <= i + size_y) {
		j = c - i;
		if(i==0 || j==0)
			table[i][j] = 0;
		else if(x[i-1] == y[j-1])
			table[i][j] = 1 + table[i-1][j-1];
		else
			table[i][j] = MAX(table[i-1][j], table[i][j-1]);
	}
#pragma omp barrier
	longestSubSeq(i, c+1);
}

int main(int argc, char **argv) {

  struct timeval tv1;
  struct timeval tv2;
	

	// Time
	double time;

	FILE   *fp;
	// Read input file (sequences in two lines)
	if ( argc > 1 ) {
		fp = fopen(argv[1], "r"); 
		if ( fp == NULL) {
			printf("[ERROR] : Failed to read file named '%s'.\n", argv[1]);
			exit(1);
		}
	} else {
		printf("USAGE : %s [filename].\n", argv[0]);
		exit(1);
	}

	// Read sizes of seqeunces
	fscanf(fp, "%d %d", &size_x, &size_y);
	//Initializations
	x = malloc(size_x*sizeof(char));
	if ( x == NULL ) {
		printf("[ERROR] : Failed to allocate memory for first seq.\n");
		exit(1);
	}
	y = malloc(size_y*sizeof(char));
	if ( y == NULL ) {
		printf("[ERROR] : Failed to allocate memory for second seq.\n");
		exit(1);
	}


	fscanf(fp, "%s", x);
	fscanf(fp, "%s", y);

	//printInput();
	int i;
	table = (int **)calloc(size_x+1, sizeof(int*));
	for(i=0; i<size_x+1; i++)
		table[i] = (int *)calloc(size_y+1, sizeof(int));


  gettimeofday(&tv1,0);


//#pragma omp parallel
//	{
//		int i, j=0, c;
//#pragma omp for
//		for(i=0; i<=size_x; i++)
//		{
//			for(c = 0; c <= size_x + size_y; c++) {
//				if (c >= i && c <= i + size_y) {
//					j = c - i;
//					if(i==0 || j==0)
//						table[i][j] = 0;
//					else if(x[i-1] == y[j-1])
//						table[i][j] = 1 + table[i-1][j-1];
//					else
//						table[i][j] = MAX(table[i-1][j], table[i][j-1]);
//				}
//#pragma omp barrier
//			}
//		}
//	}
//
 #pragma omp parallel
	{
		int i, j=0;
#pragma omp for
		for(i=0; i<=size_x; i++)
		{
			longestSubSeq(i, 0);
		}
	}
	//printTable();

	gettimeofday(&tv2,0);
  fprintf(stderr,"Run time = ");
  getruntime(tv1,tv2);

	fprintf(stdout, "longest subseq length = %d\n",table[size_x][size_y]);


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
