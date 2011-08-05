#include	<stdio.h>
#include	<stdlib.h>		// srand() & rand()
#include	"prodcon.h"
#include	"semaphore.h"

#define DEBUG
#define	P_RAND_SEED	1234

extern int runFlag;
extern int empty;
extern int full;
extern int bufManip;


void *producer(void *vParam) {
// Local variables
	const int timeToProduce = 200000;	// 0.2 seconds
	int itCount;
	double result = 0;
	struct buffer_t *widgPtr;

// Announce existence
	printf("Producer: Alive and running, N = %d\n", N);

	widgPtr = (struct buffer_t *) vParam;		// Cast buffer pointer
	srand(P_RAND_SEED);							// Set random#  seed
	itCount = 100;
	while(runFlag) {
    // Produce the buffer	
		usleep(rand()%timeToProduce);	// Simulate production time
    // Get an empty buffer
		P(empty);

	// Manipulate the buffer pool
		P(bufManip);
		widgPtr->buffer[widgPtr->nextEmpty] = itCount++;
#ifdef DEBUG
	// Write record to stdout
			printf("Producer: Produce widget #%d in buffer #%d\n",
				widgPtr->buffer[widgPtr->nextEmpty], widgPtr->nextEmpty);
#endif
		widgPtr->nextEmpty = (widgPtr->nextEmpty+1) % N;
printf("updated widgPtr->nextEmpty = %d\n", widgPtr->nextEmpty);
		V(bufManip);
		V(full);
	}

// Terminating
	printf("Producer: Terminating\n");

	pthread_exit(1);
}
