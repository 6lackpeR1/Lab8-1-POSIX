#include	<pthread.h>
#include	<sched.h>
#include   	 <malloc.h>
#include	"semaphore.h"
#define	DEBUG	

semaphore *sem;
int num_sems = 0;

/* Local function prototypes */
semaphore *lookup(int);

void *P(int sem_ref) {
    semaphore *this_sem;

    this_sem = lookup(sem_ref);
    pthread_mutex_lock(&this_sem->mtx);
    this_sem->value--;
    if(this_sem->value < 0) { /* Block this thread */
        pthread_mutex_unlock(&this_sem->mtx);
        pthread_mutex_lock(&this_sem->hold);	// This should have 0 val initially
    }
    pthread_mutex_unlock(&this_sem->mtx);
}

void *V(int sem_ref) {
    semaphore *this_sem;

    this_sem = lookup(sem_ref);
    pthread_mutex_lock(&this_sem->mtx);
    this_sem->value++;
    if(this_sem->value > 0) pthread_mutex_unlock(&this_sem->hold);
    pthread_mutex_unlock(&this_sem->mtx);
}

int create_semaphore(int iVal) {
    semaphore *new_sem;

    new_sem = (semaphore *) malloc(sizeof(semaphore));
    new_sem->id = ++num_sems;
    new_sem->value = (iVal < 0)? -iVal: iVal;
    pthread_mutex_init(&new_sem->mtx, NULL);
    pthread_mutex_init(&new_sem->hold, NULL);
/* This won't block.  It is a hack to get hold into the right state.
 * We want a general semaphore, and we are using a mutex to do it.
 */
    pthread_mutex_lock(&new_sem->hold);
    new_sem->next = sem;
    sem = new_sem;
#ifdef DEBUG
    printf("created semaphore number %d with initial value = %d\n",
		new_sem->id, new_sem->value);
#endif
    return new_sem->id;
}

int delete_semaphore(int me) {
#ifdef DEBUG
    printf("delete_semaphore() not implemented\n");
#endif
}

semaphore *lookup(int sid) {
    semaphore *next_sem;

    next_sem = sem;
    while(next_sem != NULL) {
	if(next_sem->id == sid) return next_sem;
	next_sem = next_sem->next;
    }
/* Semaphore not found */
    return NULL;
}
