#include	<pthread.h>
#include	<stdio.h>
#include   	 <stdlib.h>
#include	"prodcon.h"
#include	"semaphore.h"


#define DEBUG

int runFlag = TRUE;

// int handles to semaphores
// These are globals to simplify the code (they are shared)
int empty;
int full;
int bufManip;
struct buffer_t widgets;


// The main program establishes the shared information used by the
// producer and consumer threads

int main(int argc, char *argv[]) {
// Local variables
 	pthread_t prod_thrd, cons_thrd;	// Producer & consumer handles
	int runTime;
	int i;

// Get command line argument
	if(argc != 2||atoi(argv[1]) < 1) {
		printf("Usage: prodcon <run_time_seconds>\n");
		exit(0);
	} else {
		runTime = atoi(argv[1]);
		printf("Computation to run for %d seconds\n", runTime);
	}

// Initialize synchronization objects
	empty = create_semaphore (N);
	full = create_semaphore (0);
	bufManip = create_semaphore(1);

// Initialize buffer pool
	widgets.nextEmpty = 0;
	widgets.nextFull = 0;
	for(i = 0; i < N; i++)
		widgets.buffer[i] = EMPTY;

	
// Create producer and consumer threads
	printf("Main thread: Creating consumer thread\n");
	pthread_create(&cons_thrd, NULL, consumer, &widgets);
	printf("Main thread: Creating producer thread\n");
	pthread_create(&prod_thrd, NULL, producer, &widgets);

// Sleep while the children work ...
printf("Parent going to sleep ... \n");
	sleep(runTime);
printf("Parent awake and terminating children\n");
	runFlag = FALSE;	// Signal children to terminate

// Wait for producer & consumer to terminate
	pthread_join(prod_thrd, NULL);
	pthread_join(cons_thrd, NULL);

// Release the semaphores
	delete_semaphore(empty);
	delete_semaphore(full);
	delete_semaphore(bufManip);

// Now we can quit
	printf("Main thread: Terminated\n");

	exit(1);
}


