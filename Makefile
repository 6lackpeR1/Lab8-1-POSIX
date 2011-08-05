prodcon: main.c semaphore.o consumer.o producer.o prodcon.h
	gcc -o prodcon main.c semaphore.o consumer.o producer.o -lpthread

semaphore.o: semaphore.c semaphore.h
	gcc -c semaphore.c

consumer.o: consumer.c prodcon.h semaphore.h
	gcc -c consumer.c

producer.o: producer.c prodcon.h semaphore.h
	gcc -c producer.c

