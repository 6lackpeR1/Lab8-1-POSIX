#define	N	25
#define	EMPTY	0
#define	FULL	1
#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif
#ifndef NULL
#define NULL	'\0'
#endif

// Prototypes
void *producer(void *);
void *consumer(void *);


struct buffer_t {
	int buffer[N];
	unsigned int nextFull;
	unsigned int nextEmpty;
};
