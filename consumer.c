#include	<stdio.h>
#include	<unistd.h>		// usleep()
#include	<stdlib.h>		// srand() & rand()
#include	"prodcon.h"
#include	"semaphore.h"

#define DEBUG
#define	C_RAND_SEED	6789

extern int runFlag;
extern int empty;
extern int full;
extern int bufManip;


void *consumer(void *vParam) {
// Local variables
	int itCount;
	const int timeToConsume = 300000;	// 0.3 seconds
	double result = 0;
	struct buffer_t *widgPtr;


// Announce existence
	printf("Consumer: Alive and running, N = %d\n", N);

	widgPtr = (struct buffer_t *) vParam;		// Cast buffer pointer
	srand(C_RAND_SEED);							// Set random#  seed
	runFlag = TRUE;
	while(runFlag) {
    // Get a full buffer
		P(full);

	// Manipulate shared data structure
		P(bufManip);
		itCount = widgPtr->buffer[widgPtr->nextFull];
#ifdef DEBUG
	// Write record to stdout
		printf("Consumer: Consumed widget #%d in buffer #%d\n",
				widgPtr->buffer[widgPtr->nextFull], widgPtr->nextFull);
#endif

		widgPtr->nextFull = (widgPtr->nextFull+1) % N;
		V(bufManip);
	// Consume the buffer
		usleep(rand()%timeToConsume);	// Simulate consumption
		V(empty);
	}

// Terminating
	printf("Consumer: Terminating\n");

	pthread_exit(1);
}
