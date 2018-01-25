#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int N;
int *P;
int **M;

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

void matrix_paranth_for_len(int i, int l)
{
		if(l > N)
			return;
		int j,k,v;
		if(i <= N-l+1)
		{
			 j = i+l-1;
			 M[i][j] = INT_MAX;
			 for(k=i; k<j; k++)
			 {
					v = M[i][k] +M[k+1][j] + P[i-1]*P[k]*P[j];
					if(v<M[i][j])
						M[i][j] = v;
			 }
		}
#pragma omp barrier
		matrix_paranth_for_len(i, l+1);
}

print_val()
{
	int i,j;
	for(i=0; i<=N; i++)
	{
		for(j=0; j<=N; j++)
		{
			printf("%d\t", M[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char **argv)
{
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

	// Read number of matrices
	fscanf(fp, "%d", &N);

	int i;

	P = calloc(N+1, sizeof(int));
	for(i=0; i<=N; i++) {
		fscanf(fp, "%d", &P[i]);
	}

	M = (int **)calloc(N+1, sizeof(int *));
	for(i=0;i<=N; i++)
		M[i] = (int *)calloc(N+1, sizeof(int));
	for(i=0; i<=N; i++)
		M[i][i] = 0;

  gettimeofday(&tv1,0);
#pragma omp parallel
	{
		int i;
#pragma omp for
		for(i=1; i <= N; i++) {
			matrix_paranth_for_len(i,2);
		}
	}
	gettimeofday(&tv2,0);
  fprintf(stderr,"Run time = ");
  getruntime(tv1,tv2);

	//print_val();
	fprintf(stdout, "Optimum number of multiplications = %d\n",M[1][N]);

	return 0;
}
