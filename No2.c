#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;

void* Pth_mat_vect(void* rank); /* Thread function */

int main(int argc, char* argv[]) {
	 long 		thread; /* Use long in case of a 64-bit system */
	 pthread_t* thread_handles;
	
	 /* Get number of threads from command line */
	 thread_count = strtol(argv[1], NULL, 10);
	
	 thread_handles = malloc (thread_count*sizeof(pthread_t));
	
	 for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL,
	 		Pth_mat_vect, (void*) thread);
	
	 printf("\nHello from the main thread\n");
	
	 for (thread = 0; thread < thread_count; thread++)
	 	pthread_join(thread_handles[thread], NULL);
	
	 free(thread_handles);
	 return 0;
 } 	 /* main */
 
 void* Pth_mat_vect(void* rank) {
	long my_rank = (long) rank;
	int i, j;
	int m = 30;
	int n = 30;
	int local_m = m/thread_count;
	int my_first_row = my_rank*local_m;
	int my_last_row = (my_rank+1)*local_m - 1;

	for (i = my_first_row; i <= my_last_row; i++) {
		int y[i];
		y[i] = 0.0;
		for (j = 0; j < n; j++) {
			int A[i][j],x[j];
			y[i] += A[i][j]*x[j];
			printf("%d\n",y[i]);
		}
	}
	printf("\nHello from thread %ld of %d\n", my_rank, thread_count);
	
	return NULL;
} /* Pth mat vect */
