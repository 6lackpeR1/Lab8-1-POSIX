/* Semaphore function prototypes */
void *P(int);
void *V(int);
int create_semaphore(int);


typedef struct semaphore_t {
	int	id;
	int	value;
	pthread_mutex_t	mtx;
	pthread_mutex_t	hold;
	struct semaphore_t	*next;
} semaphore;

